#include "SimpleRenderer2D.h"

void SimpleRenderer2D::submit(const Renderable2D *renderable)
{
	m_render_queue.push_back((StaticSprite *)renderable);
}

void SimpleRenderer2D::flush()
{
	while (! m_render_queue.empty())
	{
		const StaticSprite *sprite = m_render_queue.front();
		sprite->get_vao()->bind();
		sprite->get_ibo()->bind();

		sprite->get_shader().setUniformMat4("vmmat", glm::translate(sprite->get_position()));
		glDrawElements(
			GL_TRIANGLES,
			sprite->get_ibo()->get_count(),
			GL_UNSIGNED_SHORT,
			0
		);

		sprite->get_ibo()->unbind();
		sprite->get_vao()->unbind();

		m_render_queue.pop_front();
	}
}
