#pragma once

// トーラスの頂点情報
struct GLtorusVertex
{
	// 余弦
	GLdouble cos;

	// 正弦
	GLdouble sin;

	// 媒介変数
	GLdouble t;

	// コンストラクタ
	GLtorusVertex(GLdouble t, GLdouble radian);

	// トーラスの頂点情報を生成する
	static std::vector<GLtorusVertex> Build(GLint N);

	// 暗黙の型変換
	operator GLdouble() const;
};
