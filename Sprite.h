#ifndef SPRITE_H_
#define SPRITE_H_

#include "Renderable2D.h"

class Sprite : public Renderable2D
{
public:
	Sprite(glm::vec3 pos, glm::vec2 size, glm::vec4 color);
};


#endif //SPRITE_H_
