#include "BatchRenderer2D.h"

BatchRenderer2D::BatchRenderer2D()
{
	init();
}

BatchRenderer2D::~BatchRenderer2D()
{
	delete m_ibo;
	glDeleteBuffers(1, &m_vbo);

}

void BatchRenderer2D::begin()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	m_buf = (VertexData *)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
}

void BatchRenderer2D::end()
{
	glUnmapBuffer(GL_ARRAY_BUFFER);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void BatchRenderer2D::submit(const Renderable2D *renderable)
{
	const glm::vec3& pos = renderable->get_position();
	const glm::vec2& siz = renderable->get_size();
	const glm::vec4& col = renderable->get_color();

	int r = col.r * 255.0f;
	int g = col.g * 255.0f;
	int b = col.b * 255.0f;
	int a = col.a * 255.0f;
	unsigned int c = a << 24 | b << 16 | g << 8 | r;

	m_buf->vertex = *m_transformation_back * glm::vec4(pos, 1.0);
	m_buf->color = c;
	m_buf++;

	m_buf->vertex = *m_transformation_back * glm::vec4(pos.x, pos.y + siz.y, pos.z, 1.0f);
	m_buf->color = c;
	m_buf++;

	m_buf->vertex = *m_transformation_back * glm::vec4(pos.x + siz.x, pos.y + siz.y, pos.z, 1.0f);
	m_buf->color = c;
	m_buf++;

	m_buf->vertex = *m_transformation_back * glm::vec4(pos.x + siz.x, pos.y, pos.z, 1.0f);
	m_buf->color = c;
	m_buf++;

	m_index_count += 6;
}

void BatchRenderer2D::flush()
{
	glBindVertexArray(m_vao);
	m_ibo->bind();

	glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_SHORT, NULL);

	m_ibo->unbind();
	glBindVertexArray(0);

	m_index_count = 0;
}

void BatchRenderer2D::init()
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
	glEnableVertexAttribArray(SHADER_COLOR_INDEX);
	glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (void *)(offsetof(VertexData, VertexData::vertex)));
	glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (void *)(offsetof(VertexData, VertexData::color)));

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLushort offset = 0;
	GLushort indices[RENDERER_INDICES_SIZE];
	for (GLushort i = 0; i < RENDERER_INDICES_SIZE; i += 6)
	{
		indices[i + 0] =  offset + 0;
		indices[i + 1] =  offset + 1;
		indices[i + 2] =  offset + 2;
		indices[i + 3] =  offset + 2;
		indices[i + 4] =  offset + 3;
		indices[i + 5] =  offset + 0;
		offset += 4;
	}

	m_ibo = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

	glBindVertexArray(0);
}


