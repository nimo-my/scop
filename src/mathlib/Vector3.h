#pragma once

#include "Vector2.h"

namespace ft {
    struct vec3 {
		GLfloat x, y, z;

		GLfloat & operator[](int i);
		GLfloat const& operator[](int i) const;
		vec3();
		vec3(vec3 const& v);
		vec3(GLfloat scalar);
		vec3(GLfloat a, GLfloat b, GLfloat c);
		vec3(vec2 _xy, GLfloat z);
		vec3(GLfloat x, vec2 _yz);

		vec3& operator=(vec3 const& v);
		vec3& operator+=(vec3 const& v);
		vec3& operator+=(GLfloat scalar);
		vec3& operator-=(GLfloat scalar);
		vec3& operator-=(vec3 const& v);
		vec3& operator*=(GLfloat scalar);
		vec3& operator*=(vec3 const& v);
		vec3& operator/=(GLfloat scalar);
		vec3& operator/=(vec3 const& v);

		vec3& operator++();
		vec3& operator--();
		vec3 operator++(int);
		vec3 operator--(int);

	};
	vec3 operator+(vec3 const& v);
	vec3 operator-(vec3 const& v);

	vec3 operator+(vec3 const& v, GLfloat scalar);
	vec3 operator+(GLfloat scalar, vec3 const& v);
	vec3 operator+(vec3 const& v1, vec3 const& v2);
	vec3 operator-(vec3 const& v, GLfloat scalar);
	vec3 operator-(GLfloat scalar, vec3 const& v);
	vec3 operator-(vec3 const& v1, vec3 const& v2);
	vec3 operator*(vec3 const& v, GLfloat scalar);
	vec3 operator*(GLfloat scalar, vec3 const& v);
	vec3 operator*(vec3 const& v1, vec3 const& v2);
	vec3 operator/(vec3 const& v, GLfloat scalar);
	vec3 operator/(GLfloat scalar, vec3 const& v);
	vec3 operator/(vec3 const& v1, vec3 const& v2);
	bool operator==(vec3 const& v1, vec3 const& v2);
	bool operator!=(vec3 const& v1, vec3 const& v2);

};