#ifndef RENDERABLE2D_H_
#define RENDERABLE2D_H_

#include "Buffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

class Renderable2D
{
public:
	Renderable2D(glm::vec3 pos, glm::vec2 size, glm::vec4 color, Shader *shader)
		: m_pos(pos), m_size(size), m_col(color), m_shader(shader)
	{
		m_vao = new VertexArray();

		GLfloat vertices[] =
		{
			0, 0, 0,
			0, size.y, 0,
			size.x, size.y, 0,
			size.x, 0, 0,
		};

		GLfloat colors[] =
		{
			color.r, color.g, color.b, color.a,
			color.r, color.g, color.b, color.a,
			color.r, color.g, color.b, color.a,
			color.r, color.g, color.b, color.a,
		};

		m_vao->addBuffer(new Buffer(vertices, 4*3, 3), 0);
		m_vao->addBuffer(new Buffer(colors, 4*4, 4), 1);

		GLushort indices[] = { 0, 1, 2, 2, 3, 0 };
		m_ibo = new IndexBuffer(indices, 6);
	}

	~Renderable2D()
	{
		delete m_vao;
		delete m_ibo;
	}

	inline const VertexArray *get_vao() const { return m_vao; }
	inline const IndexBuffer *get_ibo() const { return m_ibo; }
	inline Shader *get_shader() const { return m_shader; }

	inline const glm::vec3& get_position() const { return m_pos; }
	inline const glm::vec2& get_size() const { return m_size; }
	inline const glm::vec4& get_color() const { return m_col; }

protected:
	glm::vec3 m_pos;
	glm::vec2 m_size;
	glm::vec4 m_col;

	VertexArray *m_vao;
	IndexBuffer *m_ibo;
	Shader *m_shader;
};

#endif // RENDERABLE2D_H_
