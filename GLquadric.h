#pragma once

class GLquadric
{
protected:
	GLUquadric *state;

public:
	// デフォルトコンストラクタ
	GLquadric();

	// コンストラクタ
	GLquadric(GLUquadric *state);

	// デストラクタ
	virtual ~GLquadric();

public:
	// 描画する
	virtual void Draw(GLdouble rotation) = 0;

	// テクスチャ有効
	void EnableTexture();

	// 描画方式
	void SetDrawStyle(GLenum drawStyle);

	// 法線
	void SetNormals(GLenum normals);

	// 球体を描画する
	void Sphere(GLdouble radius, GLint slices, GLint stacks);
};
