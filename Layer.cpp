#include "Layer.h"

Layer::Layer(Renderer2D *renderer, Shader *shader, const glm::mat4& projMatrix)
	: m_renderer(renderer), m_shader(shader), m_pmat(projMatrix)
{
	m_shader->enable();
	m_shader->setUniformMat4("vpmat", m_pmat);
	m_shader->disable();
}

Layer::~Layer()
{
	delete m_shader;
	delete m_renderer;
	for (unsigned int i = 0; i < m_objects.size(); ++i)
		delete m_objects[i];
}

void Layer::add(Renderable2D *renderable)
{
	m_objects.push_back(renderable);
}

void Layer::render()
{
	m_shader->enable();

	m_renderer->begin();
	for (const Renderable2D *o : m_objects)
			o->submit(m_renderer);
	m_renderer->end();

	m_renderer->flush();
}
