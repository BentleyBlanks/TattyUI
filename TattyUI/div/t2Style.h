#ifndef T2_STYLE_H
#define T2_STYLE_H

#include <TattyUI/render/t2Image.h>
#include <TattyUI/common/t2Vector2.h>
#include <TattyUI/common/t2Dimension.h>
#include <TattyUI/common/t2Color.h>
#include <TattyUI/common/t2Settings.h>

#include <TattyUI/render/t2Gradient.h>

namespace TattyUI
{
    enum t2BackgroundPosition
    {
        T2_TOP_LEFT = 0,
        T2_TOP_CENTER,
        T2_TOP_RIGHT,
        T2_CENTER_LEFT,
        T2_CENTER_CENTER,
        T2_CENTER_RIGHT,
        T2_BOTTOM_LEFT,
        T2_BOTTOM_CENTER,
        T2_BOTTOM_RIGHT,
    };

    enum t2DivTextAlign
    {
        T2_TEXT_LEFT = 1 << 0,
        T2_TEXT_CENTER = 1 << 1,
        T2_TEXT_RIGHT = 1 << 2,

        T2_TEXT_TOP = 1 << 3,
        T2_TEXT_MIDDLE = 1 << 4,
        T2_TEXT_BOTTOM = 1 << 5,
    };

    enum t2BoxAlign
    {
        T2_START,
        T2_END,
        T2_CENTER
    };

    enum t2BoxOrient
    {
        T2_HORIZONTAL,
        T2_VERTICAL
    };

    enum t2BlockDisplay
    {
        T2_DISPLAY_NONE = 0,
        T2_DISPLAY_BLOCK
    };

    class t2Style
    {
    public:
        t2Style();

        t2Style(t2Style& s);

        // --!参考与 http://www.w3school.com.cn/cssref/
        // hidden property
        // --!弃用绝对坐标
        int x, y;

        // display
        int display;

        // background
        // 设置元素的背景颜色
        t2Color backgroundColor;
        // 设置元素的背景图像
        t2Image backgroundImage;
        // --!目前为全局填充
        // 设置背景图像的开始位置
        int backgroundPosition;
        // 规定背景图片的尺寸
        t2Vector2f backgroundSize;

        // border
        // 设置所有四个 border-*-radius 属性
        int borderRadius;
        // 水平/垂直阴影的位置
        int hBoxShadow, vBoxShadow;
        // 模糊距离
        int boxShadowBlur;
        // 阴影的颜色
        t2Color boxShadowInColor, boxShadowOutColor;

        // color
        // 规定书签的透明度[0.0f, 1.0f]
        float opacity;

        // dimension
        int width, height;
        // --!maxHeight不起作用
        int maxHeight, maxWidth;
        int minHeight, minWidth;

        // flexible box
        // 规定如何对齐框的子元素
        int boxAlign;
        // 规定当超出父元素框的空间时，是否换行显示
        bool boxLines;
        // 规定框的子元素是否应水平或垂直排列
        int boxOrient;

        // font
        // 规定文本的字体系列
        string fontFamily;
        // 规定文本的字体尺寸
        int fontSize;
        // 规定字体的粗细
        int fontWeight;

        // margin
        int marginBottom;
        int marginLeft;
        int marginRight;
        int marginTop;

        // padding
        int paddingBottom;
        int paddingLeft;
        int paddingRight;
        int paddingTop;

        // position
        // --!暂不支持
        int zIndex;

        // text
        // 设置文本的颜色
        t2Color textColor;
        // 设置字符间距
        int letterSpacing;
        // 设置行高
        int lineHeight;
        // 规定文本的水平对齐方式
        int textAlign;
        // 设置单词间距
        int wordSpacing;
        // 文本内容
        string text;

        // text-shadow
        int hTextShadow, vTextShadow;
        int textShadowBlur;
        t2Color textShadowColor;

        // 辅助属性
        // 其他辅助属性
        t2BoxGradient boxGradient;

        string fontName;

        // 实际显示内容的dimension(x, y, width, height)
        t2Dimensionf contentSize;

        // 是否显示阴影
        bool displayShadow;
    };
}

#endif