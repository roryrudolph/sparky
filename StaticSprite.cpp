#include "StaticSprite.h"

StaticSprite::StaticSprite(glm::vec3 pos, glm::vec2 size, glm::vec4 color, Shader &shader)
	: Renderable2D(pos, size, color), m_shader(shader)
{
	m_vao = new VertexArray();

	GLfloat vertices[] =
	{
		  0.0f,   0.0f, 0.0f,
		  0.0f, size.y, 0.0f,
		size.x, size.y, 0.0f,
		size.x,   0.0f, 0.0f,
	};

	GLfloat colors[] =
	{
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
		color.x, color.y, color.z, color.w,
	};

	m_vao->addBuffer(new Buffer(vertices, 4*3, 3), 0);
	m_vao->addBuffer(new Buffer(colors, 4*4, 4), 1);

	GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
	m_ibo = new IndexBuffer(indices, 6);
}

StaticSprite::~StaticSprite()
{
	delete m_vao;
	delete m_ibo;
}
