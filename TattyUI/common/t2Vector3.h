#ifndef T2_VECTOR3_H
#define T2_VECTOR3_H

#include <TattyUI/common/t2Settings.h>

namespace TattyUI
{
    template <class Type>
    class t2Vector3
    {
    public:
        Type x, y, z;

        void set(const Type x, const Type y, const Type z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
    };

    // 特化
    typedef t2Vector3<float> t2Vector3f;
    typedef t2Vector3<int> t2Vector3i;

    // t2Point
    typedef t2Vector3f t2Point3f;
    typedef t2Vector3i t2Point3i;

    // 零向量
    static t2Vector3f t2Vector3fZero;
    static t2Vector3i t2Vector3iZero;
}

#endif