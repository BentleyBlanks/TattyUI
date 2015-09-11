#ifndef T2_VECTOR2_H
#define T2_VECTOR2_H

#include <TattyUI/common/t2Settings.h>

namespace TattyUI
{
	template <class Type>
	class t2Vector2
	{
	public:
		Type x, y;

		t2Vector2() :x(0), y(0)
		{
		}
		t2Vector2(Type x, Type y) :x(x), y(y)
		{
		}
		// 复制构造
		t2Vector2(const t2Vector2<Type>& vector) :x(vector.x), y(vector.y)
		{
		}

		void clone(const t2Vector2<Type>& vector)
		{
			x = vector.x; y = vector.y;
		}

		void set(t2Vector2& vector)
		{
			set(vector.x, vector.y);
		}

		void set(const Type x, const Type y)
		{
			this->x = x; this->y = y;
		}

		// 重载 =
		t2Vector2<Type>& operator=(const t2Vector2<Type>& vector);
		// 重载 == !=
		bool operator==(const t2Vector2<Type>& vector) const;
		bool operator!=(const t2Vector2<Type>& vector) const;

		// 重载一元 - +
		t2Vector2<Type> operator-();
		t2Vector2<Type> operator+();

		// 重载 二元 + -
		t2Vector2<Type> operator+(const t2Vector2<Type>& vector) const;
		t2Vector2<Type> operator-(const t2Vector2<Type>& vector) const;

		// 标量 乘除法 * / scale
		t2Vector2<Type> operator*(const Type scale) const;
		// 会对
		t2Vector2<Type> operator/(const Type scale) const;

		// 重载 += -= *= /=
		t2Vector2<Type>& operator+=(const t2Vector2<Type>& vector);
		t2Vector2<Type>& operator-=(const t2Vector2<Type>& vector);
		t2Vector2<Type>& operator*=(const Type scale);
		t2Vector2<Type>& operator/=(const Type scale);

		// 向量 * vector(无需inline一个右乘 因为类型相同左右不分)
		Type operator*(const t2Vector2<Type>& vector) const;

		// 置为零向量
		inline void zero()
		{
			// --!之所以此处不(Type)强制类型转换 是因为意义不大 但是却消耗比较大的速度
			x = 0;
			y = 0;
		}

		// 将此2D向量标准化
		inline bool normalize()
		{
			Type length = getLength();
			if (length == 0)
				return false;

			Type inverseLength = 1.0f / length;
			x *= inverseLength;
			y *= inverseLength;

			return true;
		}

		// 求模长
		inline Type getLength() const
		{
			return sqrtf(x*x + y*y);
		}

		inline Type getLengthSquare() const
		{
			return (x*x + y*y);
		}

		// 叉积
		inline Type cross(const t2Vector2<Type>& vector) const
		{
			// |i j k|
			// |a b c|
			// |x y z|
			// |axb|的长度代表了以a和b为邻边的平行四边形的面积
			return x*vector.y - y*vector.x;
		}

		// 与一标量叉积的结果为 先求得当前向量的垂直向量(-y, x)再缩放scalar倍
		// 叉积
		template <class Type>
		inline t2Vector2<Type> cross(const float& scalar) const
		{
			return t2Vector2<Type>(-this->y*scalar, scalar*this->x);
		}

		inline Type dot(const t2Vector2<Type>& vector) const
		{
			return this->x*vector.x + this->y*vector.y;
		}

		// 两点间距离
		inline Type getDistance(const t2Vector2<Type>& end) const
		{
			return sqrt((end.x - x)*(end.x - x) + (end.y - y)*(end.y - y));
		}

		inline Type getDistanceSquare(const t2Vector2<Type>& end) const
		{
			return (end.x - x)*(end.x - x) + (end.y - y)*(end.y - y);
		}

		// 测试使用的Console Log输出
		inline void print(std::string name)
		{
#ifdef _DEBUG
			// 为空
			if (name.empty())
				name = "";
			std::cout << "t2Vector2 ";
			std::cout << name << "(x: " << x << ", y: " << y << ")" << std::endl;
#endif
		}

		inline void print()
		{
#ifdef _DEBUG
			std::cout << "t2Vector2 ";
			std::cout << "(x: " << x << ", y: " << y << ")" << std::endl;
#endif
		}

	};

	// 成员函数
	// 重载 =
	template <class Type>
	t2Vector2<Type>& t2Vector2<Type>::operator=(const t2Vector2<Type>& vector)
	{
		this->x = vector.x;
		this->y = vector.y;

		return *this;
	}

