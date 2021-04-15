#pragma once

#include "GLcamera.h"
#include "GLpoint.hpp"

struct PS4axes
{
	// L2軸
	float L2;

	// L3軸
	GLpoint2f L3;

	// R2軸
	float R2;

	// R3軸
	GLpoint2f R3;

	// デフォルトコンストラクタ
	PS4axes();

	// コンストラクタ
	PS4axes(const float *axes);

	// デストラクタ
	virtual ~PS4axes();

	// カメラに適用する
	virtual void operator()(GLcamera &camera) const;
};
