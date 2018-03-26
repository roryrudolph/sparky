#ifndef RENDERER2D_H_
#define RENDERER2D_H_

#include "Renderable2D.h"
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

class Renderer2D
{
public:
	virtual void submit(const Renderable2D *renderable) = 0;
	virtual void flush() = 0;

};

#endif // RENDERER2D_H_
