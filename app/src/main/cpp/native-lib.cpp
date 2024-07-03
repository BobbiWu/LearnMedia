#include <jni.h>
#include <string>


extern "C"
JNIEXPORT jstring JNICALL
Java_com_learnmedia_MainActivity_stringFromJNI(JNIEnv *env, jobject thiz) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

//绘制三角形

extern "C"
JNIEXPORT void JNICALL
Java_com_learnmedia_GlPlayer_drawTriangle(JNIEnv *env, jobject thiz, jobject surface) {

}