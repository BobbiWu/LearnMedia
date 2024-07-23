#include <jni.h>
#include <string>
#include <android/log.h>
#include <android/native_window_jni.h>
#include <EGL/egl.h>
#include <GLES3/gl3.h>
#include <string.h>
#include <android/bitmap.h>
#include <unistd.h>
#include "FragmentShader.h"
#include "Shader.h"
#include <vector>


#define LOGD(...) __android_log_print(ANDROID_LOG_WARN,"learnMedia",__VA_ARGS__)


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
//1.获取原始窗口
    //be sure to use ANativeWindow_release()
    // * when done with it so that it doesn't leak.
    ANativeWindow *nwin = ANativeWindow_fromSurface(env, surface);
    //获取Display
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display == EGL_NO_DISPLAY) {
        LOGD("egl display failed");
        return;
    }
    //2.初始化egl，后两个参数为主次版本号
    if (EGL_TRUE != eglInitialize(display, 0, 0)) {
        LOGD("eglInitialize failed");
        return;
    }

    //3.1 surface配置，可以理解为窗口
    EGLConfig eglConfig;
    EGLint configNum;
    EGLint configSpec[] = {
            EGL_RED_SIZE, 4,
            EGL_GREEN_SIZE, 4,
            EGL_BLUE_SIZE, 4,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_NONE
    };

    if (EGL_TRUE != eglChooseConfig(display, configSpec, &eglConfig, 1, &configNum)) {
        LOGD("eglChooseConfig failed");
        return;
    }

//    BITMAP_INFO_LOGD("eglChooseConfig eglConfig:" + eglConfig);

    //3.2创建surface(egl和NativeWindow进行关联。最后一个参数为属性信息，0表示默认版本)
    EGLSurface winSurface = eglCreateWindowSurface(display, eglConfig, nwin, 0);
    if (winSurface == EGL_NO_SURFACE) {
        LOGD("eglCreateWindowSurface failed");
        return;
    }

    //4 创建关联上下文
    const EGLint ctxAttr[] = {
            EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE
    };
    //EGL_NO_CONTEXT表示不需要多个设备共享上下文
    EGLContext context = eglCreateContext(display, eglConfig, EGL_NO_CONTEXT, ctxAttr);
    if (context == EGL_NO_CONTEXT) {
        LOGD("eglCreateContext failed");
        return;
    }
    //将egl和opengl关联
    //两个surface一个读一个写。第二个一般用来离线渲染？
    if (EGL_TRUE != eglMakeCurrent(display, winSurface, winSurface, context)) {
        LOGD("eglMakeCurrent failed");
        return;
    }

    Shader shader(vertexSimpleShape,fragSimpleShape);
    shader.use();




    static float triangleVer[] = {
            0.8f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.8f, 0.0f,
    };

//    GLuint apos = static_cast<GLuint>(glGetAttribLocation(program, "aPosition"));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, triangleVer);
    glEnableVertexAttribArray(0);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    //窗口显示，交换双缓冲区
    eglSwapBuffers(display, winSurface);

    shader.release();

}