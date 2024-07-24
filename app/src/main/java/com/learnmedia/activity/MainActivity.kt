package com.learnmedia.activity

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import com.learnmedia.ui.GlPlayer
import com.learnmedia.VideoTypeEnum
import com.learnmedia.VideoTypeListData
import com.xoon.learnmedia.R
import com.xoon.learnmedia.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    private lateinit var bind: ActivityMainBinding
    private var videoType = VideoTypeEnum.DRAW_TRIANGLE

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        bind = ActivityMainBinding.inflate(layoutInflater)
        setContentView(bind.root)

        intent.apply {
            videoType = getSerializableExtra(VideoTypeListData.VIDEO_TYPE_KEY) as? VideoTypeEnum
                ?: VideoTypeEnum.DRAW_TRIANGLE
        }
        bind.glPlayer.setVideoType(videoType)
    }


    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }

}