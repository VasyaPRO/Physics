#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

class VertexBuffer
{
public:
    VertexBuffer();
    VertexBuffer(const void* data, unsigned int size);
    ~VertexBuffer();
    VertexBuffer(const VertexBuffer& vertexBuffer) = delete;
    VertexBuffer& operator=(const VertexBuffer& vertexBuffer) = delete;
    void setData(const void* data, unsigned int size);
    void update(const void* data, unsigned int size, int offset);

    // NOTE: this may be slow
    int getSize() const;
private:
    unsigned int handle;

    friend void bindBuffer(const VertexBuffer& vertexBuffer);
};

#endif