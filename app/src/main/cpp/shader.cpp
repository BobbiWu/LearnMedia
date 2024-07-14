//
// Created by insane on 2024/7/8.
//
#include <GLES3/gl3.h>
#include "shader.h"

GLint Shader::initShader(const char *source, GLint type) {
    //创建shader
    GLint sh = glCreateShader(type);
    if (sh == 0) {
        Shader_LOGD("glCreateShader %d failed", type);
        return 0;
    }
    //加载shader
    glShaderSource(sh,
                   1,//shader数量
                   &source,
                   0);//代码长度，传0则读到字符串结尾

    //编译shader
    glCompileShader(sh);

    //打印出编译错误信息
    GLint status;
    glGetShaderiv(sh, GL_COMPILE_STATUS, &status);
    if (status == 0) {
        Shader_LOGD("glCompileShader %d failed", type);
        Shader_LOGD("source %s", source);
        auto *infoLog = new GLchar[2048];
        GLsizei length;
        glGetShaderInfoLog(sh, 2048, &length, infoLog);
//        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;

        Shader_LOGD("ERROR::SHADER::VERTEX::COMPILATION_FAILED %s", infoLog);
        return 0;
    }

    Shader_LOGD("glCompileShader %d success", type);
    return sh;
}
