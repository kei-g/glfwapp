#include "GLtorus.h"

void GLtorus::Draw(const GLtorusVertex &s, const GLtorusVertex &t) const
{
	glNormal3d(t.cos * s.cos, t.sin, t.cos * s.sin);
	glTexCoord2d(1 - s, t - offset);
	const auto c = radiusOuter + radiusInner * t.cos;
	glVertex3d(c * s.cos, radiusInner * t.sin, c * s.sin);
}

GLtorus::GLtorus(GLdouble radiusOuter, GLdouble radiusInner, GLint slices, GLint stacks)
	: GLquadric(nullptr), offset(0), radiusInner(radiusInner), radiusOuter(radiusOuter), slices(GLtorusVertex::Build(slices)), stacks(GLtorusVertex::Build(stacks))
{
}

void GLtorus::Draw(GLdouble rotation)
{
	glRotated(rotation, 0, 1, 0);

	glBegin(GL_TRIANGLE_STRIP);
	const auto cb = slices.cbegin();
	const auto ce = slices.cend() - 1;
	for (auto s = cb; s != ce;) {
		const auto &s0 = *s;
		const auto &s1 = *++s;
		for (const auto &t : stacks) {
			Draw(s0, t);
			Draw(s1, t);
		}
	}
	glEnd();
}
