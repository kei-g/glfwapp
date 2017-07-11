#pragma once

template<typename T, size_t N>
struct GLpoint
{
	T val[N];

	// デフォルトコンストラクタ
	GLpoint()
	{
		for (auto i = size_t(); i < N; i++) {
			new(val + i)T();
		}
	}

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

	// コンストラクタ
	GLpoint(T v1, T v2)
		: val{ v1, v2 }
	{
	}

	// コピーコンストラクタ
	GLpoint(const GLpoint<T, N> &p)
	{
		for (auto i = size_t(); i < N; i++) {
			new(val + i)T(p.val[i]);
		}
	}

	// ムーブコンストラクタ
	GLpoint(GLpoint<T, N> &&p)
	{
		for (auto i = size_t(); i < N; i++) {
			new(val + i)T(p.val[i]);
		}
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
struct GLpoint2 : public GLpoint<T, 2>
{
	T &x, &y;

	// デフォルトコンストラクタ
	GLpoint2()
		: GLpoint(), x(val[0]), y(val[1])
	{
	}

	// コンストラクタ
	GLpoint2(T x, T y)
		: GLpoint(x, y), x(val[0]), y(val[1])
	{
	}

	// コピーコンストラクタ
	GLpoint2(const GLpoint2<T> &p)
		: GLpoint(p), x(val[0]), y(val[1])
	{
	}

	// ムーブコンストラクタ
	GLpoint2(GLpoint2<T> &&p) = delete;

	// 型変換
	template<typename U>
	operator GLpoint2<U>() const
	{
		return GLpoint2<U>{ static_cast<U>(x), static_cast<U>(y) };
	}
};

typedef typename GLpoint2<GLdouble> GLpoint2d;
typedef typename GLpoint2<GLfloat> GLpoint2f;

template<typename T>
struct GLpoint3 : public GLpoint<T, 3>
{
	T &x, &y, &z;

	// デフォルトコンストラクタ
	GLpoint3()
		: GLpoint(), x(val[0]), y(val[1]), z(val[2])
	{
	}

	// コンストラクタ
	GLpoint3(T x, T y, T z)
		: GLpoint(x, y, z), x(val[0]), y(val[1]), z(val[2])
	{
	}

	// コピーコンストラクタ
	GLpoint3(const GLpoint3<T> &p)
		: GLpoint(p), x(val[0]), y(val[1]), z(val[2])
	{
	}

	// ムーブコンストラクタ
	GLpoint3(GLpoint3<T> &&p)
		: GLpoint(std::move(p)), x(val[0]), y(val[1]), z(val[2])
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
