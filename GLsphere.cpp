#include "GLsphere.h"

// Ô“¹ŒXÎŠp
constexpr auto Obliquity = 23.43;

GLsphere::GLsphere(GLdouble radius, GLint slices, GLint stacks)
	: radius(radius), slices(slices), stacks(stacks)
{
}

void GLsphere::Draw(GLdouble rotation)
{
	glRotated(rotation, 0, cos(Obliquity * M_PI / 180), sin(Obliquity * M_PI / 180)); // ’n²‚É‘Î‚·‚é‰ñ“]
	glRotated(Obliquity - 90, 1, 0, 0); // ’n²‚ÌŒX‚«‚ğÄŒ»‚·‚é
	Sphere(radius, slices, stacks);
}
