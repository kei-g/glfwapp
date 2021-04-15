#pragma once

#include "GLquadric.h"
#include "GLtorusVertex.h"

class GLtorus : public GLquadric
{
private:
	// 小半径
	GLdouble radiusInner;

	// 大半径
	GLdouble radiusOuter;

	// 縦方向
	const std::vector<GLtorusVertex> slices;

	// 横方向
	const std::vector<GLtorusVertex> stacks;

public:
	// 開始オフセット(deg)
	GLdouble offset;

private:
	//
	void Draw(const GLtorusVertex &s, const GLtorusVertex &t) const;

public:
	// コンストラクタ
	GLtorus(GLdouble radiusOuter, GLdouble radiusInner, GLint slices, GLint stacks);

	// 描画する
	virtual void Draw(GLdouble rotation);
};
