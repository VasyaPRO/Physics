#include "VertexBuffer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer()
{
    glGenBuffers(1, &handle);
}

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
    glGenBuffers(1, &handle);
    setData(data, size);
}

VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &handle);
}

void VertexBuffer::setData(const void* data, unsigned int size)
{
    bindBuffer(*this);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

void VertexBuffer::update(const void* data, unsigned int size, int offset)
{
    bindBuffer(*this);
    glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
}

int VertexBuffer::getSize() const
{
    bindBuffer(*this);
    int size;
    glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
    return size;
}

void bindBuffer(const VertexBuffer& vertexBuffer)
{
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer.handle);
}