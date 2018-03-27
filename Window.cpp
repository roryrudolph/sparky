#include "Window.h"
#include <stdio.h>
#include <string.h>

struct cb
{
	static void cursor_enter(GLFWwindow *window, int entered);
	static void cursor_pos(GLFWwindow *window, double xpos, double ypos);
	static void mouse_button(GLFWwindow *window, int button, int action, int mods);
	static void window_size(GLFWwindow *window, int width, int height);
	static void key(GLFWwindow *window, int key, int scancode, int action, int mods);
};

/**
 * Constructor
 * @param title The window title
 * @param width The window width
 * @param height The window height
 */
Window::Window(const char *title, int width, int height)
{
	m_title = title;
	m_width = width;
	m_height = height;

	if (! init())
		glfwTerminate();

	memset(m_keys, false, MAX_KEYS * sizeof(*m_keys));
	memset(m_mouse_btns, false, MAX_BUTTONS * sizeof(*m_mouse_btns));
}

/**
 * Destructor
 */
Window::~Window()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

/**
 * Clears the window
 */
void Window::clear() const
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/**
 * Updates the window
 */
void Window::update()
{
	GLenum errnum = glGetError();
	if (errnum != GL_NO_ERROR)
	{
		printf("ERROR: %s: OpenGL %d: ", __func__, errnum);
		switch (errnum)
		{
			case GL_INVALID_ENUM:
				printf("Invalid enum\n");
				break;
			case GL_INVALID_VALUE:
				printf("Invalid value\n");
				break;
			case GL_INVALID_OPERATION:
				printf("Invalid operation\n");
				break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
				printf("Invalid framebuffer operation\n");
				break;
			case GL_OUT_OF_MEMORY:
				printf("Out of memory\n");
				break;
			case GL_STACK_UNDERFLOW:
				printf("Stack underflow\n");
				break;
			case GL_STACK_OVERFLOW:
				printf("Stack overflow\n");
				break;
			default:
				printf("\n");
		}
	}

	glfwPollEvents();
	glfwSwapBuffers(m_window);
}

/**
 * Returns whether the window is set to close or not
 * @return Returns TRUE if the window is set to close, else FALSE
 */
bool Window::should_close() const
{
	return (glfwWindowShouldClose(m_window) == 1);
}

void Window::get_mouse_position(double &x, double &y) const
{
	x = m_mx;
	y = m_my;
}

/**
 * Initialize the window
 * @return Returns true on success, else false
 */
bool Window::init()
{
	if (! glfwInit())
	{
		printf("ERROR: %s: Could not initialize GLFW\n", __func__);
		return false;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_VISIBLE, 0);

	m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
	if (! m_window)
	{
		glfwTerminate();
		printf("ERROR: %s: Could not create GLFW window\n", __func__);
		return false;
	}

	glfwSetCursorEnterCallback(m_window, cb::cursor_enter);
	glfwSetCursorPosCallback(m_window, cb::cursor_pos);
	glfwSetMouseButtonCallback(m_window, cb::mouse_button);
	glfwSetKeyCallback(m_window, cb::key);
	glfwSetWindowSizeCallback(m_window, cb::window_size);

	glfwMakeContextCurrent(m_window);
	glfwSetWindowUserPointer(m_window, this);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		printf("ERROR: %s: Could not initialize GLEW\n", __func__);
		return false;
	}

	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glGetError(); // Force clear errors

	return true;
}

bool Window::is_key_pressed(unsigned int key) const
{
	// TODO log this
	if (key >= MAX_KEYS)
		return false;
	return (m_keys[key]);
}

bool Window::is_mouse_button_pressed(unsigned int btn) const
{
	// TODO log this
	if (btn >= MAX_BUTTONS)
		return false;
	return (m_mouse_btns[btn]);
}

/**
 * Cursor enter/exit callback
 * @param window The window that received the event
 * @param entered GLFW_TRUE if the cursor entered the window's client area, or GLFW_FALSE if it left it
 */
void cb::cursor_enter(GLFWwindow *window, int entered)
{
	if (window && entered) { ; } // TODO For now, satifies -Werror=unused-parameters
}

/**
 * Cursor position callback
 * @param window The window that received the event
 * @param xpos The new cursor x-coordinate, relative to the left edge of the client area
 * @param ypos The new cursor y-coordinate, relative to the top edge of the client area
 */
void cb::cursor_pos(GLFWwindow *window, double xpos, double ypos)
{
	Window *w = (Window *)glfwGetWindowUserPointer(window);
	w->m_mx = xpos;
	w->m_my = ypos;
}

/**
 * @param window The window that received the event.
 * @param key The keyboard key that was pressed or released.
 * @param scancode The system-specific scancode of the key.
 * @param action GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.
 * @param mods Bit field describing which modifier keys were held down
 */
void cb::key(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (scancode) { ; } // TODO For now, satifies -Werror=unused-parameter

	Window *w = (Window *)glfwGetWindowUserPointer(window);
	w->m_keys[key] = action != GLFW_RELEASE;

	switch (key)
	{
		case GLFW_KEY_ESCAPE:
			if (action == GLFW_PRESS && mods == 0)
				glfwSetWindowShouldClose(window, 1);
			break;
		default:
			break;
	}
}

/**
 * Mouse button callback
 * @param window The window that received the event.
 * @param button The mouse button that was pressed or released.
 * @param action One of GLFW_PRESS or GLFW_RELEASE.
 * @param mods Bit field describing which modifier keys were held down
 */
void cb::mouse_button(GLFWwindow *window, int button, int action, int mods)
{
	if (mods) { ; } // TODO For now, satifies -Werror=unused-parameter

	Window *w = (Window *)glfwGetWindowUserPointer(window);
	w->m_mouse_btns[button] = action != GLFW_RELEASE;
}

/**
 * Window (re)size callback
 * @param window The window that was resized
 * @param width The new width, in screen coordinates, of the window
 * @param height The new height, in screen coordinates, of the window
 */
void cb::window_size(GLFWwindow *window, int width, int height)
{
	if (window) { ; } // TODO For now, satifies -Werror=unused-parameter

	glViewport(0, 0, width, height);
}

