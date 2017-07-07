#pragma once

template<typename T>
struct GLcolor4
{
	T val[4], &red, &green, &blue, &alpha;

	// デフォルトコンストラクタ
	GLcolor4()
		: GLcolor4(0, 0, 0, 1)
	{
	}

	// コンストラクタ
	GLcolor4(T red, T green, T blue, T alpha = 1.0)
		: val{ red, green, blue, alpha }, red(val[0]), green(val[1]), blue(val[2]), alpha(val[3])
	{
	}

	// 型変換
	template<typename U>
	operator GLcolor4<U>() const
	{
		return GLcolor4<U>{ static_cast<U>(red), static_cast<U>(green), static_cast<U>(blue), static_cast<U>(alpha) };
	}

	// プリミティブポインタへの変換
	operator const T*() const
	{
		return val;
	}

	// プリミティブポインタへの変換
	operator T*()
	{
		return val;
	}
};

typedef typename GLcolor4<GLdouble> GLcolor4d;
typedef typename GLcolor4<GLfloat> GLcolor4f;

namespace GLcolor {
	// 白
	static const GLcolor4d White = GLcolor4d{ 1, 1, 1 };

	// とても明るいグレー
	static const GLcolor4d BrightGray = GLcolor4d{ 0.75, 0.75, 0.75 };

	// 明るいグレー
	static const GLcolor4d LightGray = GLcolor4d{ 0.5, 0.5, 0.5 };

	// グレー
	static const GLcolor4d Gray = GLcolor4d{ 0.25, 0.25, 0.25 };

	// 暗いグレー
	static const GLcolor4d DarkGray = GLcolor4d{ 0.125, 0.125, 0.125 };
}
