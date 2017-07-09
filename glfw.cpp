#include "glfw.h"

stbi_uc *stbi_load_from_resource(HMODULE hModule, int resourceId, LPCTSTR resourceType, int *width, int *height, int *comp, int req_comp = 0)
{
	auto resourceInfo = FindResource(hModule, MAKEINTRESOURCE(resourceId), resourceType);
	auto resource = LoadResource(hModule, resourceInfo);
	auto image = LockResource(resource);
	auto size = SizeofResource(hModule, resourceInfo);
	return stbi_load_from_memory(static_cast<stbi_uc *>(image), static_cast<int>(size), width, height, comp, req_comp);
}

void glLoadTextureFromResource(HMODULE hModule, int resourceId, LPCTSTR resourceType)
{
	auto w = 0, h = 0, c = 0;
	auto buf = stbi_load_from_resource(hModule, resourceId, resourceType, &w, &h, &c);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, buf);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	stbi_image_free(buf);
}

// 赤道傾斜角
constexpr auto Obliquity = 23.43;

// リソースID
constexpr int resourceIDs[] = { IDR_IMAGE_EARTH, IDR_IMAGE_DQ2, IDR_IMAGE_DQ3, IDR_IMAGE_DQ4, IDR_IMAGE_DQ5 };

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow
)
{
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
		GLuint textures[5] = { 0 };
		glGenTextures(_countof(textures), textures);
		stbi_set_flip_vertically_on_load(1);
		for (auto i = 0; i < _countof(textures); i++) {
			glBindTexture(GL_TEXTURE_2D, textures[i]);
			glLoadTextureFromResource(hInstance, resourceIDs[i], TEXT("Image"));
		}
		glBindTexture(GL_TEXTURE_2D, textures[0]);

		// 表示オブジェクトの種類
		auto sphere = true;

		// トーラスのテクスチャの開始オフセット
		auto torusOffset = 0.5;

		// カメラ
		auto camera = GLcamera{ -3, 0, 0 };

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
			case GLFW_KEY_1:
				glBindTexture(GL_TEXTURE_2D, textures[0]);
				break;
			case GLFW_KEY_2:
				glBindTexture(GL_TEXTURE_2D, textures[1]);
				break;
			case GLFW_KEY_3:
				glBindTexture(GL_TEXTURE_2D, textures[2]);
				break;
			case GLFW_KEY_4:
				glBindTexture(GL_TEXTURE_2D, textures[3]);
				break;
			case GLFW_KEY_5:
				glBindTexture(GL_TEXTURE_2D, textures[4]);
				break;
			case GLFW_KEY_S:
				sphere = true;
				break;
			case GLFW_KEY_T:
				sphere = false;
				break;
			case GLFW_KEY_O:
				if (!sphere) {
					torusOffset += static_cast<double>(1) / 128;
				}
				break;
			case GLFW_KEY_L:
				if (!sphere) {
					torusOffset -= static_cast<double>(1) / 128;
				}
				break;
			case GLFW_KEY_C:
				if (action == GLFW_RELEASE) {
					camera.lookAtCenter = !camera.lookAtCenter;
				}
				break;
			}
		});

		// アスペクト比
		auto aspect = 16.0 / 9;
		context->SetResizeCallback([&aspect](int w, int h) {
			aspect = static_cast<double>(w) / h;
		});

		// オブジェクトを生成
		auto quadric = GLquadric();
		quadric.SetDrawStyle(GLU_FILL);
		quadric.SetNormals(GLU_SMOOTH);
		quadric.EnableTexture();

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

			// オブジェクトを描画
			GLmaterial::Light(GL_FRONT);
			glPushMatrix();
			glEnable(GL_TEXTURE_2D);
			if (sphere) {
				glRotated(angle, 0, cos(Obliquity * M_PI / 180), sin(Obliquity * M_PI / 180)); // 地軸に対する回転
				glRotated(Obliquity - 90, 1, 0, 0); // 地軸の傾きを再現する
				quadric.Sphere(1, 32, 32);
			}
			else {
				glRotated(angle, 0, 1, 0);
				quadric.Torus(0.875, 0.375, 128, 128, [&torusOffset](GLdouble s, GLdouble t) {
					glTexCoord2d(1 - s, t - torusOffset);
				});
			}
			glDisable(GL_TEXTURE_2D);
			glPopMatrix();

			// オブジェクトを回転させる
			angle += 0.0625;
			if (360 < angle) {
				angle -= 360;
			}

			context->SwapBuffers();

			glfwWaitEventsTimeout(0.015625);
		}
	}
	catch (const std::exception &e) {
		MessageBox(nullptr, e.what(), nullptr, MB_ICONHAND);
	}

	return 0;
}
