//
// Created by insane on 2024/7/8.
//

#ifndef LEARNMEDIA_FRAGMENTSHADER_H
#define LEARNMEDIA_FRAGMENTSHADER_H

static const char *vertexSimpleShape =
        "        #version 300 es\n"
        "        layout (location = 0) \n"
        "        in vec4 aPosition;//输入的顶点坐标，会在程序指定将数据输入到该字段\n"
        "\n"
        "        out\n"
        "        vec4 vTextColor;//输出的颜色\n"

        "        out\n"
        "        vec4 vPosition;//输出的坐标\n"
        "\n"
        "        void main() {\n"
        "            //直接把传入的坐标值作为传入渲染管线。gl_Position是OpenGL内置的\n"
        "            gl_Position = aPosition;\n"
        "            vPosition = aPosition;\n"
        "            gl_PointSize = 50.0;\n"
        //        "            vTextColor = vec4(aPosition.x ,aPosition.y ,aPosition.z,1.0);\n"
        "        }";


#endif //LEARNMEDIA_FRAGMENTSHADER_H
