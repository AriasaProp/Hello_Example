#include <jni.h>
#include "mainListener.h"
#include "translated_opengles.h"

void main_loop();

#include <android/log.h>
#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, "Hello_Activity", __VA_ARGS__)
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "Hello_Activity", __VA_ARGS__)


#define JEx(R, M) extern "C" JNIEXPORT R JNICALL Java_com_ariasaproject_example_HelloWorld_##M

#include <EGL/egl.h>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <iostream>

std::condition_variable cv;
std::mutex mtx;
std::thread *mthread = nullptr;

int mayorV = 3, minorV = 0;
bool resume = false, pause = false, destroy = false, resize = false, rendered = false, hasSurface = false, mExited = false;
unsigned int width = 0, height = 0;
unsigned int frames = 0, fps = 0;
float deltaTime = 0;


JEx(void, onstart) (JNIEnv *e, jobject o){
	mthread = new std::thread(main_loop);
}

JEx(void, onresume) (JNIEnv *e, jobject o){
	
	resume = true;
	cv.notify_all()
}

JEx(void, surfacecreated) (JNIEnv *e, jobject o){
	
	
}

JEx(void, surfacechanged) (JNIEnv *e, jobject o, jint w, jint h){
	std::unique_lock<std::mutex> u_lck(mtx);
	if (!hasSurface) {
		rendered = true;
		hasSurface = true;
	}
	width = w;
	height = h;
	resize = true;
	cv.notify_all();
	while (!mExited && rendered)
		cv.wait(u_lck);
}

JEx(void, surfacedestroyed) (JNIEnv *e, jobject o){
	hasSurface = false;
	cv.notify_all();
}

JEx(void, onpause) (JNIEnv *e, jobject o, jboolean _finish){
	std::unique_lock<std::mutex> u_lck(mtx);
	pause = true;
	rendered = true;
	cv.notify_all();
	while (!mExited && rendered)
		cv.wait(u_lck);
	if (!_finish) return;
	destroy = true;
	cv.notify_all();
	while (!mExited)
		cv.wait(u_lck);
}

JEx(void, onstop) (JNIEnv *e, jobject o){
	if (mthread->joinable())
		mthread->join();
	delete mthread;
}


#include <chrono>

