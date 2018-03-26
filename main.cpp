#include "Window.h"
#include <stdio.h>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

/**
 * Main program entry point
 * @return Returns 0 on success, else error
 */
int main(void)
{
	Window window("Sparky", 640, 480);

	while (! window.should_close())
	{
		window.clear();
		window.update();
	}

	return (0);
}