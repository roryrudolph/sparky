#include "Window.h"
#include "Shader.h"
#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp> // rotate, scale, translate

/**
 * Main program entry point
 * @return Returns 0 on success, else error
 */
int main(void)
{
	int width = 960;
	int height = 540;
	Window window("Sparky", width, height);

	GLfloat vertices[] =
	{
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0,
	};

	GLushort indices[] =
	{
		0, 1, 2,
		2, 3, 0,
	};

	GLfloat colorsA[] =
	{
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 1.0f,
	};

	GLfloat colorsB[] =
	{
		0.2f, 0.3f, 0.8f, 1.0f,
		0.2f, 0.3f, 0.8f, 1.0f,
		0.2f, 0.3f, 0.8f, 1.0f,
		0.2f, 0.3f, 0.8f, 1.0f,
	};

	VertexArray sprite1, sprite2;
	IndexBuffer ibo(indices, 6);

	sprite1.addBuffer(new Buffer(vertices, 4*3, 3), 0);
	sprite1.addBuffer(new Buffer(colorsA, 4*4, 4), 1);

	sprite2.addBuffer(new Buffer(vertices, 4*3, 3), 0);
	sprite2.addBuffer(new Buffer(colorsB, 4*4, 4), 1);

	Shader shader("vs.glsl", "fs.glsl");
	shader.enable();

	shader.setUniformMat4("vmmat", glm::mat4());
	shader.setUniformMat4("vvmat", glm::mat4());
	shader.setUniformMat4("vpmat", glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

	shader.setUniform2f("flit", glm::vec2(4.0f, 1.5f));

	while (! window.should_close())
	{
		window.clear();

		double x, y;
		window.get_mouse_position(x, y);
		float flit_x = (float)(x * 16.0f / (float)width);
		float flit_y = (float)(9.0f - y * 9.0f / (float)height);
		shader.setUniform2f("flit", glm::vec2(flit_x, flit_y));

		sprite1.bind();
		ibo.bind();
		shader.setUniformMat4("vmmat", glm::translate(glm::vec3(4, 3, 0)));
		glDrawElements(GL_TRIANGLES, ibo.get_count(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite1.unbind();

		sprite2.bind();
		ibo.bind();
		shader.setUniformMat4("vmmat", glm::translate(glm::vec3(0, 0, 0)));
		glDrawElements(GL_TRIANGLES, ibo.get_count(), GL_UNSIGNED_SHORT, 0);
		ibo.unbind();
		sprite2.unbind();

		window.update();
	}

	return (0);
}