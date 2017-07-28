#include "PS4axes.h"

#include "GLquaternion.hpp"
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
	camera.gaze.x = fmod(camera.gaze.x - R3.x * 2, 360);
	camera.gaze.y = cage::clip(-85.0, camera.gaze.y - R3.y, 85.0);

	const auto q = make_quaternion<double>(GLpoint3d(0, 0, -1), (camera.gaze.x - 90) * M_PI / 180);
	auto d = (~q * GLpoint3d(L3.x, L3.y, 0) * q).imag<GLpoint3d>();
	d *= static_cast<double>(1) / 64;
	camera += d;
}
