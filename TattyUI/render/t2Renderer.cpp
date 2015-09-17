#include <TattyUI/render/t2Renderer.h>
#include <TattyUI/common/t2Color.h>

#ifdef T2_RENDERER_NANOVG
// 矢量图形库
#include <TattyUI/render/nanovg/src/nanovg.h>
#include <TattyUI/render/nanovg/src/nanovg_gl.h>
#include <TattyUI/render/nanovg/src/nanovg_gl_utils.h>
#endif

namespace TattyUI
{
    class t2Renderer::t3Context
    {
    public:
        t3Context()
        {
            vg = NULL;
            // nanovg
#if (T2_PLATFORM_IOS || T2_PLATFORM_ANDROID)
            vg = nvgCreateGLES2(NVG_ANTIALIAS | NVG_STENCIL_STROKES | NVG_DEBUG);
#else
            vg = nvgCreateGL3(NVG_STENCIL_STROKES | NVG_ANTIALIAS | NVG_DEBUG);
#endif
        }
        // nanovg
        NVGcontext* vg;

        NVGcolor vgColor;

        NVGcolor vgStrokeColor;

        NVGcolor vgTextColor;

        float vgStrokeWidth;

        string fontName;
    };

	t2Renderer* t2Renderer::getInstance()
	{
		static t2Renderer renderer;
		return &renderer;
	}

	t2Renderer::t2Renderer():fillMode(T2_FILLED)
	{
        context = new t2Renderer::t3Context();

		//pixelPoint.resize(1);
		//linePoints.resize(2);
		//rectPoints.resize(4);
		//triPoints.resize(3);
        //
		//circleResolution = T2_CIRCLE_RESOLUTION_DEFAULT;
		//circlePoints.resize(T2_CIRCLE_RESOLUTION_DEFAULT+1);
        //
		//arcPoints.resize(T2_ARC_RESOLUTION_DEFAULT + 1);
		//arcResolution = T2_ARC_RESOLUTION_DEFAULT;
        //
		//roundRectPoints.resize(T2_ROUNDRECT_RESOLUTION_DEFAULT);
	}

    void t2Renderer::begin()
    {
        nvgBeginFrame(context->vg, t2GetWindowWidth(), t2GetWindowHeight(), 1);

        nvgSave(context->vg);
        //nvgGlobalAlpha(context->vg, 0.7);
    }

    void t2Renderer::end()
    {
        nvgRestore(context->vg);

        nvgEndFrame(context->vg);
    }

