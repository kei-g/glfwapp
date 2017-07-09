#include "GLcamera.h"

GLcamera::GLcamera()
	: GLcamera(0, 0, 0, 0)
{
}

GLcamera::GLcamera(double x, double y, double z, double direction)
	: GLpoint3d(x, y, z), direction(direction), lookAtCenter(false)
{
}

void GLcamera::LookAt()
{
	if (lookAtCenter) {
		gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);
	}
	else {
		gluLookAt(x, y, z, x + cos(direction * M_PI / 180), y, z + sin(direction * M_PI / 180), 0, 1, 0);
	}
}

void GLcamera::MoveAhead(double distance)
{
	x += cos(direction * M_PI / 180) * distance;
	z += sin(direction * M_PI / 180) * distance;
}
