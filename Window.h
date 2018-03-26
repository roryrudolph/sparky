#ifndef WINDOW_H_
#define WINDOW_H_

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define MAX_KEYS     1024
#define MAX_BUTTONS  32

class Window
{
public:
	Window(const char *title, int width, int height);
	~Window();

	void clear() const;
	void update();
	bool should_close() const;

	inline int get_width() const { return m_width; }
	inline int get_height() const { return m_height; }
	void get_mouse_position(double &x, double &y) const;

private:
	bool init();
	bool is_key_pressed(unsigned int key) const;
	bool is_mouse_button_pressed(unsigned int btn) const;

	GLFWwindow *m_window;
	const char *m_title;
	int m_width, m_height;

	bool m_keys[MAX_KEYS];
	bool m_mouse_btns[MAX_BUTTONS];
	double m_mx, m_my;

	friend struct cb;
};


#endif // WINDOW_H_
