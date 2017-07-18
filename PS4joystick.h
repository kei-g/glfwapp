#pragma once

#include "PS4axes.h"

class PS4joystick
{
private:
	// ID
	const int id;

public:
	// コンストラクタ
	PS4joystick(int id);

	// デストラクタ
	virtual ~PS4joystick();

	// 状態を取得する
	void Poll(PS4axes &axes) const;
};
