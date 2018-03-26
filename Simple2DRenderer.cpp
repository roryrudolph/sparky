#include "Simple2DRenderer.h"

void Simple2DRenderer::submit(const Renderable2D *renderable)
{
	m_render_queue.push_back(renderable);
}

void Simple2DRenderer::flush()
{
	while (! m_render_queue.empty())
	{
		const Renderable2D *renderable = m_render_queue.front();
		renderable->get_vao()->bind();
		renderable->get_ibo()->bind();

		renderable->get_shader()->setUniformMat4("vmmat", glm::translate(renderable->get_position()));
		glDrawElements(
			GL_TRIANGLES,
			renderable->get_ibo()->get_count(),
			GL_UNSIGNED_SHORT,
			0
		);

		renderable->get_ibo()->unbind();
		renderable->get_vao()->unbind();

		m_render_queue.pop_front();
	}
}
