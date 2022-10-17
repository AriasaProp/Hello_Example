#include <jni.h>


extern "C" jstring Java_com_ariasaproject_example_HelloWorld_helloJNI(JNIEnv *e, jclass clazz)
{
		return e->NewStringUTF("Hello there, i'm from native c++!");
}
