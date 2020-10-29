#include "VertexArray.h"

VertexArray::VertexArray()
{
    glGenVertexArrays(1, &handle);
}

VertexArray::~VertexArray()
{
    glDeleteVertexArrays(1, &handle);
}

void bindVertexArray(const VertexArray& vertexArray)
{
    glBindVertexArray(vertexArray.handle);
}