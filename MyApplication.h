#pragma once

#include "GLapplication.h"
#include "GLcamera.h"
#include "GLsphere.h"
#include "GLtexture.h"
#include "GLtorus.h"

class MyApplication : public GLapplication, public GLcamera {
private:
	struct DragContext {
		// ボタン
		const int button;

		// 前回の座標
		GLpoint2d last;

		// 状態
		const int mods;

		// ドラッグ開始座標
		const GLpoint2d origin;

		// コンストラクタ
		DragContext(int button, int mods, const GLpoint2d &cursor)
			: button(button), last(cursor), mods(mods), origin(cursor)
		{
		}
	};

	// アスペクト比
	GLdouble aspect;

	// マウスカーソルの座標
	GLpoint2d cursor;

	// ドラッグ情報
	std::shared_ptr<DragContext> dragContext;

	// テクスチャ画像の読み込み要求
	std::deque<size_t> queue;

	// 回転
	GLdouble rotation;

	// 球面
	GLsphere sphere;

	// 描画対象
	GLquadric *target;

	// テクスチャ
	std::vector<GLtexture> textures;

	// トーラス
	GLtorus torus;

	// ウィンドウの高さ
	int windowHeight;

	// ウィンドウの幅
	int windowWidth;

	// 必要な機能を有効にする
	void ApplyCapabilities();

	// 使用するテクスチャを指定する
	void BindTextureAt(size_t pos);

	// カーソルイベントを処理する
	void CursorEvent(GLdouble x, GLdouble y);

	// ドラッグイベントを処理する
	void DragEvent(GLdouble dx, GLdouble dy);

	// キーイベントを処理する
	void KeyEvent(int key, int scan, int action, int mods);

	// マウスイベントを処理する
	void MouseEvent(int button, int action, int mods);

	// スクロールイベントを処理する
	void ScrollEvent(double x, double y);

protected:
	// 描画する[描画スレッドから呼ばれる]
	virtual void Render();

	// 初期化する[描画スレッドから呼ばれる]
	virtual void Setup();

	// 更新する[描画スレッドから呼ばれる]
	virtual void Update();

public:
	// デフォルトコンストラクタ
	MyApplication();

	// ウィンドウを生成する
	virtual std::shared_ptr<GLcontext> CreateContext(int width, int height, const char *title);

	// アプリケーションを実行する
	virtual void Run(std::shared_ptr<GLcontext> &context);
};
