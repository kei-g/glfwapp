#include "PS4axes.h"

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
	camera.gaze.y += R3.y;
	if (camera.gaze.y < -45) {
		camera.gaze.y = -45;
	}
	else if (45 < camera.gaze.y) {
		camera.gaze.y = 45;
	}

	const auto v = L3.Rotate(camera.gaze.x * M_PI / 180);
	camera.x -= v.y / 64;
	camera.z += v.x / 64;
}
