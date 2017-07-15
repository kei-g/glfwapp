#pragma once

#include "GLpoint.hpp"

struct GLcamera : public GLpoint3d
{
	// 視線の向き(deg)
	GLpoint2d gaze;

	// デフォルトコンストラクタ
	GLcamera();

	// コンストラクタ
	GLcamera(double x, double y, double z, double direction = 0);

	// 視線ベクトル
	GLpoint3d GetVector() const;

	// 視線を適用する
	void LookAt();

	// 視線の方向へ進む
	void MoveAhead(double distance);

	// 横方向に移動する
	void Shift(double distance);
};
