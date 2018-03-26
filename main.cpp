#include "Window.h"
#include "Shader.h"
#include "Buffer.h"
#include "IndexBuffer.h"
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
	Window window("Sparky", 640, 480);

	Shader shader("../vs.glsl", "../fs.glsl");
	shader.enable();

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		+0.5f, -0.5f, 0.0f,
		+0.5f, +0.5f, 0.0f,
		+0.5f, +0.5f, 0.0f,
		-0.5f, +0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
	};

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	shader.setUniformMat4("mmat", glm::translate(glm::vec3(1.0, 0.0, 0.0)));
	shader.setUniformMat4("vmat", glm::mat4());
	shader.setUniformMat4("pmat", glm::mat4());

	while (! window.should_close())
	{
		window.clear();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		window.update();
	}

	return (0);
}