	// 重载 == !=
	template <class Type>
	bool t2Vector2<Type>::operator==(const t2Vector2<Type>& vector) const
	{
		return equals(this->x, vector.x) && equals(this->y, vector.y);
	}

	template <class Type>
	bool t2Vector2<Type>::operator!=(const t2Vector2<Type>& vector) const
	{
		return !(equals(this->x, vector.x) && equals(this->y, vector.y));
	}

	// 重载一元 - +
	template <class Type>
	t2Vector2<Type> t2Vector2<Type>::operator-()
	{
		t2Vector2<Type> v;
		v.set(-x, -y);
		return v;
	}

	template <class Type>
	t2Vector2<Type> t2Vector2<Type>::operator+()
	{
		return *this;
	}

	// 重载 二元 + -
	template <class Type>
	t2Vector2<Type> t2Vector2<Type>::operator+(const t2Vector2<Type>& vector) const
	{
		//--!加减号和左右乘顺序相同
		return t2Vector2<Type>(x + vector.x, y + vector.y);
	}

	template <class Type>
	t2Vector2<Type> t2Vector2<Type>::operator-(const t2Vector2<Type>& vector) const
	{
		return t2Vector2<Type>(x - vector.x, y - vector.y);
	}

	// 标量 乘除法 * / scale
	template <class Type>
	t2Vector2<Type> t2Vector2<Type>::operator*(const Type scale) const
	{
		return t2Vector2<Type>(x * scale, y * scale);
	}

	template <class Type>
	t2Vector2<Type> t2Vector2<Type>::operator/(const Type scale) const
	{
		if (scale == 0)
		{
#ifdef _DEBUG
			// --!未来替换为log
			std::cout << "除数不能为零!" << std::endl;
#endif
		}
		return t2Vector2<Type>(x / scale, y / scale);
	}

	// 重载 += -= *= /=
	template <class Type>
	t2Vector2<Type>& t2Vector2<Type>::operator+=(const t2Vector2<Type>& vector)
	{
		//--!之所以不使用重载后的+-*/是希望少调用一次函数 减少开销
		x += vector.x;
		y += vector.y;
		return *this;
	}

	template <class Type>
	t2Vector2<Type>& t2Vector2<Type>::operator-=(const t2Vector2<Type>& vector)
	{
		//--!之所以不使用重载后的+-*/是希望少调用一次函数 减少开销
		x -= vector.x;
		y -= vector.y;
		return *this;
	}

	template <class Type>
	t2Vector2<Type>& t2Vector2<Type>::operator*=(const Type scale)
	{
		//--!之所以不使用重载后的+-*/是希望少调用一次函数 减少开销
		x *= scale;
		y *= scale;
		return *this;
	}

	template <class Type>
	t2Vector2<Type>& t2Vector2<Type>::operator/=(const Type scale)
	{
		//--!之所以不使用重载后的+-*/是希望少调用一次函数 减少开销
		x /= scale;
		y /= scale;
		return *this;
	}

	// 向量 * vector(无需inline一个右乘 因为类型相同左右不分)
	template <class Type>
	Type t2Vector2<Type>::operator*(const t2Vector2<Type>& vector) const
	{
		return (x*vector.x + y*vector.y);
	}


	// 非成员函数
	// 左乘标量
	// --!float类型的Scale是为了避免Scale模板类型与Martix类型冲突导致编译器无法找到合理类型
	// template<class Scale, class Type>
	template<class Type>
	t2Vector2<Type> operator*(const float scale, const t2Vector2<Type>& vector)
	{
		return t2Vector2<Type>(scale * vector.x, scale * vector.y);
	}


	// vector左叉积一标量
	// 实质为将vector左旋90度得到tempV 之后再缩放scalar倍
	template<class Type>
	inline t2Vector2<Type> t2Cross(const Type scalar, const t2Vector2<Type>& vector)
	{
		return t2Vector2<Type>(-scalar*vector.y, scalar*vector.x);
	}

	// 特化
	typedef t2Vector2<float> t2Vector2f;
	typedef t2Vector2<int> t2Vector2i;

	// t2Point
	typedef t2Vector2f t2Point2f;
	typedef t2Vector2i t2Point2i;

	// 零向量
	static t2Vector2f t2Vector2fZero;
	static t2Vector2i t2Vector2iZero;

}

#endif