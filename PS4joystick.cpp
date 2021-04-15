#include "PS4joystick.h"

static void ApplyThreshold(float &value)
{
	if (-0.125f <= value && value <= 0.125f) {
		value = 0;
	}
}

static void ApplyThreshold(GLpoint2f &value)
{
	ApplyThreshold(value.x);
	ApplyThreshold(value.y);
}

static void ApplyThreshold(PS4axes &value)
{
	ApplyThreshold(value.L2);
	ApplyThreshold(value.L3);
	ApplyThreshold(value.R2);
	ApplyThreshold(value.R3);
}

PS4joystick::PS4joystick(int id)
	: id(id)
{
}

PS4joystick::~PS4joystick()
{
}

void PS4joystick::Poll(PS4axes &axes) const
{
	auto n = 0;
	auto a = glfwGetJoystickAxes(id, &n);
	if (a) {
		new(&axes)PS4axes(a);
		ApplyThreshold(axes);
	}
}
