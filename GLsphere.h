#pragma once

#include "GLquadric.h"

class GLsphere : public GLquadric
{
private:
	// 半径
	GLdouble radius;

	// 横方向の分割数
	GLint slices;

	// 縦方向の分割数
	GLint stacks;

public:
	// コンストラクタ
	GLsphere(GLdouble radius, GLint slices, GLint stacks);

	// 描画する
	virtual void Draw(GLdouble rotation);
};
