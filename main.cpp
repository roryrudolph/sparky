#include "Window.h"
#include "Shader.h"
#include "SimpleRenderer2D.h"
#include "Sprite.h"
#include "StaticSprite.h"
#include "BatchRenderer2D.h"
#include "Timer.h"
#include "TileLayer.h"
#include "Group.h"
#include "Texture.h"

#define BATCH_RENDERER  1

/**
 * Main program entry point
 * @return Returns 0 on success, else error
 */
int main(void)
{
	int width = 960;
	int height = 540;
	const char *texture_path = "../img/wall.jpg";
	const char *vertex_shader_path = "../shaders/vs.glsl";
	const char *fragment_shader_path = "../shaders/fs.glsl";

	Window window("Sparky", width, height);

	Shader *shader1 = new Shader(vertex_shader_path, fragment_shader_path);
	shader1->enable();
	shader1->setUniform2f("flit", glm::vec2(4.0f, 1.5f));

	srand(time(NULL));

	TileLayer layer1(shader1);

	for (float y = -9.0f; y < 9.0f; y += 1.0f)
		for (float x = -16.0f; x < 16.0f; x += 1.0f)
			layer1.add(new Sprite(glm::vec3(x, y, 0.0f),
								  glm::vec2(0.9f, 0.9f),
								  glm::vec4(rand() % 1000 / 1000.0f, 0.0f, 1.0f, 1.0f)));

	glActiveTexture(GL_TEXTURE0);
	Texture tex(texture_path);
	tex.bind();

	shader1->enable();
	shader1->setUniform1i("tex", 0);
	shader1->setUniformMat4("vpmat", glm::ortho(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

//	Group *group1 = new Group(glm::translate(glm::vec3(-15.0f, 5.0f, 0.0f)));
//	group1->add(new Sprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(6.0f, 3.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
//
//	Group *button = new Group(glm::translate(glm::vec3(0.5f, 0.5f, 0.0f)));
//	button->add(new Sprite(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(5.0f, 2.0f), glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)));
//	button->add(new Sprite(glm::vec3(0.5f, 0.5f, 0.0f), glm::vec2(3.0f, 1.0f), glm::vec4(0.2f, 0.3f, 0.8f, 1.0f)));
//	group1->add(button);
//
//	layer1.add(group1);

	while (! window.should_close())
	{
		window.clear();

		double x, y;
		window.get_mouse_position(x, y);
		float flit_x = (float)(x * 32.0f / (float)width - 16.0f);
		float flit_y = (float)(9.0f - y * 18.0f / (float)height);

		shader1->setUniform2f("flit", glm::vec2(flit_x, flit_y));

		layer1.render();

		window.update();
	}

	return (0);
}
