#ifndef RENDERABLE2D_H_
#define RENDERABLE2D_H_

#include "Buffer.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Renderer2D.h"
#include <GL/glew.h>
#include <glm/glm.hpp>

struct VertexData
{
	glm::vec3 vertex;
	glm::vec2 uv;
	unsigned int color;
};

class Renderable2D
{
public:
	Renderable2D(glm::vec3 pos, glm::vec2 size, glm::vec4 color)
		: m_pos(pos), m_size(size), m_col(color)
	{
		set_uv_defaults();
	}

	virtual ~Renderable2D() { }

	virtual void submit(Renderer2D *renderer) const
	{
		renderer->submit(this);
	}

	virtual inline const glm::vec3& get_position() const { return m_pos; }
	virtual inline const glm::vec2& get_size() const { return m_size; }
	virtual inline const glm::vec4& get_color() const { return m_col; }
	virtual inline const std::vector<glm::vec2>& get_uv() const { return m_uv; }

protected:
	Renderable2D()
	{
		set_uv_defaults();
	}


	glm::vec3 m_pos;
	glm::vec2 m_size;
	glm::vec4 m_col;
	std::vector<glm::vec2> m_uv;

private:
	void set_uv_defaults()
	{
		m_uv.push_back(glm::vec2(0.0f, 0.0f));
		m_uv.push_back(glm::vec2(0.0f, 1.0f));
		m_uv.push_back(glm::vec2(1.0f, 1.0f));
		m_uv.push_back(glm::vec2(1.0f, 0.0f));
	}
};

#endif // RENDERABLE2D_H_
