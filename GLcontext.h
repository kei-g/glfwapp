#pragma once

class GLapplication;

class GLcontext
{
private:
	GLapplication &app;
	std::function<void(double, double)> cursorEvent;
	std::function<void(int, int, int, int)> keyEvent;
	std::function<void(int, int, int)> mouseEvent;
	std::function<void(int, int)> resizeEvent;
	GLFWwindow *window;

public:
	GLcontext(GLapplication &app, GLFWwindow *window);
	virtual ~GLcontext();

public:
	void MakeCurrent();
	void SetCursorCallback(const std::function<void(double, double)> &cbfunc);
	void SetKeyCallback(const std::function<void(int, int, int, int)> &cbfunc);
	void SetMouseCallback(const std::function<void(int, int, int)> &cbfunc);
	void SetResizeCallback(const std::function<void(int, int)> &cbfunc);
	bool ShouldClose() const;
	void SwapBuffers();

public:
	static GLcontext *FromWindow(GLFWwindow *window);
};
