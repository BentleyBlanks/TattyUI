#define NOMINMAX
#include <TattyUI/common/t2Color.h>
#include <regex>
#include <map>

namespace TattyUI
{
    static std::map<string, string> colorTable;

	template<typename T>
    t2Color_<T>::t2Color_<T>() : r(255), g(255), b(255), a(255)
	{
        initColorTable();
	}

	template<typename T>
	t2Color_<T>::t2Color_<T>(T r, T g, T b, T a) : r(r), g(g), b(b), a(a)
	{
        initColorTable();
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
    void TattyUI::t2Color_<T>::set(string value)
    {
        // 支持十六进制色与rgb(r, g, b)形式

        int parseR, parseG, parseB;
        static unsigned char hexColor[7];
        strcpy((char*) hexColor, value.c_str());
        if(strlen((char*) hexColor) == 7 && hexColor[0] == '#')
        {
            // 根据十六进制色值重设颜色
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

            set(r, g, b, a);
        }
        else
        {
            // rgb(r, g, b)形式
            // not good
            if(value.substr(0, 4) == "rgb(" && value.substr(value.length() - 1, 1) == ")")
            {
                regex re(R"raw(\d+)raw");
                smatch m;
                string temp = value;
                // 强制最多循环三次 防止rgb(1, 2, 3, 4,...)等恶意情况出现
                int i = 0;
                while(regex_search(temp, m, re) && i <= 3)
                {
                    string color = m[0];
                    switch(i)
                    {
                    case 0:
                        r = atoi(color.c_str());
                        break;
                    case 1:
                        g = atoi(color.c_str());
                        break;
                    case 2:
                        b = atoi(color.c_str());
                        break;
                    default:
                        break;
                    }

                    temp = m.suffix().str();
                    i++;
                }
            }
            else
            {
                // 找到指定常量色并返回其十六进制色
                // 根据十六进制色值重设颜色
                string temp = find(value.c_str());
                if(temp != "")
                    set(temp);
            }
        }

        // 十六进制色不包含透明度，因此直接保持alpha不变
        //set(r, g, b, a);
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
    string t2Color_<T>::find(string colorName)
    {
        // 不区分大小写
        for(auto c : colorTable)
        {
            if(!strcasecmp(c.first.c_str(), colorName.c_str()))
                return c.second;
        }
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


    template<typename T>
    void t2Color_<T>::initColorTable()
    {
        static bool bInit = false;
        if(bInit)
            return;

        colorTable.insert(std::pair<string, string>("AliceBlue", "#F0F8FF"));
        colorTable.insert(std::pair<string, string>("AntiqueWhite", "#FAEBD7"));
        colorTable.insert(std::pair<string, string>("Aqua", "#00FFFF"));
        colorTable.insert(std::pair<string, string>("Aquamarine", "#7FFFD4"));
        colorTable.insert(std::pair<string, string>("Azure", "#F0FFFF"));
        colorTable.insert(std::pair<string, string>("Beige", "#F5F5DC"));
        colorTable.insert(std::pair<string, string>("Bisque", "#FFE4C4"));
        colorTable.insert(std::pair<string, string>("Black", "#000000"));
        colorTable.insert(std::pair<string, string>("BlanchedAlmond", "#FFEBCD"));
        colorTable.insert(std::pair<string, string>("Blue", "#0000FF"));
        colorTable.insert(std::pair<string, string>("BlueViolet", "#8A2BE2"));
        colorTable.insert(std::pair<string, string>("Brown", "#A52A2A"));
        colorTable.insert(std::pair<string, string>("BurlyWood", "#DEB887"));
        colorTable.insert(std::pair<string, string>("CadetBlue", "#5F9EA0"));
        colorTable.insert(std::pair<string, string>("Chartreuse", "#7FFF00"));
        colorTable.insert(std::pair<string, string>("Chocolate", "#D2691E"));
        colorTable.insert(std::pair<string, string>("Coral", "#FF7F50"));
        colorTable.insert(std::pair<string, string>("CornflowerBlue", "#6495ED"));
        colorTable.insert(std::pair<string, string>("Cornsilk", "#FFF8DC"));
        colorTable.insert(std::pair<string, string>("Crimson", "#DC143C"));
        colorTable.insert(std::pair<string, string>("Cyan", "#00FFFF"));
        colorTable.insert(std::pair<string, string>("DarkBlue", "#00008B"));
        colorTable.insert(std::pair<string, string>("DarkCyan", "#008B8B"));
        colorTable.insert(std::pair<string, string>("DarkGoldenRod", "#B8860B"));
        colorTable.insert(std::pair<string, string>("DarkGray", "#A9A9A9"));
        colorTable.insert(std::pair<string, string>("DarkGreen", "#006400"));
        colorTable.insert(std::pair<string, string>("DarkKhaki", "#BDB76B"));
        colorTable.insert(std::pair<string, string>("DarkMagenta", "#8B008B"));
        colorTable.insert(std::pair<string, string>("DarkOliveGreen", "#556B2F"));
        colorTable.insert(std::pair<string, string>("Darkorange", "#FF8C00"));
        colorTable.insert(std::pair<string, string>("DarkOrchid", "#9932CC"));
        colorTable.insert(std::pair<string, string>("DarkRed", "#8B0000"));
        colorTable.insert(std::pair<string, string>("DarkSalmon", "#E9967A"));
        colorTable.insert(std::pair<string, string>("DarkSeaGreen", "#8FBC8F"));
        colorTable.insert(std::pair<string, string>("DarkSlateBlue", "#483D8B"));
        colorTable.insert(std::pair<string, string>("DarkSlateGray", "#2F4F4F"));
        colorTable.insert(std::pair<string, string>("DarkTurquoise", "#00CED1"));
        colorTable.insert(std::pair<string, string>("DarkViolet", "#9400D3"));
        colorTable.insert(std::pair<string, string>("DeepPink", "#FF1493"));
        colorTable.insert(std::pair<string, string>("DeepSkyBlue", "#00BFFF"));
        colorTable.insert(std::pair<string, string>("DimGray", "#696969"));
        colorTable.insert(std::pair<string, string>("DodgerBlue", "#1E90FF"));
        colorTable.insert(std::pair<string, string>("Feldspar", "#D19275"));
        colorTable.insert(std::pair<string, string>("FireBrick", "#B22222"));
        colorTable.insert(std::pair<string, string>("FloralWhite", "#FFFAF0"));
        colorTable.insert(std::pair<string, string>("ForestGreen", "#228B22"));
        colorTable.insert(std::pair<string, string>("Fuchsia", "#FF00FF"));
        colorTable.insert(std::pair<string, string>("Gainsboro", "#DCDCDC"));
        colorTable.insert(std::pair<string, string>("GhostWhite", "#F8F8FF"));
        colorTable.insert(std::pair<string, string>("Gold", "#FFD700"));
        colorTable.insert(std::pair<string, string>("GoldenRod", "#DAA520"));
        colorTable.insert(std::pair<string, string>("Gray", "#808080"));
        colorTable.insert(std::pair<string, string>("Green", "#008000"));
        colorTable.insert(std::pair<string, string>("GreenYellow", "#ADFF2F"));
        colorTable.insert(std::pair<string, string>("HoneyDew", "#F0FFF0"));
        colorTable.insert(std::pair<string, string>("HotPink", "#FF69B4"));
        colorTable.insert(std::pair<string, string>("IndianRed", "#CD5C5C"));
        colorTable.insert(std::pair<string, string>("Indigo", "#4B0082"));
        colorTable.insert(std::pair<string, string>("Ivory", "#FFFFF0"));
        colorTable.insert(std::pair<string, string>("Khaki", "#F0E68C"));
        colorTable.insert(std::pair<string, string>("Lavender", "#E6E6FA"));
        colorTable.insert(std::pair<string, string>("LavenderBlush", "#FFF0F5"));
        colorTable.insert(std::pair<string, string>("LawnGreen", "#7CFC00"));
        colorTable.insert(std::pair<string, string>("LemonChiffon", "#FFFACD"));
        colorTable.insert(std::pair<string, string>("LightBlue", "#ADD8E6"));
        colorTable.insert(std::pair<string, string>("LightCoral", "#F08080"));
        colorTable.insert(std::pair<string, string>("LightCyan", "#E0FFFF"));
        colorTable.insert(std::pair<string, string>("LightGoldenRodYellow", "#FAFAD2"));
        colorTable.insert(std::pair<string, string>("LightGrey", "#D3D3D3"));
        colorTable.insert(std::pair<string, string>("LightGreen", "#90EE90"));
        colorTable.insert(std::pair<string, string>("LightPink", "#FFB6C1"));
        colorTable.insert(std::pair<string, string>("LightSalmon", "#FFA07A"));
        colorTable.insert(std::pair<string, string>("LightSeaGreen", "#20B2AA"));
        colorTable.insert(std::pair<string, string>("LightSkyBlue", "#87CEFA"));
        colorTable.insert(std::pair<string, string>("LightSlateBlue", "#8470FF"));
        colorTable.insert(std::pair<string, string>("LightSlateGray", "#778899"));
        colorTable.insert(std::pair<string, string>("LightSteelBlue", "#B0C4DE"));
        colorTable.insert(std::pair<string, string>("LightYellow", "#FFFFE0"));
        colorTable.insert(std::pair<string, string>("Lime", "#00FF00"));
        colorTable.insert(std::pair<string, string>("LimeGreen", "#32CD32"));
        colorTable.insert(std::pair<string, string>("Linen", "#FAF0E6"));
        colorTable.insert(std::pair<string, string>("Magenta", "#FF00FF"));
        colorTable.insert(std::pair<string, string>("Maroon", "#800000"));
        colorTable.insert(std::pair<string, string>("MediumAquaMarine", "#66CDAA"));
        colorTable.insert(std::pair<string, string>("MediumBlue", "#0000CD"));
        colorTable.insert(std::pair<string, string>("MediumOrchid", "#BA55D3"));
        colorTable.insert(std::pair<string, string>("MediumPurple", "#9370D8"));
        colorTable.insert(std::pair<string, string>("MediumSeaGreen", "#3CB371"));
        colorTable.insert(std::pair<string, string>("MediumSlateBlue", "#7B68EE"));
        colorTable.insert(std::pair<string, string>("MediumSpringGreen", "#00FA9A"));
        colorTable.insert(std::pair<string, string>("MediumTurquoise", "#48D1CC"));
        colorTable.insert(std::pair<string, string>("MediumVioletRed", "#C71585"));
        colorTable.insert(std::pair<string, string>("MidnightBlue", "#191970"));
        colorTable.insert(std::pair<string, string>("MintCream", "#F5FFFA"));
        colorTable.insert(std::pair<string, string>("MistyRose", "#FFE4E1"));
        colorTable.insert(std::pair<string, string>("Moccasin", "#FFE4B5"));
        colorTable.insert(std::pair<string, string>("NavajoWhite", "#FFDEAD"));
        colorTable.insert(std::pair<string, string>("Navy", "#000080"));
        colorTable.insert(std::pair<string, string>("OldLace", "#FDF5E6"));
        colorTable.insert(std::pair<string, string>("Olive", "#808000"));
        colorTable.insert(std::pair<string, string>("OliveDrab", "#6B8E23"));
        colorTable.insert(std::pair<string, string>("Orange", "#FFA500"));
        colorTable.insert(std::pair<string, string>("OrangeRed", "#FF4500"));
        colorTable.insert(std::pair<string, string>("Orchid", "#DA70D6"));
        colorTable.insert(std::pair<string, string>("PaleGoldenRod", "#EEE8AA"));
        colorTable.insert(std::pair<string, string>("PaleGreen", "#98FB98"));
        colorTable.insert(std::pair<string, string>("PaleTurquoise", "#AFEEEE"));
        colorTable.insert(std::pair<string, string>("PaleVioletRed", "#D87093"));
        colorTable.insert(std::pair<string, string>("PapayaWhip", "#FFEFD5"));
        colorTable.insert(std::pair<string, string>("PeachPuff", "#FFDAB9"));
        colorTable.insert(std::pair<string, string>("Peru", "#CD853F"));
        colorTable.insert(std::pair<string, string>("Pink", "#FFC0CB"));
        colorTable.insert(std::pair<string, string>("Plum", "#DDA0DD"));
        colorTable.insert(std::pair<string, string>("PowderBlue", "#B0E0E6"));
        colorTable.insert(std::pair<string, string>("Purple", "#800080"));
        colorTable.insert(std::pair<string, string>("Red", "#FF0000"));
        colorTable.insert(std::pair<string, string>("RosyBrown", "#BC8F8F"));
        colorTable.insert(std::pair<string, string>("RoyalBlue", "#4169E1"));
        colorTable.insert(std::pair<string, string>("SaddleBrown", "#8B4513"));
        colorTable.insert(std::pair<string, string>("Salmon", "#FA8072"));
        colorTable.insert(std::pair<string, string>("SandyBrown", "#F4A460"));
        colorTable.insert(std::pair<string, string>("SeaGreen", "#2E8B57"));
        colorTable.insert(std::pair<string, string>("SeaShell", "#FFF5EE"));
        colorTable.insert(std::pair<string, string>("Sienna", "#A0522D"));
        colorTable.insert(std::pair<string, string>("Silver", "#C0C0C0"));
        colorTable.insert(std::pair<string, string>("SkyBlue", "#87CEEB"));
        colorTable.insert(std::pair<string, string>("SlateBlue", "#6A5ACD"));
        colorTable.insert(std::pair<string, string>("SlateGray", "#708090"));
        colorTable.insert(std::pair<string, string>("Snow", "#FFFAFA"));
        colorTable.insert(std::pair<string, string>("SpringGreen", "#00FF7F"));
        colorTable.insert(std::pair<string, string>("SteelBlue", "#4682B4"));
        colorTable.insert(std::pair<string, string>("Tan", "#D2B48C"));
        colorTable.insert(std::pair<string, string>("Teal", "#008080"));
        colorTable.insert(std::pair<string, string>("Thistle", "#D8BFD8"));
        colorTable.insert(std::pair<string, string>("Tomato", "#FF6347"));
        colorTable.insert(std::pair<string, string>("Turquoise", "#40E0D0"));
        colorTable.insert(std::pair<string, string>("Violet", "#EE82EE"));
        colorTable.insert(std::pair<string, string>("VioletRed", "#D02090"));
        colorTable.insert(std::pair<string, string>("Wheat", "#F5DEB3"));
        colorTable.insert(std::pair<string, string>("White", "#FFFFFF"));
        colorTable.insert(std::pair<string, string>("WhiteSmoke", "#F5F5F5"));
        colorTable.insert(std::pair<string, string>("Yellow", "#FFFF00"));
        colorTable.insert(std::pair<string, string>("YellowGreen", "#9ACD32"));
        colorTable.insert(std::pair<string, string>("Black", "#000000"));
        colorTable.insert(std::pair<string, string>("Navy", "#000080"));
        colorTable.insert(std::pair<string, string>("DarkBlue", "#00008B"));
        colorTable.insert(std::pair<string, string>("MediumBlue", "#0000CD"));
        colorTable.insert(std::pair<string, string>("Blue", "#0000FF"));
        colorTable.insert(std::pair<string, string>("DarkGreen", "#006400"));
        colorTable.insert(std::pair<string, string>("Green", "#008000"));
        colorTable.insert(std::pair<string, string>("Teal", "#008080"));
        colorTable.insert(std::pair<string, string>("DarkCyan", "#008B8B"));
        colorTable.insert(std::pair<string, string>("DeepSkyBlue", "#00BFFF"));
        colorTable.insert(std::pair<string, string>("DarkTurquoise", "#00CED1"));
        colorTable.insert(std::pair<string, string>("MediumSpringGreen", "#00FA9A"));
        colorTable.insert(std::pair<string, string>("Lime", "#00FF00"));
        colorTable.insert(std::pair<string, string>("SpringGreen", "#00FF7F"));
        colorTable.insert(std::pair<string, string>("Aqua", "#00FFFF"));
        colorTable.insert(std::pair<string, string>("Cyan", "#00FFFF"));
        colorTable.insert(std::pair<string, string>("MidnightBlue", "#191970"));
        colorTable.insert(std::pair<string, string>("DodgerBlue", "#1E90FF"));
        colorTable.insert(std::pair<string, string>("LightSeaGreen", "#20B2AA"));
        colorTable.insert(std::pair<string, string>("ForestGreen", "#228B22"));
        colorTable.insert(std::pair<string, string>("SeaGreen", "#2E8B57"));
        colorTable.insert(std::pair<string, string>("DarkSlateGray", "#2F4F4F"));
        colorTable.insert(std::pair<string, string>("LimeGreen", "#32CD32"));
        colorTable.insert(std::pair<string, string>("MediumSeaGreen", "#3CB371"));
        colorTable.insert(std::pair<string, string>("Turquoise", "#40E0D0"));
        colorTable.insert(std::pair<string, string>("RoyalBlue", "#4169E1"));
        colorTable.insert(std::pair<string, string>("SteelBlue", "#4682B4"));
        colorTable.insert(std::pair<string, string>("DarkSlateBlue", "#483D8B"));
        colorTable.insert(std::pair<string, string>("MediumTurquoise", "#48D1CC"));
        colorTable.insert(std::pair<string, string>("Indigo", "#4B0082"));
        colorTable.insert(std::pair<string, string>("DarkOliveGreen", "#556B2F"));
        colorTable.insert(std::pair<string, string>("CadetBlue", "#5F9EA0"));
        colorTable.insert(std::pair<string, string>("CornflowerBlue", "#6495ED"));
        colorTable.insert(std::pair<string, string>("MediumAquaMarine", "#66CDAA"));
        colorTable.insert(std::pair<string, string>("DimGray", "#696969"));
        colorTable.insert(std::pair<string, string>("DimGrey", "#696969"));
        colorTable.insert(std::pair<string, string>("SlateBlue", "#6A5ACD"));
        colorTable.insert(std::pair<string, string>("OliveDrab", "#6B8E23"));
        colorTable.insert(std::pair<string, string>("SlateGray", "#708090"));
        colorTable.insert(std::pair<string, string>("LightSlateGray", "#778899"));
        colorTable.insert(std::pair<string, string>("MediumSlateBlue", "#7B68EE"));
        colorTable.insert(std::pair<string, string>("LawnGreen", "#7CFC00"));
        colorTable.insert(std::pair<string, string>("Chartreuse", "#7FFF00"));
        colorTable.insert(std::pair<string, string>("Aquamarine", "#7FFFD4"));
        colorTable.insert(std::pair<string, string>("Maroon", "#800000"));
        colorTable.insert(std::pair<string, string>("Purple", "#800080"));
        colorTable.insert(std::pair<string, string>("Olive", "#808000"));
        colorTable.insert(std::pair<string, string>("Gray", "#808080"));
        colorTable.insert(std::pair<string, string>("SkyBlue", "#87CEEB"));
        colorTable.insert(std::pair<string, string>("LightSkyBlue", "#87CEFA"));
        colorTable.insert(std::pair<string, string>("BlueViolet", "#8A2BE2"));
        colorTable.insert(std::pair<string, string>("DarkRed", "#8B0000"));
        colorTable.insert(std::pair<string, string>("DarkMagenta", "#8B008B"));
        colorTable.insert(std::pair<string, string>("SaddleBrown", "#8B4513"));
        colorTable.insert(std::pair<string, string>("DarkSeaGreen", "#8FBC8F"));
        colorTable.insert(std::pair<string, string>("LightGreen", "#90EE90"));
        colorTable.insert(std::pair<string, string>("MediumPurple", "#9370DB"));
        colorTable.insert(std::pair<string, string>("DarkViolet", "#9400D3"));
        colorTable.insert(std::pair<string, string>("PaleGreen", "#98FB98"));
        colorTable.insert(std::pair<string, string>("DarkOrchid", "#9932CC"));
        colorTable.insert(std::pair<string, string>("YellowGreen", "#9ACD32"));
        colorTable.insert(std::pair<string, string>("Sienna", "#A0522D"));
        colorTable.insert(std::pair<string, string>("Brown", "#A52A2A"));
        colorTable.insert(std::pair<string, string>("DarkGray", "#A9A9A9"));
        colorTable.insert(std::pair<string, string>("LightBlue", "#ADD8E6"));
        colorTable.insert(std::pair<string, string>("GreenYellow", "#ADFF2F"));
        colorTable.insert(std::pair<string, string>("PaleTurquoise", "#AFEEEE"));
        colorTable.insert(std::pair<string, string>("LightSteelBlue", "#B0C4DE"));
        colorTable.insert(std::pair<string, string>("PowderBlue", "#B0E0E6"));
        colorTable.insert(std::pair<string, string>("FireBrick", "#B22222"));
        colorTable.insert(std::pair<string, string>("DarkGoldenRod", "#B8860B"));
        colorTable.insert(std::pair<string, string>("MediumOrchid", "#BA55D3"));
        colorTable.insert(std::pair<string, string>("RosyBrown", "#BC8F8F"));
        colorTable.insert(std::pair<string, string>("DarkKhaki", "#BDB76B"));
        colorTable.insert(std::pair<string, string>("Silver", "#C0C0C0"));
        colorTable.insert(std::pair<string, string>("MediumVioletRed", "#C71585"));
        colorTable.insert(std::pair<string, string>("IndianRed", "#CD5C5C"));
        colorTable.insert(std::pair<string, string>("Peru", "#CD853F"));
        colorTable.insert(std::pair<string, string>("Chocolate", "#D2691E"));
        colorTable.insert(std::pair<string, string>("Tan", "#D2B48C"));
        colorTable.insert(std::pair<string, string>("LightGray", "#D3D3D3"));
        colorTable.insert(std::pair<string, string>("Thistle", "#D8BFD8"));
        colorTable.insert(std::pair<string, string>("Orchid", "#DA70D6"));
        colorTable.insert(std::pair<string, string>("GoldenRod", "#DAA520"));
        colorTable.insert(std::pair<string, string>("PaleVioletRed", "#DB7093"));
        colorTable.insert(std::pair<string, string>("Crimson", "#DC143C"));
        colorTable.insert(std::pair<string, string>("Gainsboro", "#DCDCDC"));
        colorTable.insert(std::pair<string, string>("Plum", "#DDA0DD"));
        colorTable.insert(std::pair<string, string>("BurlyWood", "#DEB887"));
        colorTable.insert(std::pair<string, string>("LightCyan", "#E0FFFF"));
        colorTable.insert(std::pair<string, string>("Lavender", "#E6E6FA"));
        colorTable.insert(std::pair<string, string>("DarkSalmon", "#E9967A"));
        colorTable.insert(std::pair<string, string>("Violet", "#EE82EE"));
        colorTable.insert(std::pair<string, string>("PaleGoldenRod", "#EEE8AA"));
        colorTable.insert(std::pair<string, string>("LightCoral", "#F08080"));
        colorTable.insert(std::pair<string, string>("Khaki", "#F0E68C"));
        colorTable.insert(std::pair<string, string>("AliceBlue", "#F0F8FF"));
        colorTable.insert(std::pair<string, string>("HoneyDew", "#F0FFF0"));
        colorTable.insert(std::pair<string, string>("Azure", "#F0FFFF"));
        colorTable.insert(std::pair<string, string>("SandyBrown", "#F4A460"));
        colorTable.insert(std::pair<string, string>("Wheat", "#F5DEB3"));
        colorTable.insert(std::pair<string, string>("Beige", "#F5F5DC"));
        colorTable.insert(std::pair<string, string>("WhiteSmoke", "#F5F5F5"));
        colorTable.insert(std::pair<string, string>("MintCream", "#F5FFFA"));
        colorTable.insert(std::pair<string, string>("GhostWhite", "#F8F8FF"));
        colorTable.insert(std::pair<string, string>("Salmon", "#FA8072"));
        colorTable.insert(std::pair<string, string>("AntiqueWhite", "#FAEBD7"));
        colorTable.insert(std::pair<string, string>("Linen", "#FAF0E6"));
        colorTable.insert(std::pair<string, string>("LightGoldenRodYellow", "#FAFAD2"));
        colorTable.insert(std::pair<string, string>("OldLace", "#FDF5E6"));
        colorTable.insert(std::pair<string, string>("Red", "#FF0000"));
        colorTable.insert(std::pair<string, string>("Fuchsia", "#FF00FF"));
        colorTable.insert(std::pair<string, string>("Magenta", "#FF00FF"));
        colorTable.insert(std::pair<string, string>("DeepPink", "#FF1493"));
        colorTable.insert(std::pair<string, string>("OrangeRed", "#FF4500"));
        colorTable.insert(std::pair<string, string>("Tomato", "#FF6347"));
        colorTable.insert(std::pair<string, string>("HotPink", "#FF69B4"));
        colorTable.insert(std::pair<string, string>("Coral", "#FF7F50"));
        colorTable.insert(std::pair<string, string>("Darkorange", "#FF8C00"));
        colorTable.insert(std::pair<string, string>("LightSalmon", "#FFA07A"));
        colorTable.insert(std::pair<string, string>("Orange", "#FFA500"));
        colorTable.insert(std::pair<string, string>("LightPink", "#FFB6C1"));
        colorTable.insert(std::pair<string, string>("Pink", "#FFC0CB"));
        colorTable.insert(std::pair<string, string>("Gold", "#FFD700"));
        colorTable.insert(std::pair<string, string>("PeachPuff", "#FFDAB9"));
        colorTable.insert(std::pair<string, string>("NavajoWhite", "#FFDEAD"));
        colorTable.insert(std::pair<string, string>("Moccasin", "#FFE4B5"));
        colorTable.insert(std::pair<string, string>("Bisque", "#FFE4C4"));
        colorTable.insert(std::pair<string, string>("MistyRose", "#FFE4E1"));
        colorTable.insert(std::pair<string, string>("BlanchedAlmond", "#FFEBCD"));
        colorTable.insert(std::pair<string, string>("PapayaWhip", "#FFEFD5"));
        colorTable.insert(std::pair<string, string>("LavenderBlush", "#FFF0F5"));
        colorTable.insert(std::pair<string, string>("SeaShell", "#FFF5EE"));
        colorTable.insert(std::pair<string, string>("Cornsilk", "#FFF8DC"));
        colorTable.insert(std::pair<string, string>("LemonChiffon", "#FFFACD"));
        colorTable.insert(std::pair<string, string>("FloralWhite", "#FFFAF0"));
        colorTable.insert(std::pair<string, string>("Snow", "#FFFAFA"));
        colorTable.insert(std::pair<string, string>("Yellow", "#FFFF00"));
        colorTable.insert(std::pair<string, string>("LightYellow", "#FFFFE0"));
        colorTable.insert(std::pair<string, string>("Ivory", "#FFFFF0"));
        colorTable.insert(std::pair<string, string>("White", "#FFFFFF"));

        bInit = true;
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