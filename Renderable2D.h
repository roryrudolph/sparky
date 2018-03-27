#ifndef RENDERABLE2D_H_
#define RENDERABLE2D_H_

#include "Buffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

struct VertexData
{
	glm::vec3 vertex;
	//glm::vec4 color;
	unsigned int color;
};

class Renderable2D
{
public:
	Renderable2D(glm::vec3 pos, glm::vec2 size, glm::vec4 color)
		: m_pos(pos), m_size(size), m_col(color)
	{ }

	virtual ~Renderable2D() { }

	virtual inline const glm::vec3& get_position() const { return m_pos; }
	virtual inline const glm::vec2& get_size() const { return m_size; }
	virtual inline const glm::vec4& get_color() const { return m_col; }

protected:
	glm::vec3 m_pos;
	glm::vec2 m_size;
	glm::vec4 m_col;
};

#endif // RENDERABLE2D_H_
