#pragma once

#include "GLpoint.hpp"

struct GLcamera : public GLpoint3d
{
	// 視線の向き(deg)
	GLpoint2d gaze;

	// デフォルトコンストラクタ
	GLcamera();

	// コンストラクタ
	GLcamera(double x, double y, double z, double azimuth = 0, double elevation = 0);

	// 視線から任意のオブジェクトを生成する
	template<typename T, typename P>
	inline T Gaze(const P &predicate) const
	{
		const auto azimuth = gaze.x * M_PI / 180;
		const auto elevation = gaze.y * M_PI / 180;
		return predicate(cos(azimuth), sin(azimuth), cos(elevation), sin(elevation));
	}

	// 視線ベクトル
	GLpoint3d GetGazeVector() const;

	// 視線を適用する
	void LookAt();

	// 視線の方向へ進む
	void MoveAhead(double distance);

	// 横方向に移動する
	void Shift(double distance);
};
