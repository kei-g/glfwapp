// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>

#define _USE_MATH_DEFINES
#include <cmath>
#include <deque>
#include <functional>
#include <iomanip>
#include <memory>
#include <sstream>
#include <thread>
#include <vector>

#define GLFW_INCLUDE_GLU

#include <GLFW/glfw3.h>

constexpr GLdouble GLepsilon = static_cast<double>(1) / 8192;
