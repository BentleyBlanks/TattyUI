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
    void TattyUI::t2Color_<T>::set(const string& value)
    {
        // 只支持十六进制色
        static unsigned char hexColor[7];
        strcpy((char*) hexColor, value.c_str());
        if(strlen((char*) hexColor) != 7 || hexColor[0] != '#')
        {
            t2PrintError("十六进制色定义有误, 应以#开头, 紧跟3个十六进制数, 共7位");
            return;
        }

        int r, g, b;
        unsigned char tempColor[2];
        // r
        tempColor[0] = hexColor[1];
        tempColor[1] = hexColor[2];
        sscanf((const char*) tempColor, "%02x", &r);
        // g
        tempColor[0] = hexColor[3];
        tempColor[1] = hexColor[4];
        sscanf((const char*) tempColor, "%02x", &g);
        // b
        tempColor[0] = hexColor[5];
        tempColor[1] = hexColor[6];
        sscanf((const char*) tempColor, "%02x", &b);

        // 十六进制色不包含透明度，因此直接保持alpha不变
        set(r, g, b, a);
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