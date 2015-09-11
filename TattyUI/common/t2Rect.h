#ifndef T2_RECT_H
#define T2_RECT_H

#include <TattyUI/common/t2Vector2.h>

namespace TattyUI
{
	class t2Rect
	{
	public:
		// 左上角(x, y)
		t2Rect(float x, float y, float width, float height) :x(x), y(y), width(width), height(height)
		{
		}

		inline bool inside(const t2Point2f& p) const;
		inline bool inside(float x, float y) const;

		float x;
		float y;
		float width;
		float height;
	};

	inline bool t2Rect::inside(float x, float y) const
	{
		return inside(t2Point2f(x, y));
	}

	inline bool t2Rect::inside(const t2Point2f& p) const
	{
		return p.x > x && p.y > y
			&& p.x < x + width && p.y < y + height;
	}
}

#endif