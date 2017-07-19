#pragma once

namespace cage {
	template<typename T>
	T clip(T a, T b, T c)
	{
		return a < b ? (b < c ? b : c) : (a < c ? a : c);
	}
}
