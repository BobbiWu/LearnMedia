package com.learnmedia

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.util.Log
import android.view.Surface
import android.view.SurfaceHolder
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10


class GlPlayer(context: Context?, attrs: AttributeSet?) : GLSurfaceView(context, attrs), Runnable,
    SurfaceHolder.Callback, GLSurfaceView.Renderer {
    companion object {
        private val TAG = "GlPlayer"
    }


    fun setVideoType() {
        setRenderer(this)
        Log.d(TAG, "setVideoType")
    }

    override fun run() {
        //绘制
//        drawTriangle(holder.surface)
    }

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        Log.d(TAG, "onSurfaceCreated")
        drawTriangle(holder.surface)

//        Thread(this).start()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        Log.d(TAG, "onSurfaceChanged")

    }

    override fun onDrawFrame(gl: GL10?) {

    }


    external fun drawTriangle(surface: Surface?)
}