package com.learnmedia.activity

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.learnmedia.adapter.VideoTypeAdapter
import com.xoon.learnmedia.R
import com.xoon.learnmedia.databinding.ActivityVideoTypeListBinding

/**
 * Create by Insane
 * time: 2024/07/24
 * desc:
 */
class VideoTypeListActivity : AppCompatActivity() {
    private lateinit var bind: ActivityVideoTypeListBinding
    private val mAdapter by lazy {
        VideoTypeAdapter(this)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        bind = ActivityVideoTypeListBinding.inflate(layoutInflater)
        setContentView(bind.root)

        bind.rvVideo.adapter = mAdapter

    }
}