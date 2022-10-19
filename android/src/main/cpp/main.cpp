#include <jni.h>
#include <thread>
#include <mutex>

#include "mainListener.h"
#include "translated_opengles.h"

#define JEx(R, M) extern "C" JNIEXPORT R JNICALL Java_com_ariasaproject_example_HelloWorld_##M

JEx(void, create) (JNIEnv *e, jobject o) {
	Main::create(new tgf_gles());
}
JEx(void, resume) (JNIEnv *e, jobject o) {
	Main::resume();
}
JEx(void, resize) (JNIEnv *e, jobject o, jint w, jint h) {
	Main::resize(w, h);
}
JEx(void, render) (JNIEnv *e, jobject o, jfloat d) {
	Main::render(d);
}
JEx(void, pause) (JNIEnv *e, jobject o) {
	Main::pause();
}
JEx(void, destroy) (JNIEnv *e, jobject o) {
	Main::destroy();
}

int mayorV, minorV;
bool resume = false, pause = false, destroy = false, resize = false, rendered = false,
        hasSurface = false, mExited = false;
int width = 0, height = 0;
/*
long frameStart = System.currentTimeMillis(), lastFrameTime = System.currentTimeMillis();
int frames, fps;
float deltaTime = 0;
*/
#include <EGL/egl.h>
std::mutex mtx;
void main_loop() {
	//egl env 
  EGLDisplay *mEglDisplay = nullptr;
  EGLSurface *mEglSurface = nullptr;
  EGLConfig *mEglConfig = nullptr;
  EGLContext *mEglContext = nullptr;
	
	try {
		unsigned char eglDestroyRequest = 0;
		bool wantRender=false, newContext=true, 
		created = false, lrunning=false, lresize=false,lresume=false,lpause=false;
		while (!destroy) {
			//guard l bool funct state
			mtx.lock();
			// render notify
      if (wantRender) {
          rendered = false;
          wantRender = false;
          notifyAll();
      }
      if (rendered)
          wantRender = true;
      // egl destroy request
      if (mEglSurface && (eglDestroyRequest > 0 || !hasSurface)) {
          eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
          if (!eglDestroySurface(mEglDisplay, mEglSurface))
              throw ("eglDestroySurface failed: " + Integer.toHexString(eglGetError()));
          mEglSurface = nullptr;
          if (mEglContext && (eglDestroyRequest > 1)) {
              if (!eglDestroyContext(mEglDisplay, mEglContext))
                  throw ("eglDestroyContext failed: " + Integer.toHexString(eglGetError()));
              mEglContext = nullptr;
              newContext = true;
              if (mEglDisplay && (eglDestroyRequest > 3)) {
                  eglTerminate(mEglDisplay);
                  mEglDisplay = nullptr;
              }
          }
          eglDestroyRequest = 0;
      }
      // end destroy request

      lresize = resize;
      if (resize)
          resize = false;
      if (lpause)
          lrunning = false;
      lpause = pause;
      if (pause)
          pause = false;
      lresume = resume;
      if (resume) {
          resume = false;
          lrunning = true;
      }
      // Ready to draw?
      if (!lrunning || !hasSurface) {
          wait();
          continue;
      }
			mtx.unlock();
		}
		
	} catch (...) {
		
	}
	
}



