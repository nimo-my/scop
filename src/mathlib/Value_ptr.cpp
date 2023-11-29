#include "value_ptr.h"

namespace ft {
	GLfloat const* value_ptr(vec2 const& v) {
		return &(v.x);
	}

	GLfloat* value_ptr(vec2& v) {
		return &(v.x);
	}

	GLfloat const * value_ptr(vec3 const& v) {
		return &(v.x);
	}

	GLfloat* value_ptr(vec3& v) {
		return &(v.x);
	}

	GLfloat const* value_ptr(vec4 const& v) {
		return &(v.x);
	}

	GLfloat* value_ptr(vec4& v) {
		return &(v.x);
	}

	GLfloat const* value_ptr(mat2 const& m) {
		return &(m[0].x);
	}

	GLfloat* value_ptr(mat2& m) {
		return &(m[0].x);
	}

	GLfloat const* value_ptr(mat3 const& m) {
		return &(m[0].x);
	}

	GLfloat* value_ptr(mat3& m) {
		return &(m[0].x);
	}

	GLfloat const* value_ptr(mat4 const& m) {
		return &(m[0].x);
	}

	GLfloat* value_ptr(mat4& m) {
		return &(m[0].x);
	}
};