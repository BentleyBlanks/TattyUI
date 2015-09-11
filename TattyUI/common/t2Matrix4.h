#ifndef T2_MATRIX4_H
#define T2_MATRIX4_H

namespace TattyUI
{
	class t2Matrix4
	{
	public:
		t2Matrix4();

		t2Matrix4(float a00, float a01, float a02, float a03,
			float a10, float a11, float a12, float a13,
			float a20, float a21, float a22, float a23,
			float a30, float a31, float a32, float a33);

		~t2Matrix4(){}

		void set(float a00, float a01, float a02, float a03,
			float a10, float a11, float a12, float a13,
			float a20, float a21, float a22, float a23,
			float a30, float a31, float a32, float a33);

		bool isIdentity() const;

		void makeIdentity();

		void makeOrtho2DMatrix(double left, double right, double bottom, double top);

		float _mat[4][4];

	};
}

#endif