#include "Common.h"

namespace ft {
    mat2 makeSubMatrix(mat3 m, int _row, int _col) {
		mat2 ret = mat2();
		if (!(_row >= 0 && _row < 3) || !(_col >= 0 && _col < 3))
			return ret;
		int row = 0;
		for (int i = 0 ; i < 3 ; i++)
		{
			if (i == _row)
				continue;
			int column = 0;
			for (int j = 0 ; j < 3 ; j++)
			{
				if (j == _col)
					continue;
				ret[column][row] = m[j][i];
				column++;
			}
			row++;
		}
		return ret;
	}

	mat3 makeSubMatrix(mat4 m, int _row, int _col) {
		mat3 ret = mat3();
		if (!(_row >= 0 && _row < 4) || !(_col >= 0 && _col < 4))
			return ret;
		int row = 0;
		for (int i = 0 ; i < 4 ; i++)
		{
			if (i == _row)
				continue;
			int column = 0;
			for (int j = 0 ; j < 4 ; j++)
			{
				if (j == _col)
					continue;
				ret[column][row] = m[j][i];
				column++;
			}
			row++;
		}
		return ret;
	}


    GLfloat pi() {
        return static_cast<GLfloat>(3.1415926535897932384626433832795028);
    }

	GLfloat determinant(mat2 const& m) {
        return m[0][0] * m[1][1] - m[1][0] * m[0][1];
    }

	GLfloat determinant(mat3 const& m) {
        GLfloat det = 0.0f;
		for (int column  = 0 ; column < 3 ; column++) {
			det += m[column][0] * ((column + 2) % 2 == 0 ? 1 : -1) * determinant(makeSubMatrix(m, 0, column));
		}

		return det;
    }

	GLfloat determinant(mat4 const& m) {
		GLfloat det = 0.0f;
		for (int column  = 0 ; column < 4 ; column++) {
			det += m[column][0] * (column % 2 == 0 ? 1 : -1) * determinant(makeSubMatrix(m, 0, column));
		}
		return det;

    }

	mat2 transpose(mat2 const& m) {
		return mat2(vec2(m[0][0], m[1][0]), vec2(m[0][1], m[1][1]));
    }

	mat3 transpose(mat3 const& m) {
		return mat3(vec3(m[0][0], m[1][0], m[2][0]),
					vec3(m[0][1], m[1][1], m[2][1]),
					vec3(m[0][2], m[1][2], m[2][2]));

    }

	mat4 transpose(mat4 const& m) {
		return mat4(vec4(m[0][0], m[1][0], m[2][0], m[3][0]),
					vec4(m[0][1], m[1][1], m[2][1], m[3][1]),
					vec4(m[0][2], m[1][2], m[2][2], m[3][2]),
					vec4(m[0][3], m[1][3], m[2][3], m[3][3]));
    }

	mat2 inverse(mat2 const& m) {
		GLfloat det = determinant(m);

		return mat2(vec2(m[1][1], -m[0][1]), vec2(-m[1][0], m[0][0])) / det;
	}

	mat3 inverse(mat3 const& m) {
        GLfloat det = determinant(m);

        mat3 transM = transpose(m);
		mat3 ret = mat3();
		for (int row = 0 ; row < 3 ; row++) {
			for (int column = 0 ; column < 3 ; column++) {
				ret[column][row] = ((row + column) % 2 == 0 ? 1 : -1) * determinant(makeSubMatrix(transM, row, column));
			}
		}
		return ret / det;
    }

	mat4 inverse(mat4 const& m) {
		GLfloat det = determinant(m);
		mat4 transM = transpose(m);
		mat4 ret = mat4();
		for (int row = 0 ; row < 4 ; row++) {
			for (int column = 0 ; column < 4 ; column++) {
				ret[column][row] = ((row + column) % 2 == 0 ? 1 : -1) * determinant(makeSubMatrix(transM, row, column));
			}
		}
		return ret / det;
    }

	GLfloat radians(GLfloat degrees) {
        return degrees * 0.01745329251994329576923690768489;
    }

	GLfloat length(vec2 const& v) {
		return sqrt(v.x * v.x + v.y * v.y);
    }

	GLfloat length(vec3 const& v) {
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
    }

	GLfloat length(vec4 const& v) {
		return sqrt(v.x * v.x + v.y * v.y + v.z * v.z + v.w * v.w);
    }

	GLfloat distance(vec2 const& p0, vec2 const& p1) {
		return length(vec2(p1.x - p0.x, p1.y - p0.y));
    }

	GLfloat distance(vec3 const& p0, vec3 const& p1) {
		return length(vec3(p1.x - p0.x, p1.y - p0.y, p1.z - p0.z));
    }

	GLfloat distance(vec4 const& p0, vec4 const& p1) {
        return length(vec4(p1.x - p0.x, p1.y - p0.y, p1.z - p0.z, p1.w - p0.w));
    }

