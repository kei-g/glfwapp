#pragma once

#include "GLapplication.h"
#include "GLcamera.h"
#include "GLquadric.h"
#include "GLtexture.h"

class MyApplication : public GLapplication, public GLcamera, protected GLquadric {
private:
	// アスペクト比
	GLdouble aspect;

	// 回転
	GLdouble rotation;

	// 球orトーラス
	bool sphere;

	// テクスチャ
	std::vector<GLtexture> textures;

	// トーラスのオフセット
	GLdouble torusOffset;

	// キーイベントを処理する
	void KeyEvent(int key, int scan, int action, int mods);

public:
	// デフォルトコンストラクタ
	MyApplication(HMODULE hModule);

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
