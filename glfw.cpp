#include "glfw.hpp"

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
		auto app = MyApplication();
		auto context = app.CreateContext(1280, 720, "glfw");
		if (!context) {
			throw std::runtime_error("Can't create window");
		}
		app.Run(context);
	}
	catch (const std::exception &e) {
		MessageBox(nullptr, e.what(), nullptr, MB_ICONHAND);
	}

	return 0;
}
