#include "GLquadric.h"
#include "GLtorusVertex.h"

GLquadric::GLquadric()
	: GLquadric(gluNewQuadric())
{
}

GLquadric::GLquadric(GLUquadric *state)
	: state(state)
{
}

GLquadric::~GLquadric()
{
	if (state) {
		gluDeleteQuadric(state);
		state = nullptr;
	}
}

void GLquadric::EnableTexture()
{
	gluQuadricTexture(state, GL_TRUE);
}

void GLquadric::SetDrawStyle(GLenum drawStyle)
{
	gluQuadricDrawStyle(state, drawStyle);
}

void GLquadric::SetNormals(GLenum normals)
{
	gluQuadricNormals(state, normals);
}

void GLquadric::Sphere(GLdouble radius, GLint slices, GLint stacks)
{
	gluSphere(state, radius, slices, stacks);
}

void GLquadric::Torus(GLdouble radius, GLdouble small, GLint slices, GLint stacks, const std::function<void(GLdouble, GLdouble)> &texCoord)
{
	auto func = [&](const GLtorusVertex &s, const GLtorusVertex &t) {
		glNormal3d(t.cos * s.cos, t.sin, t.cos * s.sin);
		texCoord(s, t);
		const auto c = radius + small * t.cos;
		glVertex3d(c * s.cos, small * t.sin, c * s.sin);
	};

	// åoê¸
	const auto meridian = GLtorusVertex::Build(slices);

	// à‹ê¸
	const auto longitude = GLtorusVertex::Build(stacks);

	glBegin(GL_TRIANGLE_STRIP);
	for (auto s = 0; s < slices; s++) {
		for (auto t = 0; t <= stacks; t++) {
			func(meridian[s], longitude[t]);
			func(meridian[s + 1], longitude[t]);
		}
	}
	glEnd();
}
