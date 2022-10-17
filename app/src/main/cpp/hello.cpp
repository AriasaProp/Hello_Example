#include <jni.h>
#include <cstdlib>
#include <cstring>
#include <time.h>
#include <cmath>

#if __ANDROID_API__ >= 24
#include <GLES3/gl32.h>
#elif __ANDROID_API__ >= 21
#include <GLES3/gl31.h>
#else
#include <GLES3/gl3.h>
#endif
#include <EGL/egl.h>

#define DEBUG 1

#include <android/log.h>
#define LOG_TAG "GLES3JNI"
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#if DEBUG
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#else
#define ALOGV(...)
#endif

#define MAX_INSTANCES_PER_SIDE 16
#define MAX_INSTANCES (MAX_INSTANCES_PER_SIDE * MAX_INSTANCES_PER_SIDE)
// 2π of rotation
#define TWO_PI 6.283185307179586476925286766559005768394338798750211641949889184615632812572417997256069650684234136
// 30% of rotation
#define MAX_ROT_SPEED 1.884955592153875943077586029967701730518301639625063492584966755384689843771725399176820895205270241

struct Vertex {
    GLfloat pos[2];
    GLubyte rgba[4];
};

const Vertex QUAD[4] = {
    {{-0.7f, -0.7f}, {0x00, 0xFF, 0x00 }},
    {{0.7f, -0.7f}, {0x00, 0x00, 0xFF }},
    {{-0.7f, 0.7f}, {0xFF, 0x00, 0x00}},
    {{0.7f, 0.7f}, {0xFF, 0xFF, 0xFF}}
};

extern bool checkGlError(const char *);
extern GLuint createShader(GLenum, const char *);
extern GLuint createProgram(const char *, const char *);

class Renderer {
public:
    Renderer();
    bool init();
    ~Renderer();
    void resize(int, int);
    void render();
    float *mapOffsetBuf();
    void unmapOffsetBuf();
    float *mapTransformBuf();
    void unmapTransformBuf();
    void draw(unsigned int);

private:
		enum {VB_INSTANCE, VB_SCALEROT, VB_OFFSET, VB_COUNT};
    
    const EGLContext mEglContext;
    GLuint mProgram;
    GLuint mVB[VB_COUNT];
    GLuint mVBState;
    
    void calcSceneParams(unsigned int, unsigned int, float *);
    void step();
    unsigned int mNumInstances;
    float mScale[2];
    float mAngularVelocity[MAX_INSTANCES];
    uint64_t mLastFrameNs;
    float mAngles[MAX_INSTANCES];
};

#define STR(s) #s
#define POS_ATTRIB 0
#define COLOR_ATTRIB 1
#define SCALEROT_ATTRIB 2
#define OFFSET_ATTRIB 3
static const char VERTEX_SHADER[] =
		"#version 300 es\n"
		"layout(location=" STR(POS_ATTRIB) ") in vec2 pos;\n"
		"layout(location=" STR(COLOR_ATTRIB) ") in vec4 color;\n"
		"layout(location=" STR(SCALEROT_ATTRIB) ") in vec4 scaleRot;\n"
		"layout(location=" STR(OFFSET_ATTRIB) ") in vec2 offset;\n"
		"out vec4 vColor;\n"
		"void main(){\n"
		"    mat2 sr=mat2(scaleRot.xy, scaleRot.zw);\n"
		"    gl_Position=vec4(sr * pos + offset, 0.0, 1.0);\n"
		"    vColor=color;\n"
		"}\n";

static const char FRAGMENT_SHADER[] =
		"#version 300 es\n"
		"precision mediump float;\n"
		"in vec4 vColor;\n"
		"out vec4 outColor;\n"
		"void main(){\n"
		"    outColor=vColor;\n"
		"}\n";

Renderer::Renderer(): mProgram(0), mVBState(0) {
		mEglContext = eglGetCurrentContext();
		memset(mScale, 0, sizeof(mScale));
		memset(mAngularVelocity, 0, sizeof(mAngularVelocity));
		memset(mAngles, 0, sizeof(mAngles));
		memset(mVB, 0, sizeof(mVB));
}

