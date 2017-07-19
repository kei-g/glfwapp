#include "PS4axes.h"

#include "cage.hpp"

PS4axes::PS4axes()
{
}

PS4axes::PS4axes(const float *axes)
	: L2((axes[3] + 1) / 2), L3(axes[0], axes[1]), R2((axes[4] + 1) / 2), R3(axes[2], axes[5])
{
}

PS4axes::~PS4axes()
{
}

void PS4axes::operator()(GLcamera &camera) const
{
	camera.gaze.x = fmod(camera.gaze.x + R3.x * 2, 360);
	camera.gaze.y = cage::clip(-45.0, camera.gaze.y + R3.y, 45.0);

	const auto horz = (camera.gaze.x + 90) * M_PI / 180;
	const auto vert = camera.gaze.y * M_PI / 180;
	camera.x += (cos(horz) * L3.x - sin(horz) * L3.y) / 64;
	camera.z += (sin(horz) * L3.x + cos(horz) * L3.y) / 64;
}
