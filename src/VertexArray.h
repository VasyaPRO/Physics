#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <glad/glad.h>

#include "Vec.h"
#include "Mat.h"
#include "VertexBuffer.h"

class VertexArray
{
public:
    VertexArray();
    ~VertexArray();

    VertexArray(const VertexArray& vertexArray) = delete;
    VertexArray& operator=(const VertexArray& vertexArray) = delete;

    template <typename... T>
    void attachBuffer(const VertexBuffer& vb)
    {
        bindVertexArray(*this);
        bindBuffer(vb);
        unsigned int stride = sizeall<T...>();
        setAttrubutePointers<T...>(stride, 0);
    }
private:
    unsigned int handle = 0;
    unsigned int attributesCount = 0;

    template <typename Head, typename... Tail>
    void setAttrubutePointers(unsigned int stride, unsigned int offset)
    {
        setAttributePointer<Head>(attributesCount, stride, offset);
        attributesCount++;
        if constexpr (sizeof...(Tail) > 0)
        {
            setAttrubutePointers<Tail...>(stride, offset + sizeof(Head));
        }
    }

    template <typename T>
    void setAttributePointer(unsigned int index, unsigned int stride, unsigned int offset)
    {
        // NOTE: See specializations below
        static_assert(sizeof(T) == 0, "invalid attribute type");
    }

    template<typename... T>
    inline constexpr unsigned int sizeall()
    {
        return (0 + ... + sizeof(T));
    }

    friend void bindVertexArray(const VertexArray& vertexArray);
};

template<>
inline void VertexArray::setAttributePointer<float>(unsigned int index, unsigned int stride, unsigned int offset)
{
    glVertexAttribPointer(index, 1, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offset));
    glEnableVertexAttribArray(index);
}

template<>
inline void VertexArray::setAttributePointer<Vec2>(unsigned int index, unsigned int stride, unsigned int offset)
{
    glVertexAttribPointer(index, 2, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offset));
    glEnableVertexAttribArray(index);
}

template<>
inline void VertexArray::setAttributePointer<Vec3>(unsigned int index, unsigned int stride, unsigned int offset)
{
    glVertexAttribPointer(index, 3, GL_FLOAT, GL_FALSE, stride, reinterpret_cast<const void*>(offset));
    glEnableVertexAttribArray(index);
}

#endif