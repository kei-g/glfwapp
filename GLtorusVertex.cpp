#include "GLtorusVertex.h"

GLtorusVertex::GLtorusVertex(GLdouble t, GLdouble radian)
	: cos(std::cos(radian)), sin(std::sin(radian)), t(t)
{
}

std::vector<GLtorusVertex> GLtorusVertex::Build(GLint N)
{
	auto vertices = std::vector<GLtorusVertex>();
	vertices.reserve(N + 1);
	for (auto i = 0; i <= N; i++) {
		vertices.emplace_back(static_cast<GLdouble>(i) / N, std::numbers::pi * i * 2 / N);
	}
	return vertices;
}

GLtorusVertex::operator GLdouble() const
{
	return t;
}
