#pragma once

#include "Vector3.h"

namespace ft {
    struct vec4 {
		GLfloat x, y, z, w;

		GLfloat & operator[](int i);
		GLfloat const& operator[](int i) const;

		vec4();
		vec4(vec4 const& v);
		vec4(GLfloat scalar);
		vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w);

		vec4(vec2 const& _xy, GLfloat _z, GLfloat _w);
		vec4(GLfloat _x, vec2 const& _yz, GLfloat _w);
		vec4(GLfloat _x, GLfloat _y, vec2 const& _zw);
		vec4(vec3 const& _xyz, GLfloat _w);
		vec4(GLfloat _x, vec3 const& _yzw);
		vec4(vec2 const& _xy, vec2 const& _zw);

		vec4& operator=(vec4 const& v);
		vec4& operator+=(GLfloat scalar);
		vec4& operator+=(vec4 const& v);
		vec4& operator-=(GLfloat scalar);
		vec4& operator-=(vec4 const& v);
		vec4& operator*=(GLfloat scalar);
		vec4& operator*=(vec4 const& v);
		vec4& operator/=(GLfloat scalar);
		vec4& operator/=(vec4 const& v);

		vec4& operator++();
		vec4& operator--();
		vec4 operator++(int);
		vec4 operator--(int);
	};

	vec4 operator+(vec4 const& v);
	vec4 operator-(vec4 const& v);
	vec4 operator+(vec4 const& v, GLfloat const & scalar);
	vec4 operator+(GLfloat scalar, vec4 const& v);
	vec4 operator+(vec4 const& v1, vec4 const& v2);
	vec4 operator-(vec4 const& v, GLfloat const & scalar);
	vec4 operator-(GLfloat scalar, vec4 const& v);
	vec4 operator-(vec4 const& v1, vec4 const& v2);
	vec4 operator*(vec4 const& v, GLfloat const & scalar);
	vec4 operator*(GLfloat scalar, vec4 const& v);
	vec4 operator*(vec4 const& v1, vec4 const& v2);
	vec4 operator/(vec4 const& v, GLfloat const & scalar);
	vec4 operator/(GLfloat scalar, vec4 const& v);
	vec4 operator/(vec4 const& v1, vec4 const& v2);
	bool operator==(vec4 const& v1, vec4 const& v2);
	bool operator!=(vec4 const& v1, vec4 const& v2);

}