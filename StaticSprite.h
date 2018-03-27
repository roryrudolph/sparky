#ifndef STATIC_SPRITE_H_
#define STATIC_SPRITE_H_


#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Renderable2D.h"
#include <glm/glm.hpp>


class StaticSprite : public Renderable2D
{
public:
	StaticSprite(glm::vec3 pos, glm::vec2 size, glm::vec4 color, Shader &shader);
	~StaticSprite();

	inline const VertexArray *get_vao() const { return m_vao; }
	inline const IndexBuffer *get_ibo() const { return m_ibo; }

	inline Shader& get_shader() const { return m_shader; }

private:
	VertexArray *m_vao;
	IndexBuffer *m_ibo;
	Shader &m_shader;

};


#endif //STATIC_SPRITE_H_