bool Renderer::init() {
    mProgram = createProgram(VERTEX_SHADER, FRAGMENT_SHADER);
    if (!mProgram)
        return false;
    glGenBuffers(VB_COUNT, mVB);
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_INSTANCE]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(QUAD), &QUAD[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_SCALEROT]);
    glBufferData(GL_ARRAY_BUFFER, MAX_INSTANCES * 4 * sizeof(float), NULL, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_OFFSET]);
    glBufferData(GL_ARRAY_BUFFER, MAX_INSTANCES * 2 * sizeof(float), NULL, GL_STATIC_DRAW);
    glGenVertexArrays(1, & mVBState);
    glBindVertexArray(mVBState);
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_INSTANCE]);
    glVertexAttribPointer(POS_ATTRIB, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (const GLvoid * ) offsetof(Vertex, pos));
    glVertexAttribPointer(COLOR_ATTRIB, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (const GLvoid * ) offsetof(Vertex, rgba));
    glEnableVertexAttribArray(POS_ATTRIB);
    glEnableVertexAttribArray(COLOR_ATTRIB);
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_SCALEROT]);
    glVertexAttribPointer(SCALEROT_ATTRIB, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glEnableVertexAttribArray(SCALEROT_ATTRIB);
    glVertexAttribDivisor(SCALEROT_ATTRIB, 1);
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_OFFSET]);
    glVertexAttribPointer(OFFSET_ATTRIB, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);
    glEnableVertexAttribArray(OFFSET_ATTRIB);
    glVertexAttribDivisor(OFFSET_ATTRIB, 1);
    ALOGV("Using OpenGL ES 3.0 renderer");
    return true;
}

Renderer::~Renderer() {
    if (eglGetCurrentContext() != mEglContext)
        return;
    glDeleteVertexArrays(1, & mVBState);
    glDeleteBuffers(VB_COUNT, mVB);
    glDeleteProgram(mProgram);
}

void Renderer::resize(int w, int h) {
    auto offsets = mapOffsetBuf();
    calcSceneParams(w, h, offsets);
    unmapOffsetBuf();
    for (unsigned int i = 0; i < mNumInstances; i++) {
        mAngles[i] = drand48() * TWO_PI;
        mAngularVelocity[i] = MAX_ROT_SPEED * (2.0 * drand48() - 1.0);
    }

    mLastFrameNs = 0;
    glViewport(0, 0, w, h);
}

void Renderer::calcSceneParams(unsigned int w, unsigned int h, float *offsets) {
    const float NCELLS_MAJOR = MAX_INSTANCES_PER_SIDE;
    const float CELL_SIZE = 2.0f / NCELLS_MAJOR;
    const float dim[2] = {
        fmaxf(w, h),
        fminf(w, h)
    };
    const float aspect[2] = {
        dim[0] / dim[1],
        dim[1] / dim[0]
    };
    const float scene2clip[2] = {
        1.0f,
        aspect[0]
    };
    const int ncells[2] = {
        static_cast < int > (NCELLS_MAJOR),
        (int) floorf(NCELLS_MAJOR * aspect[1])
    };

    float centers[2][MAX_INSTANCES_PER_SIDE];
    for (int d = 0; d < 2; d++) {
        auto offset = -ncells[d] / NCELLS_MAJOR; // -1.0 for d=0 
        for (auto i = 0; i < ncells[d]; i++) {
            centers[d][i] = scene2clip[d] * (CELL_SIZE * (i + 0.5f) + offset);
        }
    }

    int major = w >= h ? 0 : 1;
    int minor = w >= h ? 1 : 0;
    for (int i = 0; i < ncells[0]; i++) {
        for (int j = 0; j < ncells[1]; j++) {
            int idx = i * ncells[1] + j;
            offsets[2 * idx + major] = centers[0][i];
            offsets[2 * idx + minor] = centers[1][j];
        }
    }

    mNumInstances = ncells[0] * ncells[1];
    mScale[major] = 0.5f * CELL_SIZE * scene2clip[0];
    mScale[minor] = 0.5f * CELL_SIZE * scene2clip[1];
}

void Renderer::step() {
    timespec now;
    clock_gettime(CLOCK_MONOTONIC, & now);
    auto nowNs = now.tv_sec * 1000000000ull + now.tv_nsec;

    if (mLastFrameNs > 0) {
        float dt = float(nowNs - mLastFrameNs) * 0.000000001f;
        for (unsigned int i = 0; i < mNumInstances; i++) {
            mAngles[i] += mAngularVelocity[i] * dt;
            if (mAngles[i] >= TWO_PI) {
                mAngles[i] -= TWO_PI;
            } else if (mAngles[i] <= -TWO_PI) {
                mAngles[i] += TWO_PI;
            }
        }
        float *transforms = mapTransformBuf();
        for (unsigned int i = 0; i < mNumInstances; i++) {
            float s = sinf(mAngles[i]);
            float c = cosf(mAngles[i]);
            transforms[4 * i + 0] = c * mScale[0];
            transforms[4 * i + 1] = s * mScale[1];
            transforms[4 * i + 2] = -s * mScale[0];
            transforms[4 * i + 3] = c * mScale[1];
        }
        unmapTransformBuf();
    }
    mLastFrameNs = nowNs;
}

void Renderer::render() {
    step();
    glClearColor(0.2f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    draw(mNumInstances);
    checkGlError("Renderer::render");
}


float *Renderer::mapOffsetBuf() {
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_OFFSET]);
    return (float *) glMapBufferRange(GL_ARRAY_BUFFER,
        0, MAX_INSTANCES * 2 * sizeof(float),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
}

