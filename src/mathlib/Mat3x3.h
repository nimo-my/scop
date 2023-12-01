#pragma once

#include "Vector3.h"
#include "Mat2x2.h"

namespace ft {
	struct mat3 {
		typedef vec3 col_type;
		typedef vec3 row_type;
		typedef mat3 type;
		typedef mat3 transpose_type;
		typedef GLfloat value_type;
	private:
		col_type value[3];
	
	public:

		mat3();
		mat3(mat3 const& m);
		mat3(GLfloat scalar);
		mat3(GLfloat x0, GLfloat y0, GLfloat z0,
			 GLfloat x1, GLfloat y1, GLfloat z1,
			 GLfloat x2, GLfloat y2, GLfloat z2);
		mat3(col_type const& v0,
			 col_type const& v1,
			 col_type const& v2);
		mat3(mat2 const& x);

		mat3& operator=(mat3 const& m);

		col_type & operator[](int i);
		col_type const& operator[](int i) const;

		mat3& operator+=(GLfloat s);
		mat3& operator+=(mat3 const& m);
		mat3& operator-=(GLfloat s);
		mat3& operator-=(mat3 const& m);
		mat3& operator*=(GLfloat s);
		mat3& operator*=(mat3 const& m);
		mat3& operator/=(GLfloat s);
		mat3& operator/=(mat3 const& m);

		mat3& operator++();
		mat3& operator--();
		mat3 operator++(int);
		mat3 operator--(int);
	};

	mat3 operator+(mat3 const& m);
	mat3 operator-(mat3 const& m);

	mat3 operator+(mat3 const& m, GLfloat scalar);
	mat3 operator+(GLfloat scalar, mat3 const& m);
	mat3 operator+(mat3 const& m1, mat3 const& m2);
	mat3 operator-(mat3 const& m, GLfloat scalar);
	mat3 operator-(GLfloat scalar, mat3 const& m);
	mat3 operator-(mat3 const& m1, mat3 const& m2);
	mat3 operator*(mat3 const& m, GLfloat scalar);
	mat3 operator*(GLfloat scalar, mat3 const& m);
	typename mat3::col_type operator*(mat3 const& m, typename mat3::row_type const& v);
	typename mat3::row_type operator*(typename mat3::col_type const& v, mat3 const& m);
	mat3 operator*(mat3 const& m1, mat3 const& m2);
	mat3 operator/(mat3 const& m, GLfloat scalar);
	mat3 operator/(GLfloat scalar, mat3 const& m);
	typename mat3::col_type operator/(mat3 const& m, typename mat3::row_type const& v);
	typename mat3::row_type operator/(typename mat3::col_type const& v, mat3 const& m);
	mat3 operator/(mat3 const& m1, mat3 const& m2);
}