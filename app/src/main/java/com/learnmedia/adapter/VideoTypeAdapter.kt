package com.learnmedia.adapter

import android.content.Context
import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.learnmedia.VideoTypeListData
import com.learnmedia.activity.MainActivity
import com.xoon.learnmedia.R

/**
 * Create by Insane
 * time: 2024/07/24
 * desc:
 */
class VideoTypeAdapter(val context: Context) :
    RecyclerView.Adapter<VideoTypeAdapter.VideoTypeViewHolder>() {
    inner class VideoTypeViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView) {
        val textView: TextView? = itemView.findViewById(R.id.tv_name)

        init {
            itemView.setOnClickListener {
                Intent().apply {
                    setClass(context, MainActivity::class.java)
                    putExtra(
                        VideoTypeListData.VIDEO_TYPE_KEY,
                        VideoTypeListData.videoTypeList[adapterPosition].type
                    )
                    context.startActivity(this)
                }
            }
        }
    }

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): VideoTypeViewHolder {
        val v = LayoutInflater.from(parent.context)
            .inflate(R.layout.item_video_type_layout, parent, false)
        return VideoTypeViewHolder(v)
    }

    override fun getItemCount(): Int {
        return VideoTypeListData.videoTypeList.size
    }

    override fun onBindViewHolder(holder: VideoTypeViewHolder, position: Int) {
        holder.textView?.text = VideoTypeListData.videoTypeList[position].name

    }
}