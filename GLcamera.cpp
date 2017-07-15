#include "GLcamera.h"

GLcamera::GLcamera()
	: GLcamera(0, 0, 0, 0)
{
}

GLcamera::GLcamera(double x, double y, double z, double direction)
	: GLpoint3d(x, y, z), gaze(direction, 0)
{
}

GLpoint3d GLcamera::GetVector() const
{
	const auto horz = gaze.x * M_PI / 180;
	const auto vert = gaze.y * M_PI / 180;
	return GLpoint3d(cos(horz) * cos(vert), -sin(vert), sin(horz));
}

void GLcamera::LookAt()
{
	auto c = *this;
	c += GetVector();
	gluLookAt(x, y, z, c.x, c.y, c.z, 0, 1, 0);
}

void GLcamera::MoveAhead(double distance)
{
	auto c = GetVector();
	c *= distance;
	*this += c;
}

void GLcamera::Shift(double distance)
{
	auto c = GLpoint3d(0, 1, 0).cross(GetVector());
	c *= distance;
	*this += c;
}
