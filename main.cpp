#include "Window.h"
#include "Shader.h"
#include "SimpleRenderer2D.h"
#include "Sprite.h"
#include "StaticSprite.h"
#include "BatchRenderer2D.h"
#include "Timer.h"
#include "TileLayer.h"

#define BATCH_RENDERER  1

/**
 * Main program entry point
 * @return Returns 0 on success, else error
 */
int main(void)
{
	int width = 960;
	int height = 540;
	Window window("Sparky", width, height);

	Shader *shader = new Shader("../shaders/vs.glsl", "../shaders/fs.glsl");
	shader->setUniform2f("flit", glm::vec2(4.0f, 1.5f));

	srand(time(NULL));

	TileLayer layer(shader);
	for (float y = -9.0f; y < 9.0f; y += 1.0f)
		for (float x = -16.0f; x < 16.0f; x += 1.0f)
			layer.add(new Sprite(glm::vec3(x, y, 0.0f), glm::vec2(0.9f, 0.9f), glm::vec4(rand() % 1000 / 1000.0f, 0.0f, 1.0f, 1.0f)));

	while (! window.should_close())
	{
		window.clear();

		double x, y;
		window.get_mouse_position(x, y);
		float flit_x = (float)(x * 32.0f / (float)width - 16.0f);
		float flit_y = (float)(9.0f - y * 18.0f / (float)height);
		shader->setUniform2f("flit", glm::vec2(flit_x, flit_y));

		layer.render();

		window.update();
	}

	return (0);
}