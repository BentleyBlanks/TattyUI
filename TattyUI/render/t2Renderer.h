#ifndef T2_RENDERER_H
#define T2_RENDERER_H

#include <TattyUI/common/t2Color.h>
#include <TattyUI/common/t2Vector2.h>

#ifdef T2_RENDERER_NANOVG
struct NVGcontext;
#endif

namespace TattyUI
{
	//enum t2CircleResolution
	//{
	//	T2_CIRCLE_RESOLUTION_DEFAULT = 20,
	//	T2_CIRCLE_RESOLUTION_ROUGH = 10,
	//	T2_CIRCLE_RESOLUTION_EXQUISITE = 50,

	//	T2_ARC_RESOLUTION_DEFAULT = 10,
	//	T2_ARC_RESOLUTION_ROUGH = 5,
	//	T2_ARC_RESOLUTION_EXQUISITE = 20,

	//	T2_ROUNDRECT_RESOLUTION_DEFAULT = 32,
	//	T2_ROUNDRECT_RESOLUTION_ROUGH = 16,
	//	T2_ROUNDRECT_RESOLUTION_EXQUISITE = 64,
	//};

    enum t2ArcDirection
    {
        T2_CCW = 1,			// Winding for solid shapes
        T2_CW = 2,				// Winding for holes
    };

    enum t2TextAlign
    {
        // Horizontal align
        T2_ALIGN_LEFT = 1 << 0,	// Default, align text horizontally to left.
        T2_ALIGN_CENTER = 1 << 1,	// Align text horizontally to center.
        T2_ALIGN_RIGHT = 1 << 2,	// Align text horizontally to right.
        // Vertical align
        T2_ALIGN_TOP = 1 << 3,	// Align text vertically to top.
        T2_ALIGN_MIDDLE = 1 << 4,	// Align text vertically to middle.
        T2_ALIGN_BOTTOM = 1 << 5,	// Align text vertically to bottom. 
        T2_ALIGN_BASELINE = 1 << 6, // Default, align text vertically to baseline. 
    };


	class t2Renderer
	{
	public:
		static t2Renderer* getInstance();

        // 所有渲染内容都不应在begin-end块外出现
        void begin();

        void end();

		// [0, 255]
        void clear(int r, int g, int b, int a = 255.0f);

        // set
        void setColor(const t2Color &color);

        void setColor(int r, int g, int b, int a = 255.0f);

        void setTextColor(const t2Color &color);

        void setTextColor(int r, int g, int b, int a = 255.0f);

        void setStrokeColor(int r, int g, int b, int a = 255.0f);

        void setStrokeWidth(float strokeWidth);

        //void setFillMode(t2FillMode fillMode);

        void setBlendMode(t2BlendMode blendMode);

        // --!目前尽量不要在循环中反复调用
        void setFont(const char* name);

        // draw
        void drawEllipse(float x, float y, float rx, float ry, bool bFill = true);

        void drawCircle(int x, int y, int radius, bool bFill = true);

		// --1目前只支持圆的一部分
        void drawArc(float x, float y, float radius, float angle0, float angle1, int direction = T2_CCW, bool bFill = true);

		// --!渲染时开启倘若开启抗锯齿 则在渲染1px宽矩形/线性时会得到2px的奇怪的抗锯齿之后的样式 
        void drawLine(int startX, int startY, int endX, int endY, bool bFill = true);

        void drawRect(int x, int y, int width, int height, bool bFill = true);

        void drawRoundRect(int x, int y, int width, int height, float borderRadius, bool bFill = true);

        void drawText(int x, int y, int size, string caption, int blur = 0, int align = T2_ALIGN_LEFT | T2_ALIGN_MIDDLE);

        // 字体
        // --!未来可配置成自动读取创建
        void loadFont(const char* name, const char* filePath);
        
		// 抗锯齿
		void enableAntiAliasing();

		void disableAntiAliasing();

#ifdef T2_RENDERER_NANOVG
        NVGcontext* getContext();
#endif

	private:
		// 非常严格的单例模式
		t2Renderer();
		t2Renderer(const t2Renderer&){}
		~t2Renderer(){}
		t2Renderer& operator=(const t2Renderer& event) const{}

        t2FillMode fillMode;

        // 实际底层渲染框架句柄
        class t3Context;
        t3Context* context;

		// 圆使用多边形逼近 resolution表示一个完整的圆分的段数 因此顶点数比段数要多1
		//void setCircleResolution(float resolution);
        //
		//void setArcResolution(float resolution);
        //
		// 顶点数组
		//vector<t2Point2i> pixelPoint;
		//vector<t2Point2i> linePoints;
        //
		//vector<t2Point2f> roundRectPoints;
		//vector<t2Point2i> rectPoints;
		//vector<t2Point2i> triPoints;
		//vector<t2Point2i> arcPoints;
		//vector<t2Point2i> circlePoints;
        //
		//float currentCircleResolution;
		//float circleResolution;
        //
		//float currentArcResolution;
		//float arcResolution;
	};
}

#endif