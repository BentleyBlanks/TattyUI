#ifndef T2_COLOR_H
#define T2_COLOR_H

#include <TattyUI/common/t2Settings.h>
#include <limits>

namespace TattyUI
{
	enum t2ColorComponent
	{
		T2_COLOR_RED = 0,
		T2_COLOR_GREEN,
		T2_COLOR_BLUE,
		T2_COLOR_ALPHA
	};

	template<typename T>
	class t2Color_
	{
	public:
		t2Color_<T>();

		t2Color_<T>(T r, T g, T b, T a = limit());

        t2Color_<T>(t2Color_<T> &c);

		void set(t2Color_<T>& color);

		void set(T r, T g, T b, T a = limit());

		void zero();

		void print();

		static float limit();

		T r, g, b, a;
	};

	//A typedef representing an 8-bit RGBA color.
	typedef t2Color_<uint8> t2Color;

	typedef t2Color_<uint16> t2ShortColor;

	typedef t2Color_<float> t2FloatColor;
}

#endif