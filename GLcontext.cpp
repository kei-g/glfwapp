#include "GLcontext.h"

GLcontext::GLcontext(GLapplication &app, GLFWwindow *window)
	: app(app), window(window)
{
	glfwSetWindowUserPointer(window, this);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow *window, int width, int height) {
		glViewport(0, 0, width, height);
		auto context = GLcontext::FromWindow(window);
		if (context && context->resizeEvent) {
			context->resizeEvent(width, height);
		}
	});
}

GLcontext::~GLcontext()
{
	glfwDestroyWindow(window);
}

void GLcontext::MakeCurrent()
{
	glfwMakeContextCurrent(window);
}

void GLcontext::SetCursorCallback(const std::function<void(double, double)> &cbfunc)
{
	const auto firstTime = !cursorEvent;
	cursorEvent = cbfunc;
	if (firstTime) {
		glfwSetCursorPosCallback(window, [](GLFWwindow *window, double x, double y) {
			auto context = GLcontext::FromWindow(window);
			if (context && context->cursorEvent) {
				context->cursorEvent(x, y);
			}
		});
	}
}

void GLcontext::SetKeyCallback(const std::function<void(int, int, int, int)> &cbfunc)
{
	const auto firstTime = !keyEvent;
	keyEvent = cbfunc;
	if (firstTime) {
		glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scan, int action, int mods) {
			auto context = GLcontext::FromWindow(window);
			if (context && context->keyEvent) {
				context->keyEvent(key, scan, action, mods);
			}
		});
	}
}

void GLcontext::SetMouseCallback(const std::function<void(int, int, int)> &cbfunc)
{
	const auto firstTime = !mouseEvent;
	mouseEvent = cbfunc;
	if (firstTime) {
		glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
			auto context = GLcontext::FromWindow(window);
			if (context && context->mouseEvent) {
				context->mouseEvent(button, action, mods);
			}
		});
	}
}

void GLcontext::SetResizeCallback(const std::function<void(int, int)> &cbfunc)
{
	resizeEvent = cbfunc;
}

void GLcontext::SetScrollCallback(const std::function<void(double, double)> &cbfunc)
{
	const auto firstTime = !scrollEvent;
	scrollEvent = cbfunc;
	if (firstTime) {
		glfwSetScrollCallback(window, [](GLFWwindow *window, double x, double y) {
			auto context = GLcontext::FromWindow(window);
			if (context && context->scrollEvent) {
				context->scrollEvent(x, y);
			}
		});
	}
}

bool GLcontext::ShouldClose() const
{
	return !!glfwWindowShouldClose(window);
}

void GLcontext::SwapBuffers()
{
	glfwSwapBuffers(window);
}

GLcontext *GLcontext::FromWindow(GLFWwindow *window)
{
	return static_cast<GLcontext *>(glfwGetWindowUserPointer(window));
}
