#version 430 core
layout (location = 0) in vec2 aPos;
out vec2 pos;

layout (location = 2) uniform mat3 projection;
layout (location = 7) uniform mat3 model;

void main()
{
   gl_Position = vec4(projection * model * vec3(aPos.x, aPos.y, 1.0), 1.0);
   gl_Position.z = 0.0;
   pos = (model * vec3(aPos.x, aPos.y, 1.0)).xy;
}