void main_loop() {
	TranslatedGraphicsFunction *tgf = new tgf_gles();
	//egl env 
	EGLDisplay *mEglDisplay = nullptr;
	EGLSurface *mEglSurface = nullptr;
	EGLConfig *mEglConfig = nullptr;
	EGLContext *mEglContext = nullptr;
	unsigned long
		frameStart = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).count(),
		lastFrameTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).count();

	try {
		unsigned char eglDestroyRequest = 0;
		bool wantRender = false, newContext = true, 
			created = false, lrunning = false, lresize = false, lresume = false, lpause = false;
		while (!destroy) {
			{
				//guard l bool function state
				std::unique_lock<std::mutex> u_lck(mtx);
				// render notify
				if (wantRender) {
					rendered = false;
					wantRender = false;
					mtx.notify_all();
				}
				if (rendered)
					wantRender = true;
				// egl destroy request
				if (mEglSurface && (eglDestroyRequest > 0 || !hasSurface)) {
					eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
					if (!eglDestroySurface(mEglDisplay, mEglSurface)) {
						std::ostringstream ss;
    						ss << "eglDestroySurface failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
						throw (ss.str());
					}
					mEglSurface = nullptr;
					if (mEglContext && (eglDestroyRequest > 1)) {
						if (!eglDestroyContext(mEglDisplay, mEglContext)) {
							std::ostringstream ss;
    							ss << "eglDestroyContext failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
							throw (ss.str());
						}
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
				mtx.notify_all();
				// Ready to draw?
				if (!lrunning || !hasSurface) {
					cv.wait(u_lck);
					continue;
				}
			}
			if (!mEglDisplay) {
				unsigned int temp[2]; // for chaching value output

				mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
				if (mEglDisplay == EGL_NO_DISPLAY || !mEglDisplay) {
					mEglDisplay = null;
					std::ostringstream ss;
    					ss << "eglGetDisplay failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
					throw (ss.str());
				}
				if (eglInitialize(mEglDisplay, temp, 0, temp, 1))
					ALOGV("version EGL " + temp[0] + "." + temp[1]);
				else {
					std::ostringstream ss;
    					ss << "eglInitialize failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
					throw (ss.str());
				}
				if (!mEglConfig) {
					// choose best config
					unsigned int s_configAttribs2[3] = {EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER, EGL_NONE };
					eglChooseConfig(mEglDisplay, s_configAttribs2, 0, null, 0, 0, temp, 0);
					if (!temp[0])
						throw ("No configs match with configSpec");
					const unsigned int j = temp[0];
					EGLConfig configs[j];
					eglChooseConfig(mEglDisplay, s_configAttribs2, 0, configs, 0, configs.length, temp, 0);
					int lastSc = -1, curSc;
					*mEglConfig = configs[0];
					for (EGLConfig config : configs) {
						temp[0] = -1;
						// alpha should 0
						// choose higher depth, stencil, color buffer(rgba)
						curSc = -1;
						for (int attr : {EGL_RENDERABLE_TYPE, EGL_BUFFER_SIZE, EGL_ALPHA_SIZE, EGL_DEPTH_SIZE, EGL_STENCIL_SIZE}) {
							if (eglGetConfigAttrib(mEglDisplay, config, attr, temp, 0)) {
								if (attr == EGL_ALPHA_SIZE)
								temp[0] *= -1;
								curSc += temp[0];
							} else {
								int error;
								while ((error = eglGetError()) != EGL_SUCCESS) {
									std::ostringstream ss;
    									ss << "eglConfigAttribute failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << error;
									throw (ss.str());
								}
							}
						}
						if (curSc > lastSc) {
							lastSc = curSc;
							*mEglConfig = config;
						}
					}
				}
			}
			if (newContext || !mEglSurface) {
				if (newContext) {
					unsigned int attrib_list[3] = {EGL_CONTEXT_CLIENT_VERSION, mayorV, EGL_NONE};
					mEglContext = eglCreateContext(mEglDisplay, mEglConfig, EGL_NO_CONTEXT, attrib_list, 0);
					if (!mEglContext || mEglContext == EGL_NO_CONTEXT) {
						mEglContext = nullptr;
						std::ostringstream ss;
    						ss << "createContext failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
						throw (ss.str());
					}
				}
				mEglSurface = eglCreateWindowSurface(mEglDisplay, mEglConfig, holder, null, 0);
				if (!mEglSurface || mEglSurface == EGL_NO_SURFACE) {
					mEglSurface = nullptr;
					std::ostringstream ss;
    					ss << "Create EGL Surface failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
					throw (ss.str());
				}
				if (!eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext)) {
					std::ostringstream ss;
    					ss << "Make EGL failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
					throw (ss.str());
				}
				if (newContext) {
					Main::create(tgf);

					Main::resize(width, height);
					lresize = false;
					lastFrameTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).count();
					newContext = false;
				}
			}
			if (lresize) {
				eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
				eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext);
				Main::resize(width, height);
			}

			unsigned long time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).count();

			if (lresume) {
				Main::resume();
				time = frameStart = lastFrameTime = 0;
			}
			if (time - frameStart > 1000l) {
				fps = frames;
				frames = 0;
				frameStart = time;
			}

			deltaTime = (time - lastFrameTime) / 1000.f;
			lastFrameTime = time;

			Main::render(deltaTime);

			if (lpause) {
				Main::pause();
				eglDestroyRequest |= 1;
			}
			if (!eglSwapBuffers(mEglDisplay, mEglSurface)) {
				unsigned int error = eglGetError();
				switch (error) {
				case EGL_BAD_DISPLAY:
					eglDestroyRequest |= 4;
					break;
				case 0x300E:
				case EGL_BAD_CONTEXT:
					eglDestroyRequest |= 2;
					break;
				case EGL_BAD_SURFACE:
					eglDestroyRequest |= 1;
					break;
				case EGL_BAD_NATIVE_WINDOW:
					std::ostringstream ss;
    					ss << "eglSwapBuffers returned EGL_BAD_NATIVE_WINDOW. tid=" << std::this_thread::get_id();
					throw (ss.str());
					break;
				default:
					std::ostringstream ss;
    					ss << "eglSwapBuffers failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << error;
					throw (ss.str());
					break;
			}
		}
		frames++;
	} catch (std::string err) {
		ALOGE(err);
	} finally {
		// dispose all resources
		Main::destroy();

		if (mEglSurface) {
			eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
			eglDestroySurface(mEglDisplay, mEglSurface);
			mEglSurface = nullptr;
		}
		if (mEglContext) {
			eglDestroyContext(mEglDisplay, mEglContext);
			mEglContext = nullptr;
		}
		if (mEglDisplay) {
			eglTerminate(mEglDisplay);
			mEglDisplay = nullptr;
		}
		// end thread
		synchronized (this) {
			mExited = true;
			cv.notify_all();
		}
	}
	delete tgf;
}