/*
    // main loop
    @Override
    public void run() {
        EGLDisplay mEglDisplay = null;
        EGLSurface mEglSurface = null;
        EGLConfig mEglConfig = null;
        EGLContext mEglContext = null;
        try {
            byte eglDestroyRequest = 0;// to destroy egl surface, egl contex, egl display, ?....
            boolean wantRender = false, newContext = true, // indicator
                    created = false, lrunning = true, lresize, lresume = false, lpause = false;// on running state
            while (!destroy) {
                synchronized (this) {
                    // render notify
                    if (wantRender) {
                        rendered = false;
                        wantRender = false;
                        notifyAll();
                    }
                    if (rendered)
                        wantRender = true;
                    // egl destroy request
                    if (mEglSurface != null && (eglDestroyRequest > 0 || !hasSurface)) {
                        EGL14.eglMakeCurrent(mEglDisplay, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_CONTEXT);
                        if (!EGL14.eglDestroySurface(mEglDisplay, mEglSurface))
                            throw new RuntimeException("eglDestroySurface failed: " + Integer.toHexString(EGL14.eglGetError()));
                        mEglSurface = null;
                        if (mEglContext != null && (eglDestroyRequest > 1)) {
                            if (!EGL14.eglDestroyContext(mEglDisplay, mEglContext))
                                throw new RuntimeException("eglDestroyContext failed: " + Integer.toHexString(EGL14.eglGetError()));
                            mEglContext = null;
                            newContext = true;
                            if (mEglDisplay != null && (eglDestroyRequest > 3)) {
                                EGL14.eglTerminate(mEglDisplay);
                                mEglDisplay = null;
                            }
                        }
                        eglDestroyRequest = 0;
                    }
                    // end destroy request

                    lresize = resize;
                    if (resize)
                        resize = false;
                    if (lpause)
                        lrunning = false;
                    lpause = pause;
                    if (pause)
                        pause = false;
                    lresume = resume;
                    if (resume) {
                        resume = false;
                        lrunning = true;
                    }
                    // Ready to draw?
                    if (!lrunning || !hasSurface) {
                        wait();
                        continue;
                    }
                }

                if (mEglDisplay == null) {
                    final int[] temp = new int[2]; // for chaching value output

                    mEglDisplay = EGL14.eglGetDisplay(EGL14.EGL_DEFAULT_DISPLAY);
                    if (mEglDisplay == EGL14.EGL_NO_DISPLAY || mEglDisplay == null) {
                        mEglDisplay = null;
                        throw new RuntimeException("eglGetDisplay failed " + Integer.toHexString(EGL14.eglGetError()));
                    }
                    if (EGL14.eglInitialize(mEglDisplay, temp, 0, temp, 1))
                        Log.i(TAG, "version EGL " + temp[0] + "." + temp[1]);
                    else
                        throw new RuntimeException("eglInitialize failed " + Integer.toHexString(EGL14.eglGetError()));

                    if (mEglConfig == null) {
                        // choose best config
                        final int[] s_configAttribs2 = {EGL14.EGL_COLOR_BUFFER_TYPE, EGL14.EGL_RGB_BUFFER, EGL14.EGL_NONE };
                        EGL14.eglChooseConfig(mEglDisplay, s_configAttribs2, 0, null, 0, 0, temp, 0);
                        if (temp[0] <= 0)
                            throw new IllegalArgumentException("No configs match with configSpec");
                        EGLConfig[] configs = new EGLConfig[temp[0]];
                        EGL14.eglChooseConfig(mEglDisplay, s_configAttribs2, 0, configs, 0, configs.length, temp, 0);
                        int lastSc = -1, curSc;
                        mEglConfig = configs[0];
                        for (EGLConfig config : configs) {
                            temp[0] = -1;
                            // alpha should 0
                            // choose higher depth, stencil, color buffer(rgba)
                            curSc = -1;
                            for (int attr : new int[]{EGL14.EGL_RENDERABLE_TYPE, EGL14.EGL_BUFFER_SIZE, EGL14.EGL_ALPHA_SIZE, EGL14.EGL_DEPTH_SIZE, EGL14.EGL_STENCIL_SIZE}) {
                                if (EGL14.eglGetConfigAttrib(mEglDisplay, config, attr, temp, 0)) {
                                    if (attr == EGL14.EGL_ALPHA_SIZE)
                                        temp[0] *= -1;
                                    curSc += temp[0];
                                } else {
                                    int error;
                                    while ((error = EGL14.eglGetError()) != EGL14.EGL_SUCCESS)
                                        Log.e(TAG, String.format("EglConfigAttribute : EGL error: 0x%x", error));
                                }
                            }
                            if (curSc > lastSc) {
                                lastSc = curSc;
                                mEglConfig = config;
                            }
                        }
                    }
                }
                if (newContext || mEglSurface == null) {
                    if (newContext) {
                        final int[] attrib_list = {EGL14.EGL_CONTEXT_CLIENT_VERSION, mayorV, EGL14.EGL_NONE};
                        mEglContext = EGL14.eglCreateContext(mEglDisplay, mEglConfig, EGL14.EGL_NO_CONTEXT, attrib_list, 0);
                        if (mEglContext == null || mEglContext == EGL14.EGL_NO_CONTEXT) {
                            mEglContext = null;
                            throw new RuntimeException("createContext failed: " + Integer.toHexString(EGL14.eglGetError()));
                        }
                    }
                    mEglSurface = EGL14.eglCreateWindowSurface(mEglDisplay, mEglConfig, holder, null, 0);
                    if (mEglSurface == null || mEglSurface == EGL14.EGL_NO_SURFACE) {
                        mEglSurface = null;
                        throw new RuntimeException("Create EGL Surface failed: " + Integer.toHexString(EGL14.eglGetError()));
                    }
                    if (!EGL14.eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext))
                        throw new RuntimeException("Make EGL failed: " + Integer.toHexString(EGL14.eglGetError()));

                    if (newContext) {
                  			create();
                       
                        resize(width, height);
                        lresize = false;
                        lastFrameTime = System.currentTimeMillis();
                        newContext = false;
                    }
                }
                if (lresize) {
                    EGL14.eglMakeCurrent(mEglDisplay, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_CONTEXT);
                    EGL14.eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext);
                    resize(width, height);
                }

                long time = System.currentTimeMillis();

                if (lresume) {
                    resume();
                    time = frameStart = lastFrameTime = 0;
                }
                if (time - frameStart > 1000l) {
                    fps = frames;
                    frames = 0;
                    frameStart = time;
                }
                deltaTime = (time - lastFrameTime) / 1000f;
                lastFrameTime = time;

                render(deltaTime);
                
                if (lpause) {
                    pause();
                    eglDestroyRequest |= 1;
                }
                if (!EGL14.eglSwapBuffers(mEglDisplay, mEglSurface)) {
                    int error = EGL14.eglGetError();
                    switch (error) {
                        case EGL14.EGL_BAD_DISPLAY:
                            eglDestroyRequest |= 4;
                            break;
                        case 0x300E:
                        case EGL14.EGL_BAD_CONTEXT:
                            eglDestroyRequest |= 2;
                            break;
                        case EGL14.EGL_BAD_SURFACE:
                            eglDestroyRequest |= 1;
                            break;
                        case EGL14.EGL_BAD_NATIVE_WINDOW:
                            Log.e(TAG, "eglSwapBuffers returned EGL_BAD_NATIVE_WINDOW. tid=" + Thread.currentThread().getId());
                            break;
                        default:
                            Log.e(TAG, "eglSwapBuffers failed: " + Integer.toHexString(EGL14.eglGetError()));
                    }
                }
                frames++;
            }
        } catch (Throwable e) {
            // fall thru and exit normally
            for (StackTraceElement s : e.getStackTrace()) {
                Log.e(TAG, s.toString());
            }
            Log.e(TAG, "error " + e.getMessage());
        } finally {
            // dispose all resources
            destroy();

            if (mEglSurface != null) {
                EGL14.eglMakeCurrent(mEglDisplay, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_SURFACE, EGL14.EGL_NO_CONTEXT);
                EGL14.eglDestroySurface(mEglDisplay, mEglSurface);
                mEglSurface = null;
            }
            if (mEglContext != null) {
                EGL14.eglDestroyContext(mEglDisplay, mEglContext);
                mEglContext = null;
            }
            if (mEglDisplay != null) {
                EGL14.eglTerminate(mEglDisplay);
                mEglDisplay = null;
            }
            // end thread
            synchronized (this) {
                mExited = true;
                notifyAll();
            }
        }
    }
*/