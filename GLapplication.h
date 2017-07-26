#pragma once

#include "GLcontext.h"

class GLapplication
{
public:
	// デフォルトコンストラクタ
	GLapplication();

	// デストラクタ
	virtual ~GLapplication();

	// ウィンドウを生成する
	virtual std::shared_ptr<GLcontext> CreateContext(int width, int height, const char *title);

	// アプリケーションを実行する
	virtual void Run(std::shared_ptr<GLcontext> &context) = 0;
};
