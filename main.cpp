#include "Window.h"
#include "Shader.h"
#include "Buffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Simple2DRenderer.h"
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

	Shader shader("vs.glsl", "fs.glsl");
	shader.enable();

	shader.setUniformMat4("vmmat", glm::mat4());
	shader.setUniformMat4("vvmat", glm::mat4());
	shader.setUniformMat4("vpmat", glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

	shader.setUniform2f("flit", glm::vec2(4.0f, 1.5f));

	Renderable2D sprite1(
		glm::vec3(5.0f, 5.0f, 0.0f),
		glm::vec2(4.0f, 4.0f),
		glm::vec4(1.0f, 0.0f, 1.0f, 1.0f),
		&shader
	);
	Renderable2D sprite2(
		glm::vec3(7.0f, 1.0f, 0.0f),
		glm::vec2(2.0f, 3.0f),
		glm::vec4(0.2f, 0.0f, 1.0f, 1.0f),
		&shader
	);

	Simple2DRenderer renderer;

	while (! window.should_close())
	{
		window.clear();

		double x, y;
		window.get_mouse_position(x, y);
		float flit_x = (float)(x * 16.0f / (float)width);
		float flit_y = (float)(9.0f - y * 9.0f / (float)height);
		shader.setUniform2f("flit", glm::vec2(flit_x, flit_y));

		renderer.submit(&sprite1);
		renderer.submit(&sprite2);

		renderer.flush();

		window.update();
	}

	return (0);
}