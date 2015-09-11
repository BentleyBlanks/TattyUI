#ifndef T2_MATH_H
#define T2_MATH_H

#include <TattyUI/common/t2Settings.h>

namespace TattyUI
{
	int t2NextPow2(int a);

	// is p2 inside rect(p1, width, height);
	bool pointInsideRect(int p1x, int p1y, int width, int height, int p2x, int p2y);
}

#endif