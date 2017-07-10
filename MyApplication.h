#pragma once

#include "GLapplication.h"
#include "GLcamera.h"
#include "GLsphere.h"
#include "GLtexture.h"
#include "GLtorus.h"

class MyApplication : public GLapplication, public GLcamera {
private:
	// アスペクト比
	GLdouble aspect;

	// マウスカーソルの座標
	GLpoint3d cursor;

	// ドラッグ情報
	std::shared_ptr<GLpoint3d> drag;

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

	// キーイベントを処理する
	void KeyEvent(int key, int scan, int action, int mods);

	// マウスイベントを処理する
	void MouseEvent(int button, int action, int mods);

public:
	// デフォルトコンストラクタ
	MyApplication();

	// 必要な機能を有効にする
	void ApplyCapabilities();

	// 使用するテクスチャを指定する
	void BindTextureAt(size_t pos);

	// ウィンドウを生成する
	virtual std::shared_ptr<GLcontext> CreateContext(int width, int height, const char *title);

	// 描画する
	void Render();

	// 更新する
	void Update();
};
