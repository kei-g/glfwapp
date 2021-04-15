#pragma once

#include "GLcolor4.hpp"

struct GLmaterial
{
	GLcolor4f ambient;
	GLcolor4f diffuse;
	GLcolor4f specular;
	GLfloat shininess;

	// デフォルトコンストラクタ
	GLmaterial();

	// コンストラクタ
	GLmaterial(const GLcolor4f &ambient, const GLcolor4f &diffuse, const GLcolor4f &specular, GLfloat shininess = 32.0f);

	// デストラクタ
	virtual ~GLmaterial();

	// この材質を適用する
	void operator()(GLenum face) const;

	// 翡翠
	static const GLmaterial Jade;

	// 明るい
	static const GLmaterial Light;

	// ルビー
	static const GLmaterial Ruby;

	// 白
	static const GLmaterial White;
};
