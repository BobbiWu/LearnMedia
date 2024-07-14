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
    /**        此处开始EGL的配置              **/

    //1. 获取原始窗口
    ANativeWindow *nwin = ANativeWindow_fromSurface(env, surface);

    //获取OpenGL es渲染目标Display，EGL_DEFAULT_DISPLAY表示默认的Display
    EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    if (display != EGL_NO_DISPLAY) {
        LOGD("egl display failed");
        return;
    }

    //2.初始化egl Diaplay的连接，后两个参数是指针，是分别用来返回EGL主次版本号
    EGLBoolean init = eglInitialize(display, 0, 0);
    if (init != EGL_TRUE) {
        LOGD("eglInitialize failed");
        return;
    }

    //返回的EGL帧缓存配置
    EGLConfig eglConfig;
    //配置数量
    EGLint configNum;

    //期望的EGL帧缓存配置列表,配置为一个key一个value的形式，以下的EGL_RED_SIZE、EGL_GREEN_SIZE、EGL_BLUE_SIZE分别表示EGL帧缓冲中的颜色缓冲一个颜色通道用多少位表示。
    //指定EGL surface类型
    EGLint configSpec[] = {
            EGL_RED_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_BLUE_SIZE, 8,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_NONE
    };

    //返回一个和期望的EGL帧缓存配置列表configSpec匹配的EGL帧缓存配置列表，存储在eglConfig中
    if (eglChooseConfig(display, configSpec, &eglConfig, 1, &configNum) != EGL_TRUE) {
        LOGD("eglChooseConfig failed");
        return;
    }

    //通过egl和NativeWindow以及EGL帧缓冲配置创建EGLSurface。最后一个参数为属性信息，0表示不需要属性)
    EGLSurface winSurface = eglCreateWindowSurface(display, eglConfig, nwin, 0);
    if (winSurface == EGL_NO_SURFACE) {
        LOGD("eglCreateWindowSurface failed");
        return;
    }

    //渲染上下文EGLContext关联的帧缓冲配置列表，EGL_CONTEXT_CLIENT_VERSION表示这里是配置EGLContext的版本，
    const EGLint ctxSpec[] = {
            EGL_CONTEXT_CLIENT_VERSION, 3,
            EGL_NONE
    };

    //通过Display和上面获取到的的EGL帧缓存配置列表创建一个EGLContext， EGL_NO_CONTEXT表示不需要多个设备共享上下文
    EGLContext context = eglCreateContext(display, eglConfig, EGL_NO_CONTEXT, ctxSpec);
    if (context == EGL_NO_CONTEXT) {
        LOGD("eglCreateContext failed");
        return;
    }

    //将EGLContext和当前线程以及draw和read的EGLSurface关联，关联之后，当前线程就成为了OpenGL es的渲染线程
    if (eglMakeCurrent(display, winSurface, winSurface, context) != EGL_TRUE) {
        LOGD("eglMakeCurrent failed");
        return;
    }

    /**        此处结束EGL的配置              **/

    /**        此处开始加载着色器程序               **/
    GLint vsh = initShader(vertexSimpleShape, GL_VERTEX_SHADER);
    GLint fsh = initShader(fragSimpleShape, GL_FRAGMENT_SHADER);


    GLint program = glCreateProgram();
    if (program == 0) {
        LOGD("glCreateProgram failed");
        return;
    }


    glAttachShader(program, vsh);
    glAttachShader(program, fsh);


    glLinkProgram(program);
    GLint status = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == 0) {
        LOGD("glLinkProgram failed");
        return;
    }
    LOGD("glLinkProgram success");

    glUseProgram(program);

    /**        此处加载着色器程序结束              **/


    /**        此处开始将数据传入图形渲染管线              **/
    static float triangleVer[] = {
            0.8f, -0.8f, 0.0f,
            -0.8f, -0.8f, 0.0f,
            0.0f, 0.8f, 0.0f,
    };
   //顶点坐标传到变量“aPosition”中，所以先指定接收的变量名
    GLuint apos = static_cast<GLuint>(glGetAttribLocation(program, "aPosition"));
    glEnableVertexAttribArray(apos);
    //stride：步长，一个重要概念，表示前一个顶点属性的起始位置到下一个顶点属性的起始位置在数组中有多少字节。如果传0，则说明顶点属性数据是紧密挨着的
    glVertexAttribPointer(apos, 3, GL_FLOAT, GL_FALSE, 0, triangleVer);

    /**        此处结束将数据传入图形渲染管线              **/

    /**        此处开始将图像渲染到屏幕              **/

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

    eglSwapBuffers(display, winSurface);

    /**        此处结束图像渲染              **/


}