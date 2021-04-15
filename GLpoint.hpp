#pragma once

template<typename T, size_t N>
struct GLpoint
{
	T val[N];

	// デフォルトコンストラクタ
	GLpoint()
	{
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
	GLpoint(const GLpoint<T, N> &point)
	{
		for (auto i = size_t(); i < N; i++) {
			new(val + i)T(point[i]);
		}
	}

	// ムーブコンストラクタ
	GLpoint(GLpoint<T, N> &&point)
	{
		for (auto i = size_t(); i < N; i++) {
			new(val + i)T(point[i]);
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

	// インデックス
	const T &operator[](size_t index) const
	{
		return val[index];
	}

	// インデックス
	T &operator[](size_t index)
	{
		return val[index];
	}

	// 加算
	virtual GLpoint<T, N> &operator +=(const GLpoint<T, N> &point)
	{
		for (auto i = size_t(); i < N; i++) {
			val[i] += point[i];
		}
		return *this;
	}

	// 乗算
	virtual GLpoint<T, N> operator +(const GLpoint<T, N> &point) const
	{
		auto v = GLpoint<T, N>();
		for (auto i = size_t(); i < N; i++) {
			new(v.val + i)T(val[i] + point[i]);
		}
		return v;
	}

	// 減算
	virtual GLpoint<T, N> operator -(const GLpoint<T, N> &point) const
	{
		auto v = GLpoint<T, N>();
		for (auto i = size_t(); i < N; i++) {
			new(v.val + i)T(val[i] - point[i]);
		}
		return v;
	}

	// 乗算
	virtual GLpoint<T, N> &operator *=(const T arg)
	{
		for (auto i = size_t(); i < N; i++) {
			val[i] *= arg;
		}
		return *this;
	}

	// 乗算
	virtual GLpoint<T, N> operator *(const T arg) const
	{
		auto v = GLpoint<T, N>();
		for (auto i = size_t(); i < N; i++) {
			new(v.val + i)T(val[i] * arg);
		}
		return v;
	}

	// 内積
	virtual T dot(const GLpoint<T, N> &point) const
	{
		auto d = T();
		for (auto i = size_t(); i < N; i++) {
			d += val[i] * point[i];
		}
		return d;
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
	GLpoint2(const GLpoint<T, 2> &p)
		: GLpoint(p), x(val[0]), y(val[1])
	{
	}

	// ムーブコンストラクタ
	GLpoint2(GLpoint<T, 2> &&p)
		: GLpoint(p), x(val[0]), y(val[1])
	{
	}

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
	GLpoint3(const GLpoint<T, 3> &p)
		: GLpoint(p), x(val[0]), y(val[1]), z(val[2])
	{
	}

	// ムーブコンストラクタ
	GLpoint3(GLpoint<T, 3> &&p)
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

	// 外積
	GLpoint3 cross(const GLpoint3<T> &point) const
	{
		return GLpoint3(y * point.z - z * point.y, z * point.x - x * point.z, x * point.y - y * point.x);
	}
};

typedef typename GLpoint3<GLdouble> GLpoint3d;
typedef typename GLpoint3<GLfloat> GLpoint3f;
