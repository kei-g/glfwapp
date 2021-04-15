#include "GLcamera.h"

GLcamera::GLcamera()
	: GLcamera(0, 0, 0, 0)
{
}

GLcamera::GLcamera(double x, double y, double z, double azimuth, double elevation)
	: GLpoint3d(x, y, z), gaze(azimuth, elevation)
{
}

GLpoint3d GLcamera::GetGazeVector() const
{
	return Gaze<GLpoint3d>([](auto ac, auto as, auto ec, auto es) {
#if defined(_MSC_VER)
		return GLpoint3d(ac * ec, as * ec, es);
#else
		return GLpoint3d(ac * ec, -es, as * ec);
#endif
	});
}

void GLcamera::LookAt()
{
#if defined(_MSC_VER)
	auto c = *this;
	c += GetGazeVector();
	gluLookAt(x, y, z, c.x, c.y, c.z, 0, 0, 1);
#else
	auto c = GLpoint3d(x, y, z);
	c += GetGazeVector();
	gluLookAt(x, y, z, c.x, c.y, c.z, 0, 1, 0);
#endif
}

void GLcamera::MoveAhead(double distance)
{
	auto c = GetGazeVector();
	c *= distance;
	*this += c;
}

void GLcamera::Shift(double distance)
{
	auto c = GLpoint3d(0, 1, 0).cross(GetGazeVector());
	c *= distance;
	*this += c;
}
