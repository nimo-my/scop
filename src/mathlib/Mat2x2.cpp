#include "Common.h"

namespace ft {
    mat2::mat2(): value{col_type(1, 0), col_type(0, 1)} {}
    mat2::mat2(mat2 const& m): value{m[0], m[1]} {}
    mat2::mat2(GLfloat scalar): value{col_type(scalar, 0), col_type(0, scalar)} {}
    mat2::mat2(GLfloat const& x1, GLfloat const& y1, GLfloat const& x2, GLfloat const& y2): value{col_type(x1, x2), col_type(y1, y2)} {}
    mat2::mat2(col_type const& v1,
            col_type const& v2): value{col_type(v1), col_type(v2)} {}

	typename mat2::col_type& mat2::operator[](int i)
	{
		if (!(i >= 0 && i < 2))
			std::exit(-1);
		return this->value[i];
	}

	typename mat2::col_type const& mat2::operator[](int i) const
	{
		if (!(i >= 0 && i < 2))
			std::exit(-1);
		return this->value[i];
	}

    mat2& mat2::operator=(mat2 const& m) {
        this->value[0] = m[0];
        this->value[1] = m[1];

        return *this;
    }

    mat2& mat2::operator+=(GLfloat s) {
        this->value[0] += s;
        this->value[1] += s;

        return *this;
    }

    mat2& mat2::operator+=(mat2 const& m) {
        this->value[0] += m[0];
        this->value[1] += m[1];

        return *this;
    }

    mat2& mat2::operator-=(GLfloat s) {
        this->value[0] -= s;
        this->value[1] -= s;

        return *this;
    }

    mat2& mat2::operator-=(mat2 const& m) {
        this->value[0] -= m[0];
        this->value[1] -= m[1];

        return *this;
    }

    mat2& mat2::operator*=(GLfloat s) {
        this->value[0] *= s;
        this->value[1] *= s;

        return *this;
    }

    mat2& mat2::operator*=(mat2 const& m) {
        this->value[0] *= m[0];
        this->value[1] *= m[1];

        return *this;
    }

    mat2& mat2::operator/=(GLfloat s) {
        this->value[0] /= s;
        this->value[1] /= s;

        return *this;
    }

    mat2& mat2::operator/=(mat2 const& m) {
        this->value[0] /= m[0];
        this->value[0] /= m[1];

        return *this;
    }

    mat2& mat2::operator++() {
        ++this->value[0];
        ++this->value[1];
        
        return *this;
    }

    mat2& mat2::operator--() {
        --this->value[0];
        --this->value[1];

        return *this;
    }

    mat2 mat2::operator++(int) {
        mat2 res(*this);
        
        ++*this;
        return res;
    }

    mat2 mat2::operator--(int) {
        mat2 res(*this);

        --*this;
        return res;
    }

    mat2 operator+(mat2 const& m) {
        return mat2(m);
    }

	mat2 operator-(mat2 const& m) {
        return mat2(-m);
    }

	mat2 operator+(mat2 const& m, GLfloat scalar) {
        return mat2(m[0] + scalar, m[1] + scalar);
    }

	mat2 operator+(GLfloat scalar, mat2 const& m) {
        return mat2(scalar + m[0], scalar + m[1]);
    }

	mat2 operator+(mat2 const& m1, mat2 const& m2) {
        return mat2(m1[0] + m2[0], m1[1] + m2[1]);
    }

	mat2 operator-(mat2 const& m, GLfloat scalar) {
        return mat2(m[0] - scalar, m[1] - scalar);
    }

	mat2 operator-(GLfloat scalar, mat2 const& m) {
        return mat2(scalar - m[0], scalar - m[1]);
    }

	mat2 operator-(mat2 const& m1, mat2 const& m2) {
        return mat2(m1[0] - m2[0], m1[1] - m2[1]);
    }

	mat2 operator*(mat2 const& m, GLfloat scalar) {
        return mat2(m[0] * scalar, m[1] * scalar);
    }

	mat2 operator*(GLfloat scalar, mat2 const& m) {
        return mat2(scalar * m[0], scalar * m[1]);
    }

	typename mat2::col_type operator*(mat2 const& m, typename mat2::row_type const& v) {
        return vec2(
			m[0][0] * v.x + m[1][0] * v.y,
			m[0][1] * v.x + m[1][1] * v.y);
    }

	typename mat2::row_type operator*(typename mat2::col_type const& v, mat2 const& m) {
        return vec2(
            v.x * m[0][0] + v.y * m[0][1],
			v.x * m[1][0] + v.y * m[1][1]);
    }

	mat2 operator*(mat2 const& m1, mat2 const& m2) {
        return mat2(
            m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0],
            m1[0][1] * m2[0][0] + m1[1][1] * m2[0][1],
			m1[0][0] * m2[1][0] + m1[1][0] * m2[1][1],
			m1[0][1] * m2[1][0] + m1[1][1] * m2[1][1]);
    }

	mat2 operator/(mat2 const& m, GLfloat scalar) {
		return mat2(
			m[0] / scalar,
			m[1] / scalar);
    }

	mat2 operator/(GLfloat scalar, mat2 const& m) {
		return mat2(
			scalar / m[0],
			scalar / m[1]);

    }

	typename mat2::col_type operator/(mat2 const& m, typename mat2::row_type const& v) {
		return inverse(m) * v;

    }

	typename mat2::row_type operator/(typename mat2::col_type const& v, mat2 const& m) {
		return v * inverse(m);
    }

	mat2 operator/(mat2 const& m1, mat2 const& m2) {
		mat2 m1_copy(m1);

		return m1_copy /= m2;
    }

};
