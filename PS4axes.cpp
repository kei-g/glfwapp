#include "PS4axes.h"

#include "GLquaternion.hpp"
#include "cage.hpp"

PS4axes::PS4axes()
{
}

#if defined(_MSC_VER)
PS4axes::PS4axes(const float *axes)
	: L2((axes[3] + 1) / 2), L3(axes[0], axes[1]), R2((axes[4] + 1) / 2), R3(axes[2], axes[5])
#else
PS4axes::PS4axes(const float *axes)
	: L2(0), L3(axes[0], -axes[1]), R2(0), R3(-axes[3], -axes[4])
#endif
{
}

PS4axes::~PS4axes()
{
}

void PS4axes::operator()(GLcamera &camera) const
{
	camera.gaze.x = std::fmod(camera.gaze.x - R3.x * 2, 360);
	camera.gaze.y = cage::clip(-85.0, camera.gaze.y - R3.y, 85.0);

	const auto q = make_quaternion<double>(GLpoint3d(0, 0, -1), (camera.gaze.x - 90) * std::numbers::pi / 180);
#if defined(_MSC_VER)
	auto d = (~q * GLpoint3d(L3.x, L3.y, 0) * q).imag<GLpoint3d>();
#else
	auto d = (~q * GLpoint3d(0, L3.y, L3.x) * q).imag<GLpoint3d>();
#endif
	d *= static_cast<double>(1) / 64;
	camera += d;
}
