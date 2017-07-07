#include "GLmaterial.h"

GLmaterial::GLmaterial()
	: GLmaterial(GLcolor4f(), GLcolor4f(0.25, 0.25, 0.25), GLcolor4f(0.75, 0.75, 0.75))
{
}

GLmaterial::GLmaterial(const GLcolor4f &ambient, const GLcolor4f &diffuse, const GLcolor4f &specular, GLfloat shininess)
	: ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess)
{
}

GLmaterial::~GLmaterial()
{
}

void GLmaterial::operator()(GLenum face) const
{
	glMaterialfv(face, GL_AMBIENT, ambient.val);
	glMaterialfv(face, GL_DIFFUSE, diffuse.val);
	glMaterialfv(face, GL_SPECULAR, specular.val);
	glMaterialf(face, GL_SHININESS, shininess);
}

const GLmaterial GLmaterial::Jade = GLmaterial{
	GLcolor4f{ 0.135f,     0.2225f,   0.1575f   },
	GLcolor4f{ 0.54f,      0.89f,     0.63f     },
	GLcolor4f{ 0.316228f,  0.316228f, 0.316228f },
	12.8f,
};

const GLmaterial GLmaterial::Light = GLmaterial{
	GLcolor::LightGray,
	GLcolor::BrightGray,
	GLcolor::White,
	32.0f,
};

const GLmaterial GLmaterial::Ruby = GLmaterial{
	GLcolor4f{ 0.1745f,   0.01175f,  0.01175f  },
	GLcolor4f{ 0.61424f,  0.04136f,  0.04136f  },
	GLcolor4f{ 0.727811f, 0.626959f, 0.626959f },
	76.8f,
};

const GLmaterial GLmaterial::White = GLmaterial{
	GLcolor::White,
	GLcolor::White,
	GLcolor::White,
	32.0f,
};
