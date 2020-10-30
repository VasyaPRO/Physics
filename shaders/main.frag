#version 430 core
in vec2 pos;
out vec4 FragColor;

layout (location = 0) uniform vec2 center;
layout (location = 1) uniform float radius;

void main()
{
    float dist = length(pos - center);
    FragColor = vec4(1.0f, 0.5f, 0.2f, smoothstep(radius + 0.5, radius - 0.5, dist));
}