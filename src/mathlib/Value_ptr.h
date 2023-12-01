#pragma once

#include "Mat2x2.h"
#include "Mat3x3.h"
#include "Mat4x4.h"

namespace ft {
	GLfloat const* value_ptr(vec2 const& v);
	GLfloat* value_ptr(vec2& v);
	GLfloat const * value_ptr(vec3 const& v);
	GLfloat* value_ptr(vec3& v);
	GLfloat const* value_ptr(vec4 const& v);
	GLfloat* value_ptr(vec4& v);
	GLfloat const* value_ptr(mat2 const& m);
	GLfloat* value_ptr(mat2& m);
	GLfloat const* value_ptr(mat3 const& m);
	GLfloat* value_ptr(mat3& m);
	GLfloat const* value_ptr(mat4 const& m);
	GLfloat* value_ptr(mat4& m);
};