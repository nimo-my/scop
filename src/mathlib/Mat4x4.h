#pragma once
#include "Vector4.h"
#include "Mat2x2.h"
#include "Mat3x3.h"

namespace ft {
	struct mat4 {
		typedef vec4 col_type;
		typedef vec4 row_type;
		typedef mat4 type;
		typedef mat4 transpose_type;
		typedef GLfloat value_type;

	private:
		col_type value[4];

	public:

		mat4();
		mat4(mat4 const& m);
		mat4(GLfloat const& x);
		mat4(GLfloat const& x0, GLfloat const& y0, GLfloat const& z0, GLfloat const& w0,
			 GLfloat const& x1, GLfloat const& y1, GLfloat const& z1, GLfloat const& w1,
			 GLfloat const& x2, GLfloat const& y2, GLfloat const& z2, GLfloat const& w2,
			 GLfloat const& x3, GLfloat const& y3, GLfloat const& z3, GLfloat const& w3);
		mat4(col_type const& v0,
			 col_type const& v1,
			 col_type const& v2,
			 col_type const& v3);

		mat4(mat2 const& x);
		mat4(mat3 const& x);

		mat4& operator=(mat4 const& m);

		col_type & operator[](int i);
		col_type const& operator[](int i) const;

		mat4& operator+=(GLfloat s);
		mat4& operator+=(mat4 const& m);
		mat4& operator-=(GLfloat s);
		mat4& operator-=(mat4 const& m);
		mat4& operator*=(GLfloat s);
		mat4& operator*=(mat4 const& m);
		mat4& operator/=(GLfloat s);
		mat4& operator/=(mat4 const& m);

		mat4& operator++();
		mat4& operator--();
		mat4 operator++(int);
		mat4 operator--(int);
	};

	mat4 operator+(mat4 const& m);
	mat4 operator-(mat4 const& m);

	mat4 operator+(mat4 const& m, GLfloat const& s);
	mat4 operator+(GLfloat const& s, mat4 const& m);
	mat4 operator+(mat4 const& m1, mat4 const& m2);
	mat4 operator-(mat4 const& m, GLfloat const& s);
	mat4 operator-(GLfloat const& s, mat4 const& m);
	mat4 operator-(mat4 const& m1,	mat4 const& m2);
	mat4 operator*(mat4 const& m, GLfloat const& s);
	mat4 operator*(GLfloat const& s, mat4 const& m);
	typename mat4::col_type operator*(mat4 const& m, typename mat4::row_type const& v);
	typename mat4::row_type operator*(typename mat4::col_type const& v, mat4 const& m);
	mat4 operator*(mat4 const& m1, mat4 const& m2);
	mat4 operator/(mat4 const& m, GLfloat const& s);
	mat4 operator/(GLfloat const& s, mat4 const& m);
	typename mat4::col_type operator/(mat4 const& m, typename mat4::row_type const& v);
	typename mat4::row_type operator/(typename mat4::col_type const& v, mat4 const& m);
	mat4 operator/(mat4 const& m1,	mat4 const& m2);

	bool operator==(mat4 const& m1, mat4 const& m2);
	bool operator!=(mat4 const& m1, mat4 const& m2);
}