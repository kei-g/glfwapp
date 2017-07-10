#include "MyApplication.h"

#include "GLmaterial.h"
#include "resource.h"

void MyApplication::KeyEvent(int key, int scan, int action, int mods)
{
	switch (key) {
	case GLFW_KEY_F:
		MoveAhead(static_cast<double>(1) / 128);
		break;
	case GLFW_KEY_B:
		MoveAhead(static_cast<double>(-1) / 128);
		break;
	case GLFW_KEY_UP:
		y += static_cast<double>(1) / 128;
		break;
	case GLFW_KEY_DOWN:
		y -= static_cast<double>(1) / 128;
		break;
	case GLFW_KEY_LEFT:
		direction -= 0.5;
		break;
	case GLFW_KEY_RIGHT:
		direction += 0.5;
		break;
	case GLFW_KEY_1:
		textures[0].Bind();
		break;
	case GLFW_KEY_2:
		textures[1].Bind();
		break;
	case GLFW_KEY_3:
		textures[2].Bind();
		break;
	case GLFW_KEY_4:
		textures[3].Bind();
		break;
	case GLFW_KEY_5:
		textures[4].Bind();
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
			lookAtCenter = !lookAtCenter;
		}
		break;
	}
}

// 赤道傾斜角
constexpr auto Obliquity = 23.43;

// リソースID
constexpr int resourceIDs[] = { IDR_IMAGE_EARTH, IDR_IMAGE_DQ2, IDR_IMAGE_DQ3, IDR_IMAGE_DQ4, IDR_IMAGE_DQ5 };

MyApplication::MyApplication(HMODULE hModule)
	: GLcamera(-3, 0, 0), rotation(0), sphere(true), textures(GLtexture::Generate(hModule, resourceIDs, TEXT("Image"))), torusOffset(0)
{
	SetDrawStyle(GLU_FILL);
	SetNormals(GLU_SMOOTH);
	EnableTexture();
}

void MyApplication::ApplyCapabilities()
{
	glfwSwapInterval(1);

	glEnable(GL_BLEND);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearColor(0, 0, 0, 1);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
}

void MyApplication::BindTextureAt(size_t pos)
{
	textures[pos].Bind();
}

std::shared_ptr<GLcontext> MyApplication::CreateContext(int width, int height, const char *title)
{
	auto context = GLapplication::CreateContext(width, height, title);

	context->SetKeyCallback([&](int key, int scan, int action, int mods) {
		KeyEvent(key, scan, action, mods);
	});

	aspect = static_cast<double>(width) / height;
	context->SetResizeCallback([&](int w, int h) {
		aspect = static_cast<double>(w) / h;
	});

	return context;
}

void MyApplication::Render()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, aspect, GLepsilon, 128);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	LookAt();

	// 消去
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// カメラの位置に光源を配置
	glLightfv(GL_LIGHT0, GL_POSITION, static_cast<GLpoint3f>(*this) + 1); // 0: 並行光源, 0以外: 点光源
	glLightfv(GL_LIGHT0, GL_AMBIENT, static_cast<GLcolor4f>(GLcolor::Gray));
	glLightfv(GL_LIGHT0, GL_DIFFUSE, static_cast<GLcolor4f>(GLcolor::LightGray));
	glLightfv(GL_LIGHT0, GL_SPECULAR, static_cast<GLcolor4f>(GLcolor::White));

	// オブジェクトを描画する
	GLmaterial::Light(GL_FRONT);
	glPushMatrix();
	glEnable(GL_TEXTURE_2D);
	if (sphere) {
		glRotated(rotation, 0, cos(Obliquity * M_PI / 180), sin(Obliquity * M_PI / 180)); // 地軸に対する回転
		glRotated(Obliquity - 90, 1, 0, 0); // 地軸の傾きを再現する
		Sphere(1, 32, 32);
	}
	else {
		glRotated(rotation, 0, 1, 0);
		Torus(0.875, 0.375, 128, 128, [&](GLdouble s, GLdouble t) {
			glTexCoord2d(1 - s, t - torusOffset);
		});
	}
	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}

void MyApplication::Update()
{
	// オブジェクトを回転させる
	rotation += 0.0625;
	if (360 < rotation) {
		rotation -= 360;
	}
}
