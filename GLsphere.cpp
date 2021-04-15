#include "GLsphere.h"

// 赤道傾斜角
constexpr auto Obliquity = 23.43;

GLsphere::GLsphere(GLdouble radius, GLint slices, GLint stacks)
	: radius(radius), slices(slices), stacks(stacks)
{
}

void GLsphere::Draw(GLdouble rotation)
{
	glRotated(rotation, 0, cos(Obliquity * M_PI / 180), sin(Obliquity * M_PI / 180)); // 地軸に対する回転
	glRotated(Obliquity - 90, 1, 0, 0); // 地軸の傾きを再現する
	Sphere(radius, slices, stacks);
}
