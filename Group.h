#ifndef GROUP_H_
#define GROUP_H_

#include "Renderer2D.h"
#include "Renderable2D.h"
#include <vector>

class Group : public Renderable2D
{
public:
	Group(const glm::mat4& transform);
	void add(Renderable2D *renderable);
	void submit(Renderer2D *renderer) const override;

private:
	std::vector<Renderable2D *> m_renderables;
	glm::mat4 m_transformation_matrix;
};


#endif // GROUP_H_
