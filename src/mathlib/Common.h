#pragma once

#include "Mat2x2.h"
#include "Mat3x3.h"
#include "Mat4x4.h"
#include <cmath>

namespace ft {
	GLfloat pi();
	GLfloat determinant(mat2 const& m);
	GLfloat determinant(mat3 const& m);
	GLfloat determinant(mat4 const& m);
	mat2 transpose(mat2 const& m);
	mat3 transpose(mat3 const& m);
	mat4 transpose(mat4 const& m);
	mat2 inverse(mat2 const& m);
	mat3 inverse(mat3 const& m);
	mat4 inverse(mat4 const& m);

	GLfloat radians(GLfloat degrees);
	GLfloat length(vec2 const& v);
	GLfloat length(vec3 const& v);
	GLfloat length(vec4 const& v);
	GLfloat distance(vec2 const& p0, vec2 const& p1);
	GLfloat distance(vec3 const& p0, vec3 const& p1);
	GLfloat distance(vec4 const& p0, vec4 const& p1);
	vec2 normalize(vec2 v);
	vec3 normalize(vec3 v);
	vec4 normalize(vec4 v);

	mat4 translate(mat4 const& m, vec3 const& v);
	mat4 rotate(mat4 const& m, GLfloat angle, vec3 const& v);
	mat4 perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);
	vec3 cross(vec3 const& a, vec3 const& b);
	mat4 lookAt(vec3 const& eye, vec3 const& center, vec3 const& up);
	mat4 scale(mat4 const& m, vec3 const& v);

	GLfloat dot(vec2 const& x, vec2 const& y);
	GLfloat dot(vec3 const& x, vec3 const& y);
	GLfloat dot(vec4 const& x, vec4 const& y);
	GLfloat max(GLfloat lhs, GLfloat rhs);
	vec4 clamp(const vec4& vector, GLfloat minVal, GLfloat maxVal);

}