	vec2 normalize(vec2 v) {
		GLfloat dist = length(v);
		return vec2(v) / dist;
    }

	vec3 normalize(vec3 v) {
        GLfloat dist = length(v);
        return vec3(v) / dist;
    }

	vec4 normalize(vec4 v) {
        GLfloat dist = length(v);
        return vec4(v) / dist;
    }

	mat4 translate(mat4 const& m, vec3 const& v) {
        mat4 Result(m);
		Result[3] = m[0] * v[0] + m[1] * v[1] + m[2] * v[2] + m[3];
		return Result;
    }

	mat4 rotate(mat4 const& m, GLfloat angle, vec3 const& v) {
		GLfloat const a = angle;
		GLfloat const cosine = cos(a);
		GLfloat const sine = sin(a);

		vec3 axis(normalize(v));
		mat3 K = mat3(vec3(0, axis.z, -axis.y),
					  vec3(-axis.z, 0, axis.x),
					  vec3(axis.y, -axis.x, 0));
		mat3 Rotate = mat3(1.0f) + sine * K + (1 - cosine) * (K * K);

		mat4 Result;
		Result[0] = m[0] * Rotate[0][0] + m[1] * Rotate[0][1] + m[2] * Rotate[0][2];
		Result[1] = m[0] * Rotate[1][0] + m[1] * Rotate[1][1] + m[2] * Rotate[1][2];
		Result[2] = m[0] * Rotate[2][0] + m[1] * Rotate[2][1] + m[2] * Rotate[2][2];
		Result[3] = m[3];
		return Result;
    }

	mat4 perspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar) {
		GLfloat const tanHalfFovy = tan(fovy / static_cast<GLfloat>(2));

		mat4 Result(static_cast<GLfloat>(0));
		Result[0][0] = static_cast<GLfloat>(1) / (aspect * tanHalfFovy);
		Result[1][1] = static_cast<GLfloat>(1) / (tanHalfFovy);
		Result[2][2] = -(zFar + zNear) / (zFar - zNear);
		Result[2][3] = static_cast<GLfloat>(-1);
		Result[3][2] = -2 * (zFar * zNear) / (zFar - zNear);
		return Result;
    }

	vec3 cross(vec3 const& a, vec3 const& b) {
		mat3 crossMat = mat3(vec3(0.0f, a.z, -a.y),
							 vec3(-a.z, 0.0f, a.x),
							 vec3(a.y, -a.x, 0.0f));
		return crossMat * b;
    }

	mat4 lookAt(vec3 const& eye, vec3 const& center, vec3 const& up) {
		vec3 const f(normalize(center - eye));
		vec3 const s(normalize(cross(f, up)));
		vec3 const u(cross(s, f));

		mat4 Result(1);
		Result[0][0] = s.x;
		Result[1][0] = s.y;
		Result[2][0] = s.z;
		Result[0][1] = u.x;
		Result[1][1] = u.y;
		Result[2][1] = u.z;
		Result[0][2] =-f.x;
		Result[1][2] =-f.y;
		Result[2][2] =-f.z;
		Result[3][0] =-dot(s, eye);
		Result[3][1] =-dot(u, eye);
		Result[3][2] = dot(f, eye);

		return Result;
    }

	mat4 scale(mat4 const& m, vec3 const& v) {
		mat4 Result;
		Result[0] = m[0] * v[0];
		Result[1] = m[1] * v[1];
		Result[2] = m[2] * v[2];
		Result[3] = m[3];
		return Result;
    }

	GLfloat dot(vec2 const& x, vec2 const& y) {
		vec2 ret = x * y;
		return ret.x + ret.y;
    }

	GLfloat dot(vec3 const& x, vec3 const& y) {
		vec3 ret = x * y;
		return ret.x + ret.y + ret.z;
    }

	GLfloat dot(vec4 const& x, vec4 const& y) {
		vec4 ret = x * y;
		return ret.x + ret.y + ret.z + ret.w;
    }

	GLfloat max(GLfloat lhs, GLfloat rhs) {
		return lhs > rhs ? lhs : rhs;
	}

	GLfloat getClamp(GLfloat value, GLfloat minVal, GLfloat maxVal) {
		if (value < minVal) {
			return minVal;
		} else if (value > maxVal) {
			return maxVal;
		} else {
			return value;
		}
	}

	vec4 clamp(const vec4& vector, GLfloat minVal, GLfloat maxVal) {
		vec4 vec = vec4();

		vec.x = getClamp(vector.x, minVal, maxVal);
		vec.y = getClamp(vector.y, minVal, maxVal);
		vec.z = getClamp(vector.z, minVal, maxVal);
		vec.w = getClamp(vector.w, minVal, maxVal);
		
		return vec;
	}
}