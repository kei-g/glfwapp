// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#if defined(_MSC_VER)
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>
#endif

#if !defined(_MSC_VER)
#include <cassert>
#endif
#define _USE_MATH_DEFINES
#include <cmath>
#include <deque>
#if !defined(_MSC_VER)
#include <fstream>
#endif
#include <functional>
#include <iomanip>
#if !defined(_MSC_VER)
#include <iostream>
#endif
#include <memory>
#if __clang_major < 11
namespace std {
	namespace numbers {
		constexpr double pi = 3.141592653589793238462643383279502884197169399375105820975L;
	}
}
#else
#include <numbers>
#endif
#include <sstream>
#include <thread>
#include <vector>

#define GLFW_INCLUDE_GLU

#include <GLFW/glfw3.h>

constexpr GLdouble GLepsilon = static_cast<double>(1) / 8192;
