#pragma once

#include "GLpoint.hpp"

struct GLcamera : public GLpoint3d
{
	// 視線の向き(deg)
	double direction;

	// 中心を見る
	bool lookAtCenter;

	// デフォルトコンストラクタ
	GLcamera();

	// コンストラクタ
	GLcamera(double x, double y, double z, double direction = 0);

	// 視線を適用する
	void LookAt();

	// 視線の方向へ進む
	void MoveAhead(double distance);
};
