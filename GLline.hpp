#pragma once

#include "GLpoint.hpp"

template<template<typename> typename C, typename T>
struct GLline
{
	// 始点
	const C<T> a;

	// 終点
	const C<T> b;

	// ベクトル
	const C<T> v;

	// 線分の長さの2乗
	const T d;

	// デフォルトコンストラクタ
	GLline()
		: d(std::numeric_limits<double>().signaling_NaN())
	{
	}

	// コンストラクタ
	GLline(const C<T> &a, const C<T> &b)
		: a(a), b(b), v(b - a), d(v.dot(v))
	{
	}

	// デストラクタ
	virtual ~GLline()
	{
	}

	// 媒介変数を適用する
	const C<T> operator()(const T &t) const
	{
		return a + v * t;
	}

	// 直線との交点を求める
	template<typename U>
	bool GetCrossPoint(const GLline<C, T> &line, C<T> *c, U tolerance) const
	{
		const auto e = v.dot(line.v);
		const auto det = e * e - d * line.d;
		if (det == 0) { // 並行なので交わらない
			return false;
		}
		const auto s = line.a - a;
		const auto i = v.dot(s);
		const auto j = line.v.dot(s);
		const auto m = -line.d * i + e * j;
		const auto n = -e * i + d * j;
		const auto p = (*this)(m);
		const auto q = line(n);
		if (c) {
			*c = (p + q) / 2;
		}
		const auto pq = q - p;
		return 0 <= m && m <= 1 && 0 <= n && n <= 1 && pq.dot(pq) <= tolerance * tolerance;
	}

	// 任意の座標からこの直線に垂ろした垂線の足の座標を求める
	bool GetFootOfPerpendicular(const C<T> &point, C<T> *f, T *c = nullptr) const
	{
		const auto t = v.dot(p - a) / d;
		if (f) {
			*f = a + v * t;
		}
		if (c) {
			*c = t;
		}
		return 0 <= t && t <= 1;
	}
};

template<typename T>
struct GLline2 : public GLline<GLpoint2, T>
{
	// 方位角
	const double azimuth;

	// コンストラクタ
	GLline2(const GLpoint<T, 2> &a, const GLpoint<T, 2> &b)
		: GLline(a, b), azimuth(atan2(v.y, v.x))
	{
	}
};

typedef typename GLline2<double> GLline2d;
typedef typename GLline2<float> GLline2f;
typedef typename GLline2<int> GLline2i;

template<typename T>
struct GLline3 : public GLline<GLpoint3, T>
{
	// 方位角
	const double azimuth;

	// 仰角
	const double elevation;

	// コンストラクタ
	GLline3(const GLpoint<T, 3> &a, const GLpoint<T, 3> &b)
		: GLline(a, b), azimuth(atan2(v.y, v.x)), elevation(atan2(v.z, sqrt(v.x * v.x + v.y * v.y)))
	{
	}
};

typedef typename GLline3<double> GLline3d;
typedef typename GLline3<float> GLline3f;
typedef typename GLline3<int> GLline3i;
