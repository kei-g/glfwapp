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
