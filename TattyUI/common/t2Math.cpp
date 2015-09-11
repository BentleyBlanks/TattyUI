#include <TattyUI/common/t2Math.h>

namespace TattyUI
{
	int t2NextPow2(int a)
	{
		// from nehe.gamedev.net lesson 43
		int rval = 1;
		while(rval < a) rval <<= 1;
		return rval;
	}

	// is p2 inside rect(p1, width, height);
	bool pointInsideRect(int p1x, int p1y, int width, int height, int p2x, int p2y)
	{
		return p2x<max(p1x, p1x + width) && p2y<max(p1y, p1y + height)
			&& p2x>min(p1x, p1x + width) && p2y>min(p1y, p1y + height);
	}
}
