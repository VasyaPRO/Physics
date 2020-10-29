#include "Shader.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

using namespace std;

namespace
{
    void handle_shader_errors(GLuint shader)
    {
        GLint success = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (success == GL_FALSE) 
        {
            GLint log_size = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_size);
            char* log = new char[log_size];
            glGetShaderInfoLog(shader, log_size, nullptr, log);
            cerr << "Shader compilation error: " << endl << log << endl;
            glDeleteShader(shader);
            delete[] log;
            assert(false);
        }
    }

    void handle_program_errors(GLuint program)
    {
        GLint success = 0;
        glGetProgramiv(program, GL_LINK_STATUS, &success);
        if (success == GL_FALSE)
        {
            GLint log_size = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_size);
            char* log = new char[log_size];
            glGetProgramInfoLog(program, log_size, nullptr, log);
            cerr << "Program linking error: " << endl << log << endl;
            glDeleteProgram(program);
            delete[] log;
            assert(false);
        }
    }

    string getFileContent(const char* file_path)
    {
        stringstream ss;
        ifstream fin(file_path);
        assert(fin.is_open());
        ss << fin.rdbuf();
        return ss.str();
    }
}

Shader::Shader()
{
    program = glCreateProgram();
}

Shader::~Shader()
{
    glDeleteProgram(program);
}

void Shader::loadFromFile(const char* vertex_file_path, const char* fragment_file_path)
{
    loadFromMemory(getFileContent(vertex_file_path).c_str(), getFileContent(fragment_file_path).c_str());
}

void Shader::loadFromMemory(const char* vertex_source, const char* fragment_source)
{
    GLuint vertex_shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader, 1, &vertex_source, nullptr);
    glCompileShader(vertex_shader);

    handle_shader_errors(vertex_shader);

    GLuint fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader, 1, &fragment_source, nullptr);
    glCompileShader(fragment_shader);

    handle_shader_errors(fragment_shader);

    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
    glLinkProgram(program);

    handle_program_errors(program);

    glDetachShader(program, vertex_shader);
    glDetachShader(program, fragment_shader);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
}

void Shader::setUniform(int uniform_location, const Mat3& mat)
{
    glUniformMatrix3fv(uniform_location, 1, GL_TRUE, (GLfloat*)&mat);
}

void Shader::setUniform(int uniform_location, float f)
{
    glUniform1f(uniform_location, f);
} 

void Shader::setUniform(int uniform_location, Vec2 vec)
{
    glUniform2f(uniform_location, vec.x, vec.y);
}

int Shader::getUniformLocation(const char* uniform_name)
{
    int loc = glGetUniformLocation(program, uniform_name);
    assert(loc != -1);
    return loc;
}

void useProgram(Shader& shader_program)
{
    // NOTE: 0 is not a valid program handle
    static GLuint current_program = 0;
    if (shader_program.program != current_program)
    {
        glUseProgram(shader_program.program);
        current_program = shader_program.program;
    }
}