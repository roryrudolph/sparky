#version 410

layout (location = 0) out vec4 outColor;

uniform vec2 flit;
uniform vec4 fcol;

uniform sampler2D sampler;

in DATA
{
    vec4 pos;
    vec2 uv;
    vec4 col;
} fin;

void main()
{
    float intensity = 1.0 / length(fin.pos.xy - flit);
    outColor = fin.col * intensity;
    outColor = texture(sampler, fin.uv) * intensity;
}