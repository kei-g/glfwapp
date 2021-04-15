#pragma once

// 四元数
template<typename T>
struct GLquaternion {
	// 虚数部
	T i, j, k;

	// 実数部
	T w;

	// デフォルトコンストラクタ
	GLquaternion()
	{
	}

	// コンストラクタ
	template<typename U>
	GLquaternion(const U i, const U j, const U k, const U w)
		: i(static_cast<T>(i)), j(static_cast<T>(j)), k(static_cast<T>(k)), w(static_cast<T>(w))
	{
	}

	// デストラクタ
	virtual ~GLquaternion()
	{
	}

	// 共役四元数
	virtual GLquaternion conj() const
	{
		return GLquaternion(-i, -j, -k, w);
	}

	// 虚数部
	template<typename U>
	U imag() const
	{
		return U(i, j, k);
	}

	// 共役四元数
	virtual GLquaternion operator~() const
	{
		return conj();
	}

	// 乗算
	template<typename U>
	GLquaternion operator*(const GLquaternion<U> &q) const
	{
		return GLquaternion(
			i * q.w + w * q.i + j * q.k - k * q.j,
			j * q.w + w * q.j + k * q.i - i * q.k,
			k * q.w + w * q.k + i * q.j - j * q.i,
			w * q.w - i * q.i - j * q.j - k * q.k
		);
	}

	// 乗算
	template<template<typename> typename C, typename U>
	GLquaternion operator*(const C<U> &v) const
	{
		return GLquaternion(
			w * v.x + j * v.z - k * v.y,
			w * v.y + k * v.x - i * v.z,
			w * v.z + i * v.y - j * v.x,
			-(i * v.x + j * v.y + k * v.z)
		);
	}

	// 型変換
	template<typename U>
	operator GLquaternion<U>() const
	{
		return GLquaternion<U>(static_cast<U>(i), static_cast<U>(j), static_cast<U>(k), static_cast<U>(w));
	}
};

// 任意の軸に対する回転のための四元数
template<typename T, template<typename> typename C, typename U>
static auto make_quaternion(const C<U> &v, double theta)
{
#if defined(_MSC_VER)
	_ASSERT(v.dot(v) == 1);
#else
	assert(v.dot(v) == 1);
#endif
	const auto a = theta / 2;
	const auto c = std::cos(a);
	const auto s = std::sin(a);
	return GLquaternion<T>(v.x * s, v.y * s, v.z * s, c);
}
