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


//图元被光栅化为多少片段，就被调用多少次
static const char *fragSimpleShape =
        "  #version 300 es\n"
        "        precision\n"
        "        mediump float;\n"
        "\n"
        "        in\n"
        "        vec4 vTextColor;//输入的颜色\n"
        "        out vec4 FragColor;\n"

        "        in\n"
        "        vec4 vPosition;//输入的坐标\n"

        "        void main() {\n"
        "            //gl_FragColor是OpenGL内置的\n"
        "            FragColor = vec4(vPosition.x ,vPosition.y ,vPosition.z,1.0);\n"
        "        }";


//Uniform
static const char *vertexSimpleUniform =
        "        #version 300 es\n"
        "        layout (location = 0) \n"
        "        in vec4 aPosition;//输入的顶点坐标，会在程序指定将数据输入到该字段\n"
        "\n"
        //        "        out\n"
        //        "        vec4 vTextColor;//输出的颜色\n"
        //
        //        "        out\n"
        //        "        vec4 vPosition;//输出的坐标\n"
        "\n"
        "        void main() {\n"
        "            //直接把传入的坐标值作为传入渲染管线。gl_Position是OpenGL内置的\n"
        "            gl_Position = aPosition;\n"
        "        }";

static const char *fragSimpleUniform =
        "  #version 300 es\n"
        "        precision\n"
        "        mediump float;\n"
        "\n"
        "        uniform\n"
        "        vec4 uTextColor;//输出的颜色\n"
        "        out vec4 FragColor;\n"


        "        void main() {\n"
        "            //gl_FragColor是OpenGL内置的\n"
        "            FragColor = uTextColor;\n"
        "        }";

//WithColor
static const char *vertexSimpleShapeWithColor =
        "        #version 300 es\n"
        "        layout (location = 0) \n"
        "        in vec4 aPosition;//输入的顶点坐标，会在程序指定将数据输入到该字段\n"//如果传入的向量是不够4维的，自动将前三个分量设置为0.0，最后一个分量设置为1.0

        "        layout (location = 1) \n"
        "        in vec4 aColor;//输入的顶点的颜色\n" //如果传入的向量是不够4维的，自动将前三个分量设置为0.0，最后一个分量设置为1.0
        "\n"
        "        out\n"
        "        vec4 vTextColor;//输出的颜色\n"
        "\n"
        "        void main() {\n"
        "            //直接把传入的坐标值作为传入渲染管线。gl_Position是OpenGL内置的\n"
        "            gl_Position = aPosition;\n"
        "            vTextColor = aColor;\n"
        "        }";


static const char *fragSimpleShapeWithColor =
        "  #version 300 es\n"
        "        precision\n"
        "        mediump float;\n"
        "\n"
        "        in\n"
        "        vec4 vTextColor;//输入的颜色\n"
        "        out vec4 FragColor;\n"

        "        in\n"
        "        vec4 vPosition;//输入的坐标\n"

        "        void main() {\n"
        "            //gl_FragColor是OpenGL内置的\n"
        "            FragColor = vTextColor;\n"
        "        }";


//EBO
static const char *vertexSimpleShapeWithEBO =
        "        #version 300 es\n"
        "        layout (location = 0) \n"
        "        in vec4 aPosition;//输入的顶点坐标，会在程序指定将数据输入到该字段\n"//如果传入的向量是不够4维的，自动将前三个分量设置为0.0，最后一个分量设置为1.0

        "        layout (location = 1) \n"
        "        in vec4 aColor;//输入的顶点的颜色\n" //如果传入的向量是不够4维的，自动将前三个分量设置为0.0，最后一个分量设置为1.0
        "\n"
        "        out\n"
        "        vec4 vTextColor;//输出的颜色\n"
        "\n"
        "        void main() {\n"
        "            //直接把传入的坐标值作为传入渲染管线。gl_Position是OpenGL内置的\n"
        "            gl_Position = aPosition;\n"
        "            vTextColor = aColor;\n"
        "        }";

static const char *fragSimpleShapeEBO =
        "  #version 300 es\n"
        "        precision\n"
        "        mediump float;\n"
        "\n"
        "        in\n"
        "        vec4 vTextColor;//输入的颜色\n"
        "        out vec4 FragColor;\n"

        "        in\n"
        "        vec4 vPosition;//输入的坐标\n"

        "        void main() {\n"
        "            FragColor = vTextColor;\n"
        //        "            FragColor = vec4(1.0 ,0.0 ,0.0 ,1.0);\n"
        "        }";


//纹理
static const char *vertexSimpleTexture =
        "        #version 300 es\n"
        "        //输入的顶点坐标，会在程序指定将数据输入到该字段\n"
        "        layout (location = 0) in vec4 aPosition;\n"
        "        layout (location = 1) in vec2 aTexCoord;\n"

        "        out vec2 TexCoord;"
        "\n"
        "        void main() {\n"
        "            //直接把传入的坐标值作为传入渲染管线。gl_Position是OpenGL内置的\n"
        "            gl_Position = aPosition;\n"
        "            TexCoord = vec2(aTexCoord.x, 1.0 - aTexCoord.y);\n"
        //                "            TexCoord = aTexCoord;\n"
        "        }";

//图元被光栅化为多少片段，就被调用多少次
static const char *fragSimpleTexture =
        "        #version 300 es\n"
        "        precision mediump float;\n"
        "        in vec2 TexCoord;\n"
        "        out vec4 FragColor;\n"
        "        //传入的纹理\n"
        "        uniform sampler2D ourTexture;\n"
        "        uniform sampler2D ourTexture1;\n"

        "        void main() {\n"
        "            //gl_FragColor是OpenGL内置的\n"
        //        "            FragColor = texture(ourTexture, TexCoord);\n"
        "            FragColor = mix(texture(ourTexture, TexCoord), texture(ourTexture1, TexCoord), 0.5);\n"
        "        }";


#endif //LEARNMEDIA_FRAGMENTSHADER_H
