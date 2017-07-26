#pragma once

#include "GLcontext.h"

class GLapplication
{
	friend class GLcontext;

protected:
	// 描画する[描画スレッドから呼ばれる]
	virtual void Render() = 0;

	// 初期化する[描画スレッドから呼ばれる]
	virtual void Setup() = 0;

	// 更新する[描画スレッドから呼ばれる]
	virtual void Update() = 0;

public:
	// デフォルトコンストラクタ
	GLapplication();

	// デストラクタ
	virtual ~GLapplication();

	// ウィンドウを生成する
	virtual std::shared_ptr<GLcontext> CreateContext(int width, int height, const char *title);

	// アプリケーションを実行する[メインスレッドから呼ばれる]
	virtual void Run(std::shared_ptr<GLcontext> &context);
};
