#include "glfw.h"

// 赤道傾斜角
constexpr auto Obliquity = 23.43;

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow
)
{
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	ImmDisableIME(-1);

	try {
		auto app = GLapplication();

		auto context = app.CreateContext(1280, 720, "glfw");
		if (!context) {
			throw std::exception("Can't create window");
		}

		context->MakeCurrent();
		glfwSwapInterval(1);

		glEnable(GL_BLEND);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0, 0, 0, 1);

		// テクスチャ作成
		stbi_set_flip_vertically_on_load(1);
		auto w = 0, h = 0, c = 0;
		auto buf = stbi_load("earth.jpg", &w, &h, &c, 0);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, buf);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		stbi_image_free(buf);

		// カメラ
		auto camera = GLcamera{ -3, 0.25, 0 };

		// キー入力
		context->SetKeyCallback([&](int key, int scan, int action, int mods) {
			switch (key) {
			case GLFW_KEY_F:
				camera.MoveAhead(static_cast<double>(1) / 128);
				break;
			case GLFW_KEY_B:
				camera.MoveAhead(static_cast<double>(-1) / 128);
				break;
			case GLFW_KEY_UP:
				camera.y += static_cast<double>(1) / 128;
				break;
			case GLFW_KEY_DOWN:
				camera.y -= static_cast<double>(1) / 128;
				break;
			case GLFW_KEY_LEFT:
				camera.direction -= 0.5;
				break;
			case GLFW_KEY_RIGHT:
				camera.direction += 0.5;
				break;
			}
		});

		// アスペクト比
		auto aspect = 16.0 / 9;
		context->SetResizeCallback([&aspect](int w, int h) {
			aspect = static_cast<double>(w) / h;
		});

		// 球を生成
		auto sphere = gluNewQuadric();
		gluQuadricDrawStyle(sphere, GLU_FILL);
		gluQuadricNormals(sphere, GLU_SMOOTH);
		gluQuadricTexture(sphere, GL_TRUE);

		auto angle = double();
		while (!context->ShouldClose()) {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(60, aspect, GLepsilon, 128);

			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			camera.LookAt();

			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

			// カメラの位置に光源を配置
			glLightfv(GL_LIGHT0, GL_POSITION, static_cast<GLpoint3f>(camera) + 1); // 0: 並行光源, 0以外: 点光源
			glLightfv(GL_LIGHT0, GL_AMBIENT, static_cast<GLcolor4f>(GLcolor::Gray));
			glLightfv(GL_LIGHT0, GL_DIFFUSE, static_cast<GLcolor4f>(GLcolor::LightGray));
			glLightfv(GL_LIGHT0, GL_SPECULAR, static_cast<GLcolor4f>(GLcolor::White));

			// グリッドを描画
			glBegin(GL_LINES);
			glColor4d(1, 1, 0, 1);
			GLmaterial::Jade(GL_FRONT);
			for (auto i = -100; i <= 100; i++) {
				glVertex3d(static_cast<double>(i) / 10, 0, -10);
				glVertex3d(static_cast<double>(i) / 10, 0, +10);
				glVertex3d(-10, 0, static_cast<double>(i) / 10);
				glVertex3d(+10, 0, static_cast<double>(i) / 10);
			}
			glEnd();

			// 球を描画
			GLmaterial::Light(GL_FRONT);
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			glTranslated(0, 1, 0);
			glRotated(angle, 0, cos(Obliquity * M_PI / 180), sin(Obliquity * M_PI / 180)); // 地軸に対する回転
			glRotated(Obliquity - 90, 1, 0, 0); // 地軸の傾きを再現する
			gluSphere(sphere, 1, 32, 32);
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			// 球を回転させる
			angle += 0.0625;
			if (360 < angle) {
				angle -= 360;
			}

			context->SwapBuffers();

			glfwWaitEventsTimeout(0.015625);
		}

		// 球を破棄
		gluDeleteQuadric(sphere);
	}
	catch (const std::exception &e) {
		MessageBox(nullptr, e.what(), nullptr, MB_ICONHAND);
	}

	return 0;
}
