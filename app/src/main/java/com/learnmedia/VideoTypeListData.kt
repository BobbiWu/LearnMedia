package com.learnmedia

import com.learnmedia.model.VideoTypeVo

/**
 * Create by Insane
 * time: 2024/07/24
 * desc:
 */
object VideoTypeListData {
    const val VIDEO_TYPE_KEY = "VideoType"

    val videoTypeList = mutableListOf<VideoTypeVo>().apply {
        add(VideoTypeVo(VideoTypeEnum.DRAW_TRIANGLE, "绘制三角形"))
        add(VideoTypeVo(VideoTypeEnum.DRAW_TRIANGLE_UNIFORM, "通过uniform绘制三角形"))
        add(VideoTypeVo(VideoTypeEnum.DRAW_TRIANGLE_WITH_COLOR_PASS, "通过顶点属性绘制三角形"))
        add(VideoTypeVo(VideoTypeEnum.DRAW_TRIANGLE_VBO, "使用缓冲对象绘制三角形"))
    }
}