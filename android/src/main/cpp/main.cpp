#include "mainListener.h"
#include "translated_opengles.h"
#include <android/log.h>
#include <EGL/egl.h>
#include <android/native_window_jni.h>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <sstream>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <chrono>


#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, "Hello_Activity", __VA_ARGS__), throw ("Error print!")
#define ALOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, "Hello_Activity", __VA_ARGS__)

#define JEx(R, M) extern "C" JNIEXPORT R JNICALL Java_com_ariasaproject_example_HelloWorld_##M

std::condition_variable cv;
std::mutex mtx;
std::mutex mtx_guard;
std::thread *mthread = nullptr;

EGLint mayorV = 3, minorV = 0;
bool resume = false, pause = false, destroy = false, resize = false, rendered = false, mExited = false;
EGLint width = 0, height = 0, format = 0;
unsigned int frames = 0, fps = 0;
float deltaTime = 0;
ANativeWindow *window = nullptr;

void main_loop();

JEx(void, onstart) (JNIEnv *e, jobject o) {
	mthread = new std::thread(main_loop);
}

JEx(void, onresume) (JNIEnv *e, jobject o) {
	mtx_guard.lock();
	resume = true;
	cv.notify_all();
	mtx_guard.unlock();
}

JEx(void, surfacecreated) (JNIEnv *e, jobject o, jobject surf){
	window = ANativeWindow_fromSurface(e, surf);
}

JEx(void, surfacechanged) (JNIEnv *e, jobject o, jobject surf, jint w, jint h){
	mtx_guard.lock();
	std::unique_lock<std::mutex> u_lck(mtx);
	width = w;
	height = h;
	resize = true;
	cv.notify_all();
	while (!mExited && rendered)
		cv.wait(u_lck);
	mtx_guard.unlock();
}

JEx(void, surfacedestroyed) (JNIEnv *e, jobject o, jobject surf) {
	mtx_guard.lock();
	ANativeWindow_release(window);
	window = nullptr;
	cv.notify_all();
	mtx_guard.unlock();
}

JEx(void, onpause) (JNIEnv *e, jobject o, jboolean _finish) {
	mtx_guard.lock();
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
	mtx_guard.unlock();
}

JEx(void, onstop) (JNIEnv *e, jobject o) {
	if (mthread->joinable())
		mthread->join();
	delete mthread;
}


