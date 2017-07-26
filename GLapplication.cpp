#include "GLapplication.h"

GLapplication::GLapplication()
{
	if (!glfwInit()) {
		throw std::exception("Can't initialize GLFW");
	}
}

GLapplication::~GLapplication()
{
	glfwTerminate();
}

std::shared_ptr<GLcontext> GLapplication::CreateContext(int width, int height, const char *title)
{
	auto window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	return window ? std::make_shared<GLcontext>(*this, window) : nullptr;
}

void GLapplication::Run(std::shared_ptr<GLcontext> &context)
{
	context->Run();
}
