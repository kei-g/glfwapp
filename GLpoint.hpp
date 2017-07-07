#pragma once

template<typename T, size_t N>
struct GLpoint
{
	T val[N];

	// コンストラクタ
	GLpoint(T v1, T v2, T v3, T v4)
		: val{ v1, v2, v3, v4 }
	{
	}

	// コンストラクタ
	GLpoint(T v1, T v2, T v3)
		: val{ v1, v2, v3 }
	{
	}

	// デストラクタ
	virtual ~GLpoint()
	{
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

template<typename T>
struct GLpoint3 : public GLpoint<T, 3>
{
	T &x, &y, &z;

	// デフォルトコンストラクタ
	GLpoint3()
		: GLpoint3(0, 0, 0)
	{
	}

	// コンストラクタ
	GLpoint3(T x, T y, T z)
		: GLpoint{ x, y, z }, x(val[0]), y(val[1]), z(val[2])
	{
	}

	// 型変換
	template<typename U>
	operator GLpoint3<U>() const
	{
		return GLpoint3<U>{ static_cast<U>(x), static_cast<U>(y), static_cast<U>(z) };
	}

	// 型変換
	template<typename U>
	GLpoint<T, 4> operator +(U w) const
	{
		return GLpoint<T, 4>{ x, y, z, static_cast<T>(w) };
	}
};

typedef typename GLpoint3<GLdouble> GLpoint3d;
typedef typename GLpoint3<GLfloat> GLpoint3f;