void main_loop() {
	std::ostringstream ss;
	TranslatedGraphicsFunction *tgf = new tgf_gles();
	EGLDisplay mEglDisplay = nullptr;
	EGLSurface mEglSurface;
	EGLConfig mEglConfig = nullptr;
	EGLContext mEglContext;
	long frameStart = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count(),
		lastFrameTime= std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();

	try {
		unsigned char eglDestroyRequest = 0;
		bool wantRender = false, newContext = true, 
			created = false, lrunning = false, lresize = false, lresume = false, lpause = false;
		while (!destroy) {
			//guard l bool function state
			std::unique_lock<std::mutex> u_lck(mtx);
			mtx_guard.lock();
			// render notify
			if (wantRender) {
				rendered = false;
				wantRender = false;
				cv.notify_all();
			}
			if (rendered)
				wantRender = true;
			// egl destroy request
			if (mEglSurface && (eglDestroyRequest > 0 || !window)) {
				eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
				if (!eglDestroySurface(mEglDisplay, mEglSurface)) {
					ss.str("");
					ss.clear();
   						ss << "eglDestroySurface failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
					ALOGE("%s", ss.str().c_str());
				}
				mEglSurface = 0;
				if (mEglContext && (eglDestroyRequest > 1)) {
					if (!eglDestroyContext(mEglDisplay, mEglContext)) {
						ss.str("");
						ss.clear();
						ss << "eglDestroyContext failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
						ALOGE("%s", ss.str().c_str());
					}
					mEglContext = NULL;
					newContext = true;
					if (mEglDisplay && (eglDestroyRequest > 3)) {
						eglTerminate(mEglDisplay);
						mEglDisplay = NULL;
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
			mtx_guard.unlock();
			cv.notify_all();
			// Ready to draw?
			if (!lrunning || !window) {
				cv.wait(u_lck);
				continue;
			}
			if (!mEglDisplay) {
				EGLint temp[2]; // for chaching value output
				mEglDisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
				if (mEglDisplay == EGL_NO_DISPLAY || !mEglDisplay) {
					mEglDisplay = NULL;
					ss.str("");
					ss.clear();
    					ss << "eglGetDisplay failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
					ALOGE("%s", ss.str().c_str());
				}
				if (eglInitialize(mEglDisplay, &temp[0], &temp[1])) {
					ss.str("");
					ss.clear();
					ss << "version EGL " << temp[0] << "." << temp[1];
					ALOGV("%s", ss.str().c_str());
				} else {
					ss.str("");
					ss.clear();
    					ss << "eglInitialize failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
					ALOGE("%s", ss.str().c_str());
				}
				if (!mEglConfig) {
					// choose best config
					const EGLint s_configAttribs2[3] = {EGL_COLOR_BUFFER_TYPE, EGL_RGB_BUFFER, EGL_NONE};
					eglChooseConfig(mEglDisplay, &s_configAttribs2[0], nullptr, 0, temp);
					if (temp[0] == 0)
						throw ("No configs match with configSpec");
					const unsigned int j = temp[0];
					EGLConfig configs[j];
					eglChooseConfig(mEglDisplay, &s_configAttribs2[0], &configs[0], j, nullptr);
					int lastSc = -1, curSc;
					mEglConfig = configs[0];
					for (EGLConfig config : configs) {
						temp[0] = -1;
						// alpha should 0
						// choose higher depth, stencil, color buffer(rgba)
						curSc = -1;
						for (EGLint attr : {EGL_RENDERABLE_TYPE, EGL_BUFFER_SIZE, EGL_ALPHA_SIZE, EGL_DEPTH_SIZE, EGL_STENCIL_SIZE}) {
							if (eglGetConfigAttrib(mEglDisplay, config, attr, &temp[0])) {
								if (attr == EGL_ALPHA_SIZE)
									temp[0] *= -1;
								curSc += temp[0];
							} else {
								EGLint error;
								while ((error = eglGetError()) != EGL_SUCCESS) {
									ss.str("");
									ss.clear();
    									ss << "eglConfigAttribute failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << error;
									ALOGE("%s", ss.str().c_str());
								}
							}
						}
						if (curSc > lastSc) {
							lastSc = curSc;
							mEglConfig = config;
						}
					}
				}
			}
			if (newContext || !mEglSurface) {
				if (newContext) {
					const EGLint attrib_list[3] = {EGL_CONTEXT_CLIENT_VERSION, 3 /* may use variables*/, EGL_NONE};
					mEglContext = eglCreateContext(mEglDisplay, mEglConfig, EGL_NO_CONTEXT, attrib_list);
					if (!mEglContext || mEglContext == EGL_NO_CONTEXT) {
						mEglContext = NULL;
						ss.str("");
						ss.clear();
    						ss << "createContext failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
						ALOGE("%s", ss.str().c_str());
					}
				}
				mEglSurface = eglCreateWindowSurface(mEglDisplay, mEglConfig, window, nullptr);
				if (!mEglSurface || mEglSurface == EGL_NO_SURFACE) {
					mEglSurface = NULL;
					ss.str("");
					ss.clear();
    					ss << "Create EGL Surface failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
					ALOGE("%s", ss.str().c_str());
				}
				if (!eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext)) {
					ss.str("");
					ss.clear();
    					ss << "Make EGL failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << eglGetError();
					ALOGE("%s", ss.str().c_str());
				}
				if (newContext) {
					Main::create(tgf);

					Main::resize(width, height);
					lresize = false;
					lastFrameTime = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();
					newContext = false;
				}
			}
			if (lresize) {
				eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
				eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext);
				Main::resize(width, height);
			}
			long time = std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now()).time_since_epoch().count();
			
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
				EGLint error = eglGetError();
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
					ss.str("");
					ss.clear();
    					ss << "eglSwapBuffers returned EGL_BAD_NATIVE_WINDOW. tid=" << std::this_thread::get_id();
					ALOGE("%s", ss.str().c_str());
					break;
				default:
					ss.str("");
					ss.clear();
    					ss << "eglSwapBuffers failed: 0x" << std::setfill('0') << std::setw(8) << std::hex << error;
					ALOGE("%s", ss.str().c_str());
					break;
			}
		}
		frames++;
	} catch (...) {
		ALOGE("fall thru error!");
	}
	// dispose all resources
	Main::destroy();
	if (mEglSurface) {
		eglMakeCurrent(mEglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglDestroySurface(mEglDisplay, mEglSurface);
		mEglSurface = NULL;
	}
	if (mEglContext) {
		eglDestroyContext(mEglDisplay, mEglContext);
		mEglContext = NULL;
	}
	if (mEglDisplay) {
		eglTerminate(mEglDisplay);
		mEglDisplay = NULL;
	}
	// end thread
	mtx_guard.lock();
	mExited = true;
	cv.notify_all();
	mtx_guard.unlock();
	
	//delete tgf;
}







