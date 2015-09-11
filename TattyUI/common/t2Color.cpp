#define NOMINMAX
#include <TattyUI/common/t2Color.h>


namespace TattyUI
{
	template<typename T>
	t2Color_<T>::t2Color_<T>() : r(0), g(0), b(0), a(0)
	{
	}

	template<typename T>
	t2Color_<T>::t2Color_<T>(T r, T g, T b, T a) : r(r), g(g), b(b), a(a)
	{
	}

    template<typename T>
    t2Color_<T>::t2Color_<T>(t2Color_<T> &c) : r(c.r), g(c.g), b(c.b), a(c.a)
    {
    }


	template<typename T>
	void t2Color_<T>::set(t2Color_<T>& color)
	{
		set(color.r, color.g, color.b, color.a);
	}

	template<typename T>
	void t2Color_<T>::set(T r, T g, T b, T a)
	{
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}

	template<typename T>
	void t2Color_<T>::zero()
	{
		r = g = b = 0;
		a = limit();
	}

	template<typename T>
	void t2Color_<T>::print()
	{
		t2Log("t2Color ");
		t2Log("(r:%d, g:%d, b:%d, a:%d)\n", r, g, b, a);
	}


	template<typename T>
	float t2Color_<T>::limit()
	{
		// --!pixelType代表的数值类型可表示的最大值
        return numeric_limits<T>::max();
	}

	template<>
	float t2Color_<float>::limit()
	{
		return 1.f;
	}

	template class t2Color_<char>;
	template class t2Color_<unsigned char>;
	template class t2Color_<short>;
	template class t2Color_<unsigned short>;
	template class t2Color_<int>;
	template class t2Color_<unsigned int>;
	template class t2Color_<long>;
	template class t2Color_<unsigned long>;
	template class t2Color_<float>;
	template class t2Color_<double>;
}