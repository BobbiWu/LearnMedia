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


//绘制三角形
extern "C"
JNIEXPORT void JNICALL
Java_com_learnmedia_ui_GlPlayer_drawTriangle(JNIEnv *env, jobject thiz, jobject surface) {
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

    Shader shader(vertexSimpleShape, fragSimpleUniform);
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

/**
 * 绘制 uniform 三角形
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_learnmedia_ui_GlPlayer_drawTriangleUniform(JNIEnv *env, jobject thiz, jobject surface) {
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

    Shader shader(vertexSimpleUniform, fragSimpleUniform);
    int program = shader.use();


    static float triangleVer[] = {
            0.8f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.8f, 0.0f,
    };

    static float color[] = {
            1.0f, 0.5f, 0.5f, 1.0f
    };

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, triangleVer);
    glEnableVertexAttribArray(0);

    //获取到uTextColor在着色器程序中的location
    int colorLocation = glGetUniformLocation(program, "uTextColor");
    //通过location去传入一个color向量
    glUniform4fv(colorLocation, 1, color);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    //窗口显示，交换双缓冲区
    eglSwapBuffers(display, winSurface);

    shader.release();

}

/**
 * 绘制顶点属性三角形
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_learnmedia_ui_GlPlayer_drawTriangleWithColorPass(JNIEnv *env, jobject thiz,
                                                          jobject surface) {
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

    Shader shader(vertexSimpleShapeWithColor, fragSimpleShapeWithColor);
    int program = shader.use();


    static float triangleVerWithColor[] = {
            0.0f, 0.8f, 0.0f,//顶点
            1.0, 0.0, 0.0,//颜色

            -0.8f, -0.8f, 0.0f,//顶点
            0.0, 1.0, 0.0,//颜色

            0.8f, -0.8f, 0.0f,//顶点
            0.0, 0.0, 1.0,//颜色
    };


    static float triangleVer[] = {
            0.8f, 0.0f, 0.0f,
            0.0f, 0.0f, 0.0f,
            0.0f, 0.8f, 0.0f,
    };

    static float colors[] = {
            1.0, 0.0, 0.0,//颜色
            0.0, 1.0, 0.0,//颜色
            0.0, 0.0, 1.0,//颜色
    };

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, triangleVerWithColor);
    //解析颜色数据
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, triangleVerWithColor + 3);


//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 12, triangleVer);
//    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 12, colors);


    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);
    //窗口显示，交换双缓冲区
    eglSwapBuffers(display, winSurface);

    shader.release();

}


/**
 * 使用缓冲对象绘制三角形
 */
extern "C"
JNIEXPORT void JNICALL
Java_com_learnmedia_ui_GlPlayer_drawTriangleWithBufferObj(JNIEnv *env, jobject thiz,
                                                          jobject surface) {
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

    Shader shader(vertexSimpleShapeWithColor, fragSimpleShapeWithColor);
    int program = shader.use();



    static float triangleVerWithColor[] = {
            0.0f, 0.8f, 0.0f,//顶点
            1.0, 0.0, 0.0,//颜色
            -0.8f, -0.8f, 0.0f,//顶点
            0.0, 1.0, 0.0,//颜色
            0.8f, -0.8f, 0.0f,//顶点
            0.0, 0.0, 1.0,//颜色
    };



    //定义vbo的id数组，因为可能需要创建多个vbo
    unsigned int VBOs[1];
    //创建vbo，将创建好的vbo的id存放在VBOs数组中
    glGenBuffers(1, VBOs);
    //此时上下文绑定VBOs[0]对应的vbo缓冲
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    //将顶点数据存入vbo的缓冲区中
    glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVerWithColor), triangleVerWithColor, GL_STATIC_DRAW);
    //指定如何解析顶点属性数组，注意这里最后一个参数传的不是原数组地址，而是数据再vbo缓冲区中的相对地址
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 24, (void*)0);
    //关键点就是最后参数传地址偏移量,因为第二个属性是从第4个元素开始的，即便偏移了3个浮点数元素，所以地址指针是(void*)(3*4)
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 24, (void*)(3*4));
    //打开着色器中layout为0的输入变量
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    //清屏
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    //绘制三角形
    glDrawArrays(GL_TRIANGLES, 0, 3);
    //窗口显示，交换双缓冲区
    eglSwapBuffers(display, winSurface);
    //解绑VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    //删除VBO，即清空缓冲区
    glDeleteBuffers(1, VBOs);
    //释放着色器程序对象
    glDeleteProgram(program);
    shader.release();
}