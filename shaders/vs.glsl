#version 410

layout (location = 0) in vec4 vpos;
layout (location = 1) in vec2 vuv;
layout (location = 2) in vec4 vcol;

uniform mat4 vmmat = mat4(1.0);
uniform mat4 vvmat = mat4(1.0);
uniform mat4 vpmat = mat4(1.0);

out DATA
{
    vec4 pos;
    vec2 uv;
    vec4 col;
} vout;


void main()
{
    gl_Position = vpmat * vvmat * vmmat * vpos;
    vout.pos = vmmat * vpos;
    vout.uv = vuv;
    vout.col = vcol;
}