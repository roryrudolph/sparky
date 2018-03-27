#include "Window.h"
#include "Shader.h"
#include "SimpleRenderer2D.h"
#include "Sprite.h"
#include "StaticSprite.h"
#include "BatchRenderer2D.h"
#include "Timer.h"

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

	Shader shader("shaders/vs.glsl", "shaders/fs.glsl");
	shader.enable();

	shader.setUniformMat4("vpmat", glm::ortho(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f));

	shader.setUniform2f("flit", glm::vec2(4.0f, 1.5f));

	srand(time(NULL));
	std::vector<Renderable2D*> sprites;

#if (BATCH_RENDERER == 1)
	BatchRenderer2D renderer;

	for (float y = 0; y < 9.0f; y += 1.0f)
		for (float x = 0; x < 16.0f; x += 1.0f)
			sprites.push_back(new Sprite(glm::vec3(x, y, 0), glm::vec2(0.9f, 0.9f), glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
#else
	SimpleRenderer2D renderer;

	for (float y = 0; y < 9.0f; y += 0.1)
		for (float x = 0; x < 16.0f; x += 0.1)
			sprites.push_back(new StaticSprite(glm::vec3(x, y, 0), glm::vec2(0.04f, 0.04f), glm::vec4(rand() % 1000 / 1000.0f, 0, 1, 1), shader));
#endif

	while (! window.should_close())
	{
		window.clear();

		double x, y;
		window.get_mouse_position(x, y);
		float flit_x = (float)(x * 16.0f / (float)width);
		float flit_y = (float)(9.0f - y * 9.0f / (float)height);
		shader.setUniform2f("flit", glm::vec2(flit_x, flit_y));

#if (BATCH_RENDERER == 1)
		renderer.begin();
		for (unsigned int i = 0; i < sprites.size(); ++i)
			renderer.submit(sprites[i]);
		renderer.end();
#else
		for (unsigned int i = 0; i < sprites.size(); ++i)
			renderer.submit(sprites[i]);
#endif

		renderer.flush();

		window.update();
	}

	return (0);
}