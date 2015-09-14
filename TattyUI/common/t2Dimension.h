#ifndef T2_DIMENSION_H
#define T2_DIMENSION_H

#include <TattyUI/common/t2Settings.h>

// 本质定义与Vector4一致
namespace TattyUI
{
    template <class Type>
    class t2Dimension
    {
    public:
        Type x, y, width, height;

        t2Dimension():x(0), y(0), width(0), height(0) {}
        t2Dimension(const t2Dimension& v) :
            x(v.x), y(v.y), width(v.width), height(v.height) {}

        void set(const Type x, const Type y, const Type width, const Type height)
        {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
        }
    };

    // 特化
    typedef t2Dimension<float> t2Dimensionf;
    typedef t2Dimension<int> t2Dimensioni;

    // 零尺寸
    static t2Dimensionf t2DimensionfZero;
    static t2Dimensioni t2DimensioniZero;
}

#endif