void Renderer::unmapOffsetBuf() {
    glUnmapBuffer(GL_ARRAY_BUFFER);
}

float *Renderer::mapTransformBuf() {
    glBindBuffer(GL_ARRAY_BUFFER, mVB[VB_SCALEROT]);
    return (float *) glMapBufferRange(GL_ARRAY_BUFFER,
        0, MAX_INSTANCES * 4 * sizeof(float),
        GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
}

void Renderer::unmapTransformBuf() {
    glUnmapBuffer(GL_ARRAY_BUFFER);
}

void Renderer::draw(unsigned int numInstances) {
		glClear(GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT|GL_COLOR_BUFFER_BIT);
		glClearColor(1.f, 0, 0, 1.f);
    glUseProgram(mProgram);
    glBindVertexArray(mVBState);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, numInstances);
}

bool checkGlError(const char *funcName) {
    GLint err = glGetError();
    if (err != GL_NO_ERROR) {
        ALOGE("GL error after %s(): 0x%08x\n", funcName, err);
        return true;
    }
    return false;
}

GLuint createShader(GLenum shaderType, const char * src) {
    GLuint shader = glCreateShader(shaderType);
    if (!shader) {
        checkGlError("glCreateShader");
        return 0;
    }
    glShaderSource(shader, 1, &src, NULL);

    GLint compiled = GL_FALSE;
    glCompileShader(shader);
    glGetShaderiv(shader, GL_COMPILE_STATUS, & compiled);
    if (!compiled) {
        GLint infoLogLen = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, & infoLogLen);
        if (infoLogLen > 0) {
            GLchar * infoLog = (GLchar * ) malloc(infoLogLen);
            if (infoLog) {
                glGetShaderInfoLog(shader, infoLogLen, NULL, infoLog);
                ALOGE("Could not compile %s shader:\n%s\n",
                    shaderType == GL_VERTEX_SHADER ? "vertex" : "fragment",
                    infoLog);
                free(infoLog);
            }
        }
        glDeleteShader(shader);
        return 0;
    }
    return shader;
}

GLuint createProgram(const char *vtxSrc, const char *fragSrc) {
    GLuint vtxShader = 0;
    GLuint fragShader = 0;
    GLuint program = 0;
    GLint linked = GL_FALSE;

    vtxShader = createShader(GL_VERTEX_SHADER, vtxSrc);
    if (!vtxShader)
        goto exit;

    fragShader = createShader(GL_FRAGMENT_SHADER, fragSrc);
    if (!fragShader)
        goto exit;

    program = glCreateProgram();
    if (!program) {
        checkGlError("glCreateProgram");
        goto exit;
    }
    glAttachShader(program, vtxShader);
    glAttachShader(program, fragShader);

    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, & linked);
    if (!linked) {
        ALOGE("Could not link program");
        GLint infoLogLen = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, & infoLogLen);
        if (infoLogLen) {
            GLchar * infoLog = (GLchar * ) malloc(infoLogLen);
            if (infoLog) {
                glGetProgramInfoLog(program, infoLogLen, NULL, infoLog);
                ALOGE("Could not link program:\n%s\n", infoLog);
                free(infoLog);
            }
        }
        glDeleteProgram(program);
        program = 0;
    }

    exit:
    glDeleteShader(vtxShader);
    glDeleteShader(fragShader);
    return program;
}

static void printGlString(const char *name, GLenum s) {
    const char * v = (const char *) glGetString(s);
    ALOGV("GL %s: %s\n", name, v);
}

static Renderer *g_renderer = NULL;
#define JEx(R, M) extern "C" JNIEXPORT R JNICALL Java_com_ariasaproject_example_HelloWorld_##M 

JEx(void, init)(JNIEnv *env, jobject obj) {
    if (g_renderer) {
        delete g_renderer;
        g_renderer = NULL;
    }

    printGlString("Version", GL_VERSION);
    printGlString("Vendor", GL_VENDOR);
    printGlString("Renderer", GL_RENDERER);
    printGlString("Extensions", GL_EXTENSIONS);

    const char *versionStr = (const char *) glGetString(GL_VERSION);
    if (strstr(versionStr, "OpenGL ES 3.")) {
        g_renderer = new Renderer;
        if(!g_renderer->init())
        {
        		delete g_renderer;
        		g_renderer = NULL;
      			ALOGE("Unsupported OpenGL ES make");
        }
    } else {
        ALOGE("Unsupported OpenGL ES version");
    }
}

JEx(void, resize)(JNIEnv *env, jobject obj, jint width, jint height) {
    if (g_renderer) {
        g_renderer -> resize(width, height);
    }
}

JEx(void, step)(JNIEnv *env, jobject obj) {
    if (g_renderer) {
        g_renderer -> render();
    }
}