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
	// テクスチャ有効
	void EnableTexture();

	// 描画方式
	void SetDrawStyle(GLenum drawStyle);

	// 法線
	void SetNormals(GLenum normals);

	// 球体を描画する
	void Sphere(GLdouble radius, GLint slices, GLint stacks);

	// トーラスを描画する
	void Torus(GLdouble radius, GLdouble small, GLint slices, GLint stacks, const std::function<void(GLdouble, GLdouble)> &texCoord = [](GLdouble s, GLdouble t) { glTexCoord2d(1 - s, t - 0.5); });
};
