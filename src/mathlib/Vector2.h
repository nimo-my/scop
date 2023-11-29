#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <glad/glad.h>

namespace ft {
    struct vec2 {
		GLfloat x, y;

		GLfloat & operator[](int i);
		GLfloat const& operator[](int i) const;
		vec2();
		vec2(vec2 const& v);
		vec2(GLfloat scalar);
		vec2(GLfloat a, GLfloat b);

		vec2 & operator=(vec2 const& v);
		vec2 & operator+=(GLfloat scalar);
		vec2 & operator+=(vec2 const& v);
		vec2 & operator-=(GLfloat scalar);
		vec2 & operator-=(vec2 const& v);
		vec2 & operator*=(GLfloat scalar);
		vec2 & operator*=(vec2 const& v);
		vec2 & operator/=(GLfloat scalar);
		vec2 & operator/=(vec2 const& v);

		vec2 & operator++();
		vec2 & operator--();
		vec2 operator++(int);
		vec2 operator--(int);
    };

    vec2 operator+(vec2 const& v);
	vec2 operator-(vec2 const& v);
	vec2 operator+(vec2 const& v, GLfloat scalar);
	vec2 operator+(GLfloat scalar, vec2 const& v);
	vec2 operator+(vec2 const& v1, vec2 const& v2);
	vec2 operator-(vec2 const& v, GLfloat scalar);
	vec2 operator-(GLfloat scalar, vec2 const& v);
	vec2 operator-(vec2 const& v1, vec2 const& v2);
	vec2 operator*(vec2 const& v, GLfloat scalar);
	vec2 operator*(GLfloat scalar, vec2 const& v);
	vec2 operator*(vec2 const& v1, vec2 const& v2);
	vec2 operator/(vec2 const& v, GLfloat scalar);
	vec2 operator/(GLfloat scalar, vec2 const& v);
	vec2 operator/(vec2 const& v1, vec2 const& v2);
	bool operator==(vec2 const& v1, vec2 const& v2);
	bool operator!=(vec2 const& v1, vec2 const& v2);
};
