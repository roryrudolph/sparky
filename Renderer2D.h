#ifndef RENDERER2D_H_
#define RENDERER2D_H_

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <vector>

class Renderable2D;

class Renderer2D
{
public:
	virtual ~Renderer2D() { }

	virtual void begin() { }
	virtual void end() { }
	virtual void submit(const Renderable2D *renderable) = 0;
	virtual void flush() = 0;

	void push(glm::mat4 matrix, bool override = false)
	{
		if (override)
			m_transformation_stack.push_back(matrix);
		else
			m_transformation_stack.push_back(m_transformation_stack.back() * matrix);

		m_transformation_back = &m_transformation_stack.back();
	}

	void pop()
	{
		// TODO add to log
		if (m_transformation_stack.size() > 1)
			m_transformation_stack.pop_back();

		m_transformation_back = &m_transformation_stack.back();
	}

protected:
	Renderer2D()
	{
		m_transformation_stack.push_back(glm::mat4());
		m_transformation_back = &m_transformation_stack.back();
	}

	std::vector<glm::mat4> m_transformation_stack;
	const glm::mat4 *m_transformation_back;

};

#endif // RENDERER2D_H_
