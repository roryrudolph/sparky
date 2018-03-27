#ifndef LAYER_H_
#define LAYER_H_

#include "Renderable2D.h"
#include "Renderer2D.h"
#include "Shader.h"
#include <vector>

class Layer
{
public:
	virtual ~Layer();

	virtual void add(Renderable2D *renderable);
	virtual void render();

protected:
	Layer(Renderer2D *renderer, Shader *shader, const glm::mat4& projMatrix);

	Renderer2D *m_renderer;
	std::vector<Renderable2D *> m_objects;
	Shader *m_shader;
	glm::mat4 m_pmat;

private:
};


#endif // LAYER_H_
