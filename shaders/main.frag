#version 430 core
in vec2 pos;
out vec4 FragColor;

layout (location = 0) uniform vec2 center;
layout (location = 1) uniform float radius;

void main()
{
    if (length(pos - center) > radius)
       discard;
    FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}