#include <jni.h>

#include "mainListener.h"
#include "translated_opengles.h"

#define native(R, M) extern "C" JNIEXPORT R JNICALL Java_com_ariasaproject_example_HelloWorld_ApplicationListener_##M

native(void, create) (JNIEnv *e, jobject o) {
	Main::create(new tgf_gles());
}
native(void, resume) (JNIEnv *e, jobject o) {
	Main::resume();
}
native(void, resize) (JNIEnv *e, jobject o, jint w, jint h) {
	Main::resize(w, h);
}
native(void, render) (JNIEnv *e, jobject o, jfloat d) {
	Main::render(d);
}
native(void, pause) (JNIEnv *e, jobject o) {
	Main::pause();
}
native(void, destroy) (JNIEnv *e, jobject o) {
	Main::destroy();
}

