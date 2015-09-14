#ifndef T2_VECTOR4_H
#define T2_VECTOR4_H

#include <TattyUI/common/t2Settings.h>

namespace TattyUI
{
    template <class Type>
    class t2Vector4
    {
    public:
        Type x, y, z, w;

        t2Vector4() :x(0), y(0), z(0), w(0) {}
        t2Vector4(const t2Vector4& v):
            x(v.x), y(v.y), z(v.z), w(v.w){}

        void set(const Type x, const Type y, const Type z, const Type w)
        {
            this->x = x;
            this->y = y;
            this->z = z;
            this->w = w;
        }
    };

    // 特化
    typedef t2Vector4<float> t2Vector4f;
    typedef t2Vector4<int> t2Vector4i;

    // t2Point
    typedef t2Vector4f t2Point4f;
    typedef t2Vector4i t2Point4i;

    // 零向量
    static t2Vector4f t2Vector4fZero;
    static t2Vector4i t2Vector4iZero;
}

#endif