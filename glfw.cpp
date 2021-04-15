#include "glfw.hpp"

#if defined(_MSC_VER)
int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow
)
#else
int main(int argc, char *argv[])
#endif
{
#if defined(_MSC_VER)
	UNREFERENCED_PARAMETER(hInstance);
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);
	UNREFERENCED_PARAMETER(nCmdShow);

	ImmDisableIME(-1);
#endif

	try {
		auto app = MyApplication();
		auto context = app.CreateContext(1280, 720, "glfw");
		if (!context) {
			throw std::runtime_error("Can't create window");
		}
		app.Run(context);
	}
	catch (const std::exception &e) {
#if defined(_MSC_VER)
		MessageBox(nullptr, e.what(), nullptr, MB_ICONHAND);
#else
		std::cerr << e.what() << std::endl;
#endif
	}

	return 0;
}
