package com.learnmedia

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.TextView
import com.xoon.learnmedia.R
import com.xoon.learnmedia.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {
    private val yuvPlayer by lazy<GlPlayer> {
        findViewById(R.id.gl_player)
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        yuvPlayer.setVideoType()
    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String

    companion object {
        // Used to load the 'native-lib' library on application startup.
        init {
            System.loadLibrary("native-lib")
        }
    }
}