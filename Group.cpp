#include "Group.h"

Group::Group(const glm::mat4& transform)
	: m_transformation_matrix(transform)
{

}

void Group::add(Renderable2D *renderable)
{
	m_renderables.push_back(renderable);
}

void Group::submit(Renderer2D *renderer) const
{
	renderer->push(m_transformation_matrix);
	for (const Renderable2D *renderable : m_renderables)
		renderable->submit(renderer);
	renderer->pop();
}

