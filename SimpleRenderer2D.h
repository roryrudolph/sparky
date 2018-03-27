#ifndef SIMPLE_RENDERER_2D_H_
#define SIMPLE_RENDERER_2D_H_

#include "Renderer2D.h"
#include "StaticSprite.h"
#include <deque>

class SimpleRenderer2D : public Renderer2D
{
public:
	void submit(const Renderable2D *renderable) override;
	void flush() override;

private:
	std::deque<const StaticSprite *> m_render_queue;

};

#endif // SIMPLE_RENDERER_2D_H_

