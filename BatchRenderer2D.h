#ifndef BATCHRENDERER2D_H_
#define BATCHRENDERER2D_H_

#include "Renderer2D.h"
#include "Renderable2D.h"
#include "IndexBuffer.h"
#include <cstddef>

#define RENDERER_MAX_SPRITES   10000
#define RENDERER_VERTEX_SIZE   (sizeof(VertexData))
#define RENDERER_SPRITE_SIZE   (RENDERER_VERTEX_SIZE*4)
#define RENDERER_BUFFER_SIZE   (RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES)
#define RENDERER_INDICES_SIZE  (RENDERER_MAX_SPRITES * 6)

#define SHADER_VERTEX_INDEX    0
#define SHADER_COLOR_INDEX     1

class BatchRenderer2D : public Renderer2D
{
public:
	BatchRenderer2D();
	~BatchRenderer2D();

	void begin() override;
	void submit(const Renderable2D *renderable) override;
	void end() override;
	void flush() override;

private:
	void init();

	GLuint m_vao;
	GLuint m_vbo;
	IndexBuffer *m_ibo;
	GLsizei m_index_count;
	VertexData *m_buf;
};

#endif //BATCHRENDERER2D_H_
