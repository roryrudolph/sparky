#version 330

layout (location = 0) in vec4 vpos;

uniform mat4 mmat;
uniform mat4 vmat;
uniform mat4 pmat;

void main()
{
    gl_Position = pmat * vmat * mmat * vpos;
}