    void t2Renderer::clear(int r, int g, int b, int a)
	{
        glClearColor(r / 255.0f, g / 255.0f, b / 255.0f, a / 255.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

    void t2Renderer::setColor(int r, int g, int b, int a)
	{
        // --!颜色溢出将会导致抗锯齿出现问题
		//glColor4f(r, g, b, a);
        context->vgColor.r = r / 255.0f;
        context->vgColor.g = g / 255.0f;
        context->vgColor.b = b / 255.0f;
        context->vgColor.a = a / 255.0f;
    }

    void t2Renderer::setColor(const t2Color &color)
    {
        setColor(color.r, color.g, color.b, color.a);
    }

    void t2Renderer::setStrokeColor(int r, int g, int b, int a /*= 255.0f*/)
    {
        context->vgStrokeColor.r = r / 255.0f;
        context->vgStrokeColor.g = g / 255.0f;
        context->vgStrokeColor.b = b / 255.0f;
        context->vgStrokeColor.a = a / 255.0f;
    }

    void t2Renderer::setStrokeWidth(float strokeWidth)
    {
        context->vgStrokeWidth = strokeWidth;
    }

    void t2Renderer::setTextColor(int r, int g, int b, int a /*= 255.0f*/)
    {
        context->vgTextColor.r = r / 255.0f;
        context->vgTextColor.g = g / 255.0f;
        context->vgTextColor.b = b / 255.0f;
        context->vgTextColor.a = a / 255.0f;
    }

    void t2Renderer::setTextColor(const t2Color &color)
    {
        setTextColor(color.r, color.g, color.b, color.a);
    }

    void t2Renderer::setFont(const char* name)
    {
        // --!内存泄露
        //if(!context->fontName)
          //  delete context->fontName;

        context->fontName = string(name);
    }

    void t2Renderer::drawEllipse(float x, float y, float rx, float ry, bool bFill)
    {
        nvgBeginPath(context->vg);

        if(bFill)
            nvgFillColor(context->vg, context->vgColor);
        else
        {
            nvgStrokeColor(context->vg, context->vgStrokeColor);
            nvgStrokeWidth(context->vg, context->vgStrokeWidth);
        }

        nvgEllipse(context->vg, x, y, rx, ry);

        if(bFill)
            nvgFill(context->vg);
        else
            nvgStroke(context->vg);
    }

    void t2Renderer::drawArc(float x, float y, float radius, float angle0, float angle1, int direction, bool bFill)
	{
		//setArcResolution(resolution);
		//float step = std::abs(angleEnd - angleBegin) / arcResolution;
		//int i = 0;
		//for(float angle = angleBegin; angle < angleEnd + step; angle += step)
		//{
		//	float anglerad = angle * T2_DEGREE_TO_RADIAN;
		//	// 浮点数误差带来的无奈之举
		//	if(i <= arcResolution)
		//		arcPoints[i].set(sinf(anglerad)*radius + x, cosf(anglerad)*radius + y);
		//	else
		//		break;
		//	i++;
		//}
		//// 使用顶点数组 可搭配颜色数组 纹理做标数组等等
		//glEnableClientState(GL_VERTEX_ARRAY);
		//// 每个数组元素有多少个分量 / 分量类型 / 一个数组元素的大小 / 该数组的起始指针
		//glVertexPointer(2, GL_INT, sizeof(t2Point2i), &arcPoints[0].x);
		//if(fillMode == T2_FILLED)
		//{
		//	arcResolution++;
		//	if(arcPoints.size() < arcResolution + 1)
		//	{
		//		arcPoints.resize(arcResolution + 1);
		//	}
		//	arcPoints[arcResolution].set(x, y);
		//	// 渲染出该数组的渲染方式 / 起始位置 / 多少个元素
		//	glDrawArrays(GL_TRIANGLE_FAN, 0, arcResolution + 1);
		//}
		//else
		//	// 渲染出该数组的渲染方式 / 起始位置 / 多少个元素
		//	glDrawArrays(GL_LINE_STRIP, 0, arcResolution + 1);
        nvgBeginPath(context->vg);

        if(bFill)
            nvgFillColor(context->vg, context->vgColor);
        else
        {
            nvgStrokeColor(context->vg, context->vgStrokeColor);
            nvgStrokeWidth(context->vg, context->vgStrokeWidth);
        }

        nvgArc(context->vg, x, y, radius, angle0, angle1, direction);

        if(bFill)
            nvgFill(context->vg);
        else
            nvgStroke(context->vg);
    }

    void t2Renderer::drawCircle(int x, int y, int radius, bool bFill)
    {
        //setCircleResolution(resolution);
        //float step = 360.0f / circleResolution;
        //int i = 0;
        //for(float angle = 0.0f; angle < 360.0f; angle += step)
        //{
        //	float anglerad = PI * angle / 180.0f;
        //	// 浮点数误差带来的无奈之举
        //	if(i <= circleResolution)
        //		circlePoints[i].set(sinf(anglerad)*radius + x, cosf(anglerad)*radius + y);
        //	else
        //		break;
        //	i++;
        //}
        //// 使用顶点数组 可搭配颜色数组 纹理做标数组等等
        //glEnableClientState(GL_VERTEX_ARRAY);
        //// 每个数组元素有多少个分量 / 分量类型 / 一个数组元素的大小 / 该数组的起始指针
        //glVertexPointer(2, GL_INT, sizeof(t2Point2i), &circlePoints[0].x);
        //// 渲染出该数组的渲染方式 / 起始位置 / 多少个元素
        //glDrawArrays((fillMode == T2_FILLED) ? GL_TRIANGLE_FAN : GL_LINE_LOOP, 0, circleResolution);

        nvgBeginPath(context->vg);

        if(bFill)
            nvgFillColor(context->vg, context->vgColor);
        else
        {
            nvgStrokeColor(context->vg, context->vgStrokeColor);
            nvgStrokeWidth(context->vg, context->vgStrokeWidth);
        }

        nvgCircle(context->vg, x, y, radius);

        if(bFill)
            nvgFill(context->vg);
        else
            nvgStroke(context->vg);
	}

    void t2Renderer::drawLine(int startX, int startY, int endX, int endY, bool bFill)
	{
		////vector元素在初始化以后可以使用set来初始化内部值
		//linePoints[0].set(startX, startY);
		//linePoints[1].set(endX, endY);
        //
		//// 使用顶点数组 可搭配颜色数组 纹理做标数组等等
		//glEnableClientState(GL_VERTEX_ARRAY);
        //
		//// 每个数组元素有多少个分量 / 分量类型 / 一个数组元素的大小 / 该数组的起始指针
		//glVertexPointer(2, GL_INT, sizeof(t2Point2i), &linePoints[0].x);
		//// 渲染出该数组的渲染方式 / 起始位置 / 多少个元素
		//glDrawArrays(GL_LINE_STRIP, 0, 2);

        nvgBeginPath(context->vg);
        nvgMoveTo(context->vg, startX, startY);
        nvgLineTo(context->vg, endX, endY);
        nvgStrokeColor(context->vg, context->vgStrokeColor);
        nvgStrokeWidth(context->vg, context->vgStrokeWidth);
        nvgStroke(context->vg);
	}

    void t2Renderer::drawRect(int x, int y, int width, int height, bool bFill)
	{
		//rectPoints[0].set(x, y);
		//rectPoints[1].set(x + width, y);
		//rectPoints[2].set(x + width, y + height);
		//rectPoints[3].set(x, y + height);
        //
		//glEnableClientState(GL_VERTEX_ARRAY);
		//glVertexPointer(2, GL_INT, sizeof(t2Point2i), &rectPoints[0].x);
		//// 填充/线列
		//glDrawArrays((fillMode == T2_FILLED) ? GL_TRIANGLE_FAN : GL_LINE_LOOP, 0, 4);

        nvgBeginPath(context->vg);

        if(bFill)
            nvgFillColor(context->vg, context->vgColor);
        else
        {
            nvgStrokeColor(context->vg, context->vgStrokeColor);
            nvgStrokeWidth(context->vg, context->vgStrokeWidth);
        }

        nvgRect(context->vg, x, y, width, height);

        if(bFill)
            nvgFill(context->vg);
        else
            nvgStroke(context->vg);

		// 还原抗锯齿
		// --!可以使用AOP设计模式完成函数调用时和结束时调用的工作
		//if(!antiAliasing)
		//	enableAntiAliasing();
	}

    void t2Renderer::drawRoundRect(int x, int y, int width, int height, float borderRadius, bool bFill)
	{
		//float x1 = x, y1 = y;
		//float x2 = x + width, y2 = y + height;
		//
		//// --!来自Cinder/gl.cpp
		//// automatically determine the number of segments from the circumference
		//if(resolution <= 0)
		//	resolution = (int)floor(borderRadius * PI * 2 / 4);
		//if(resolution < 2) 
		//	resolution = 2;
        //
		//if((resolution + 2) * 4 > roundRectPoints.size())
		//	roundRectPoints.resize((resolution + 2) * 4);
        //
		////GLfloat *roundRectPoints = new float[(resolution + 2) * 2 * 4];
		//size_t tri = 0;
		//const float angleDelta = 1 / (float)resolution * PI / 2;
		//const float cornerCenterVerts[8] = { x2 - borderRadius, y2 - borderRadius, x1 + borderRadius, y2 - borderRadius,
		//	x1 + borderRadius, y1 + borderRadius, x2 - borderRadius, y1 + borderRadius };
		//for(size_t corner = 0; corner < 4; ++corner)
		//{
		//	float angle = corner * PI / 2.0f;
		//	t2Vector2f cornerCenter(cornerCenterVerts[corner * 2 + 0], cornerCenterVerts[corner * 2 + 1]);
		//	for(int s = 0; s <= resolution; s++)
		//	{
		//		t2Vector2f pt(cornerCenter.x + cosf(angle) * borderRadius, cornerCenter.y + sinf(angle) * borderRadius);
		//		roundRectPoints[tri].set(pt.x, pt.y);
		//		++tri;
		//		angle += angleDelta;
		//	}
		//}
        //
		//if(fillMode != T2_FILLED)
		//{
		//	glEnableClientState(GL_VERTEX_ARRAY);
		//	glVertexPointer(2, GL_FLOAT, 0, &roundRectPoints[0].x);
		//	glDrawArrays(GL_LINE_LOOP, 0, tri);
		//	glDisableClientState(GL_VERTEX_ARRAY);
		//}
		//else
		//{
		//	// close it off
		//	roundRectPoints[tri].set(x2, y2 - borderRadius);
		//	glEnableClientState(GL_VERTEX_ARRAY);
		//	glVertexPointer(2, GL_FLOAT, 0, &roundRectPoints[0].x);
		//	glDrawArrays(GL_TRIANGLE_FAN, 0, (resolution + 1) * 4 + 2);
		//	glDisableClientState(GL_VERTEX_ARRAY);
		//}
        //
		////delete[] verts;
        nvgBeginPath(context->vg);

        if(bFill)
            nvgFillColor(context->vg, context->vgColor);
        else
        {
            nvgStrokeColor(context->vg, context->vgStrokeColor);
            nvgStrokeWidth(context->vg, context->vgStrokeWidth);
        }

        nvgRoundedRect(context->vg, x, y, width, height, borderRadius);

        if(bFill)
            nvgFill(context->vg);
        else
            nvgStroke(context->vg);
	}

    void t2Renderer::drawText(int x, int y, int size, string caption, int blur, int align)
    {
        nvgFontBlur(context->vg, blur);
        nvgFontSize(context->vg, size);
        nvgFontFace(context->vg, context->fontName.c_str());
        nvgTextAlign(context->vg, align);
        nvgFillColor(context->vg, context->vgTextColor);
        nvgText(context->vg, x, y, caption.c_str(), nullptr);
    }

//	void t2Renderer::setCircleResolution(float resolution)
//	{
//		if(resolution > 0)
//			circleResolution = resolution;
//
//		if(circleResolution + 1 > circlePoints.size())
//		{
//			circlePoints.resize(circleResolution + 1);
//#ifdef _DEBUG
//			//t2Log("被重新分配:%f, 容量:%d, 大小:%d\n", circleResolution, circlePoints.capacity(), circlePoints.size());
//#endif
//		}
//	}
//
//	void t2Renderer::setArcResolution(float resolution)
//	{
//		if(resolution > 0)
//			arcResolution = resolution;
//
//		if(arcResolution + 1 > arcPoints.size())
//		{
//			arcPoints.resize(arcResolution + 1);
//
//#ifdef _DEBUG
//			//t2Log("被重新分配:%f, 容量:%d, 大小:%d\n", arcResolution, arcPoints.capacity(), arcPoints.size());
//#endif
//		}
//
//	}

	//void t2Renderer::setFillMode(t2FillMode fillMode)
	//{
 //       // --!停用此API
	//	//this->fillMode = fillMode;
	//}

	void t2Renderer::setBlendMode(t2BlendMode blendMode)
	{
		switch(blendMode)
		{
		case T2_BLENDMODE_DISABLED:
			glDisable(GL_BLEND);
			break;

		case T2_BLENDMODE_ALPHA:
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			break;

		case T2_BLENDMODE_ADD:
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;

		case T2_BLENDMODE_MULTIPLY:
			glEnable(GL_BLEND);
			glBlendFunc(GL_DST_COLOR, GL_ONE_MINUS_SRC_ALPHA);
			break;

		case T2_BLENDMODE_SCREEN:
			glEnable(GL_BLEND);
			glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ONE);
			break;

			//减法
		case T2_BLENDMODE_SUBTRACT:
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE);
			break;

		default:
			break;
		}
	}

	void t2Renderer::enableAntiAliasing()
	{
		glEnable(GL_MULTISAMPLE);
	}

	void t2Renderer::disableAntiAliasing()
	{
		glDisable(GL_MULTISAMPLE);
	}

    void t2Renderer::loadFont(const char* name, const char* filename)
    {
        if(-1 == nvgCreateFont(context->vg, name, filename))
        {
            t2PrintError("创建字体失败\n");
        }
    }

    NVGcontext* t2Renderer::getContext()
    {
        return context->vg;
    }

}