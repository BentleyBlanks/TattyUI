#include <TattyUI/div/t2Style.h>
#include <TattyUI/render/t2Renderer.h>

namespace TattyUI
{
    t2Style::t2Style() :
        // position
        x(0), y(0), zIndex(0),
        // background
        backgroundPosition(T2_TOP_LEFT), 
        // border
        borderRadius(0), hBoxShadow(0), vBoxShadow(0), boxShadowBlur(20),
        // color
        opacity(1.0f),
        // dimension
        width(0), height(0), maxWidth(0), maxHeight(0), minWidth(0), minHeight(0),
        // flexible box
        boxAlign(T2_START), boxLines(false), boxOrient(T2_HORIZONTAL),
        // font
        fontSize(10), fontWeight(0),
        // margin
        marginBottom(0), marginLeft(0), marginRight(0), marginTop(0),
        // padding
        paddingBottom(0), paddingLeft(0), paddingRight(0), paddingTop(0),
        // text
        letterSpacing(0), lineHeight(0), textAlign(T2_ALIGN_CENTER), wordSpacing(0),
        // text-shadow
        hTextShadow(0), vTextShadow(0), textShadowBlur(0)
    {
        boxShadowColor.set(0, 0, 0, 100);

        textColor.set(0, 0, 0, 255);
    }

    t2Style::t2Style(t2Style& s):
        // position
        x(s.x), y(s.y), zIndex(s.zIndex),
        // background
        backgroundPosition(s.backgroundPosition), backgroundColor(s.backgroundColor), backgroundImage(s.backgroundImage), backgroundSize(s.backgroundSize),
        // border
        borderRadius(s.borderRadius), hBoxShadow(s.hBoxShadow), vBoxShadow(s.vBoxShadow), boxShadowBlur(s.boxShadowBlur), boxShadowColor(s.boxShadowColor),
        // color
        opacity(s.opacity),
        // dimension
        width(s.width), height(s.height), maxWidth(s.maxWidth), maxHeight(s.maxHeight), minWidth(s.minWidth), minHeight(s.minHeight),
        // flexible box
        boxAlign(s.boxAlign), boxLines(s.boxLines), boxOrient(s.boxOrient),
        // font
        fontSize(s.fontSize), fontWeight(s.fontWeight), fontFamily(s.fontFamily),
        // margin
        marginBottom(s.marginBottom), marginLeft(s.marginLeft), marginRight(s.marginRight), marginTop(s.marginTop),
        // padding
        paddingBottom(s.paddingBottom), paddingLeft(s.paddingLeft), paddingRight(s.paddingRight), paddingTop(s.paddingTop),
        // text
        letterSpacing(s.letterSpacing), lineHeight(s.lineHeight), textAlign(s.textAlign), wordSpacing(s.wordSpacing), textColor(s.textColor), text(s.text),
        // text-shadow
        hTextShadow(s.hTextShadow), vTextShadow(s.vTextShadow), textShadowBlur(s.textShadowBlur), textShadowColor(s.textShadowColor),
        // 辅助属性
        fontName(s.fontName), boxGradient(s.boxGradient)
    {

    }

    // --!码者自己写给自己看的 小孩子不要看
    // 类CSS命名法方便写代码时使用
    string cssProperty[] = {
        // hidden property
        "x",
        "y",

        // background
        "background",
        "background-color",
        "background-size",
        "background-image",
        "background-position",

        // border
        //"border",
        //"border-bottom",
        //"border-bottom-color",
        //"border-bottom-style",
        //"border-bottom-width",
        //"border-color",
        //"border-left",
        //"border-left-color",
        //"border-left-style",
        //"border-left-width",
        //
        //"border-right",
        //"border-right-color",
        //"border-right-width",
        //
        //"border-top",
        //"border-top-color",
        //"border-top-width",
        //"border-width",
        //
        //"border-bottom-left-radius",
        //"border-bottom-right-radius",
        //"border-image",
        //"border-image-source",
        //"border-image-width",
        //
        //"border-radius",
        //"border-top-left-radius",
        //"border-top-right-radius",

        // border-box
        "border-Radius"
        "box-shadow",

        // color
        "opacity",

        // dimension
        "height",
        "max-height",
        "max-width",
        "min-height",
        "min-width",
        "width",

        // flexible box
        "box-align",
        "box-lines",
        "box-orient",

        // font
        "font",
        "font-family",
        "font-size",
        "font-weight",

        // margin
        "margin",
        "margin-bottom",
        "margin-left",
        "margin-right",
        "margin-top",

        // padding
        "padding",
        "padding-bottom",
        "padding-left",
        "padding-right",
        "padding-top",

        // position
        "z-index",

        // text
        "color",
        "letter-spacing",
        "line-height",
        "text-align",
        "word-spacing",
        "text-shadow"
    };
}