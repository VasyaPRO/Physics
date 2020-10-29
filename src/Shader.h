#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include "Vec.h"
#include "Mat.h"

class Shader
{
public:
    Shader();
    ~Shader();
    void loadFromFile(const char* vertex_file_path, const char* fragment_file_path);
    void loadFromMemory(const char* vertex_source, const char* fragment_source);

    int getUniformLocation(const char* uniform_name);
    
    void setUniform(int uniform_location, const Mat3& mat);
    void setUniform(int uniform_location, float f);
    void setUniform(int uniform_location, Vec2 vec);

    template<typename T>
    void setUniform(const char* uniform_name, T value)
    {
        setUniform(getUniformLocation(uniform_name), value);
    }

    friend void useProgram(Shader& shader_program);
private:
    GLuint program = 0;
};

#endif