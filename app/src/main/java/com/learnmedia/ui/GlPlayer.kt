package com.learnmedia.ui

import android.annotation.SuppressLint
import android.content.Context
import android.content.res.AssetManager
import android.graphics.Bitmap
import android.graphics.drawable.BitmapDrawable
import android.opengl.GLSurfaceView
import android.util.AttributeSet
import android.util.Log
import android.view.Surface
import android.view.SurfaceHolder
import com.learnmedia.VideoTypeEnum
import com.xoon.learnmedia.R
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GlPlayer(context: Context?, attrs: AttributeSet?) : GLSurfaceView(context, attrs), Runnable,
    SurfaceHolder.Callback, GLSurfaceView.Renderer {
    private val TAG = "GlPlayer"
    private var videoType = VideoTypeEnum.DRAW_TRIANGLE

    fun setVideoType(videoType: VideoTypeEnum) {
        this.videoType = videoType
        Log.d(TAG, "videoType:$videoType")
    }

    override fun surfaceCreated(holder: SurfaceHolder) {
        Log.d(TAG, "surfaceCreated")
        Thread(this).start()
    }

    override fun surfaceDestroyed(holder: SurfaceHolder) {
    }

    override fun surfaceChanged(holder: SurfaceHolder, format: Int, w: Int, h: Int) {
        surfaceWidth = w
        surfaceHeight = h
    }

    @SuppressLint("UseCompatLoadingForDrawables")
    override fun run() {
        Log.d(TAG, "run")

        when (videoType) {
            VideoTypeEnum.DRAW_TRIANGLE -> drawTriangle(holder.surface)
            VideoTypeEnum.SIMPLE_YUV -> {
                val assetManager = context?.assets
                loadYue(holder.surface, assetManager)
            }

            VideoTypeEnum.NO_FILTER_YUV -> TODO()
            VideoTypeEnum.GRAY_FILTER_YUV ->{
                val assetManager = context?.assets
                loadGradFilterYue(holder.surface,FilterType.GRAY,assetManager)
            }
            VideoTypeEnum.OPPO_FILTER_YUV -> TODO()
            VideoTypeEnum.DIVIDE_TO_2_YUV -> TODO()
            VideoTypeEnum.DIVIDE_TO_4_YUV -> TODO()
            VideoTypeEnum.SOUL_FLY_OFF_YUV -> TODO()
            VideoTypeEnum.GAUSS_BLUR_YUV -> TODO()
            VideoTypeEnum.DRAW_TRIANGLE_UNIFORM -> drawTriangleUniform(holder.surface)
            VideoTypeEnum.DRAW_TRIANGLE_WITH_COLOR_PASS -> drawTriangleWithColorPass(holder.surface)
            VideoTypeEnum.DRAW_TRIANGLE_VBO -> drawTriangleWithBufferObj(holder.surface)
            VideoTypeEnum.DRAW_TRIANGLE_EBO -> drawTriangleWithEBO(holder.surface)
            VideoTypeEnum.DRAW_TWO_TRIANGLE -> TODO()
            VideoTypeEnum.DRAW_LINE -> TODO()
            VideoTypeEnum.DRAW_TEXTURE_MAX -> {
                val bitmap =
                    (resources.getDrawable(R.drawable.liyingai) as BitmapDrawable).bitmap
                val bitmapTwo =
                    (resources.getDrawable(R.drawable.shiyuanmeili2) as BitmapDrawable).bitmap
                drawTexture(bitmap, bitmapTwo, holder.surface)
//                val bpLiyingai1 =
//                    (resources.getDrawable(R.drawable.liyingai) as BitmapDrawable).bitmap
//                val bpShiyuanmeili1 =
//                    (resources.getDrawable(R.drawable.shiyuanmeili2) as BitmapDrawable).bitmap
//                drawTexture(bpLiyingai1, bpShiyuanmeili1, holder.surface)
//                break
            }

            VideoTypeEnum.DRAW_3D_TEXTURE -> TODO()
            VideoTypeEnum.DRAW_3D_CUBE_TEXTURE -> TODO()
            VideoTypeEnum.DRAW_GRADIENT_COLOR_CUBE_TEXTURE -> TODO()
            VideoTypeEnum.DRAW_CUBES_MOVE_CAMERA -> TODO()
        }
        Log.d(TAG, "loadYuv")
    }


    internal interface FilterType {
        companion object {
            /**
             * 没有滤镜
             */
            const val NONE: Int = 0

            /**
             * 反色滤镜
             */
            const val OPPO: Int = 1

            /**
             * 反色灰度图滤镜
             */
            const val OPPO_GRAY: Int = 2

            /**
             * 灰度图滤镜
             */
            const val GRAY: Int = 3

            /**
             * 二分镜
             */
            const val DIVIDE_TO_2: Int = 4

            /**
             * 四分镜
             */
            const val DIVIDE_TO_4: Int = 5
        }
    }


    override fun onSurfaceCreated(gl: GL10, config: EGLConfig) {
    }

    private var surfaceWidth = 0
    private var surfaceHeight = 0

    init {
        setRenderer(this)
    }

    override fun onSurfaceChanged(gl: GL10, width: Int, height: Int) {
        surfaceWidth = width
        surfaceHeight = height
    }

    override fun onDrawFrame(gl: GL10) {
    }


    /**
     * 绘制三角形
     */
    external fun drawTriangle(surface: Any?)

    /**
     * 绘制 uniform 三角形
     */
    external fun drawTriangleUniform(surface: Any?)

    /**
     * 绘制顶点属性三角形
     */
    external fun drawTriangleWithColorPass(surface: Any?)

    /**
     * 使用缓冲对象绘制三角形
     */
    external fun drawTriangleWithBufferObj(surface: Any?)

    /**
     * 使用EBO绘制三角形
     */
    external fun drawTriangleWithEBO(surface: Any?)

    /**
     * 绘制纹理
     */
    external fun drawTexture(bitmap: Bitmap, bitmapTwo: Bitmap, surface: Any?)

    /**
     * 加载 yuv
     */
    external fun loadYue(surface: Any?, assetManager: AssetManager?)


    /**
     * 加载灰色滤镜 YUV FILTER
     */

    external fun loadGradFilterYue(surface: Surface?, type: Int, assetManager: AssetManager?)

    companion object {
        private const val PATH = "/sdcard/video1_640_272.yuv"
    }

}
