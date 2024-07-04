#include <jni.h>
#include <string>
#include <android/native_window_jni.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <android/log.h>

#define BITMAP_INFO_LOGD(...) __android_log_print(ANDROID_LOG_WARN,"learnMedia",__VA_ARGS__)


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
    //1. 获取原始窗口
    ANativeWindow *nwin = ANativeWindow_fromSurface(env, surface);

    //获取OpenGL es渲染目标Display，EGL_DEFAULT_DISPLAY表示默认的Display
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display != EGL_NO_DISPLAY) {
        BITMAP_INFO_LOGD("egl display failed");
        return;
    }

    //2.初始化egl Diaplay的连接，后两个参数是指针，是分别用来返回EGL主次版本号
    EGLBoolean init = eglInitialize(display, 0, 0);
    if (init != EGL_TRUE) {
        BITMAP_INFO_LOGD("eglInitialize failed");
        return;
    }
}