#version 330 core
layout (location = 0) in vec3 aPos;

uniform vec2 position;

uniform float height;

// translation matrix
mat4 translation = mat4(
    1.0, 0.0, 0.0, position.x - 1, // -1 for x and +1 for y to make it start from top left corner
    0.0, 1.0, 0.0, -position.y - (2-height*2) + 1,
    0.0, 0.0, 1.0, 0.0,
    0.0, 0.0, 0.0, 1.0
);

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) * translation;
}