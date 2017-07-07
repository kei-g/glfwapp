#pragma once

#include "GLcontext.h"

class GLapplication
{
public:
	GLapplication();
	virtual ~GLapplication();

public:
	virtual std::shared_ptr<GLcontext> CreateContext(int width, int height, const char *title);
};
