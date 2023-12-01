#include "Vector2.h"
#include <cstdlib>

namespace ft {
    vec2::vec2(): x(0.0f), y(0.0f) {}
    vec2::vec2(vec2 const& v) : x(v.x), y(v.y) {}
    vec2::vec2(GLfloat scalar): x(scalar), y(scalar) {}
    vec2::vec2(GLfloat a, GLfloat b): x(a), y(b) {}

    vec2& vec2::operator=(vec2 const& v) {
        this->x = v.x;
        this->y = v.y;

        return *this;
    }

    GLfloat& vec2::operator[](int i) {
        if (i == 0)
            return x;
        else if (i == 1)
            return y;
        else
            std::exit(-1);
    }

    GLfloat const& vec2::operator[](int i) const {
        if (i == 0)
            return x;
        else if (i == 1)
            return y;
        else
            std::exit(-1);
    }

    vec2& vec2::operator+=(GLfloat scalar) {
        this->x += scalar;
        this->y += scalar;

        return *this;
    }

    vec2& vec2::operator-=(GLfloat scalar) {
        this->x -= scalar;
        this->y -= scalar;

        return *this;
    }

    vec2& vec2::operator+=(vec2 const& v) {
        this->x += v.x;
        this->y += v.y;

        return *this;
    }

    vec2& vec2::operator-=(vec2 const& v) {
        this->x -= v.x;
        this->y -= v.y;

        return *this;
    }

    vec2& vec2::operator*=(GLfloat scalar) {
        this->x *= scalar;
        this->y *= scalar;

        return *this;
    }

    vec2& vec2::operator*=(vec2 const& v) {
        this->x *= v.x;
        this->y *= v.y;

        return *this;
    }

    vec2& vec2::operator/=(GLfloat scalar) {
        this->x /= scalar;
        this->y /= scalar;

        return *this;
    }

    vec2& vec2::operator/=(vec2 const& v) {
        this->x /= v.x;
        this->y /= v.y;

        return *this;
    }

    vec2& vec2::operator++() {
        ++this->x;
        ++this->y;

        return *this;
    }

    vec2& vec2::operator--() {
        --this->x;
        --this->y;

        return *this;
    }
    
    vec2 vec2::operator++(int) {
        vec2 Result(*this);
		++*this;
		return Result;
    }

    vec2 vec2::operator--(int) {
        vec2 Result(*this);
		--*this;
		return Result;
    }

    vec2 operator+(vec2 const& v) {
        return v;
    }

	vec2 operator-(vec2 const& v) {
        return vec2(-v.x, -v.y);
    }

	vec2 operator+(vec2 const& v, GLfloat scalar) {
        return vec2(v.x + scalar, v.y + scalar);
    }

	vec2 operator+(GLfloat scalar, vec2 const& v) {
        return vec2(scalar + v.x, scalar + v.y);
    }

	vec2 operator+(vec2 const& v1, vec2 const& v2) {
        return vec2(v1.x + v2.x, v1.y + v2.y);
    }

	vec2 operator-(vec2 const& v, GLfloat scalar) {
        return vec2(v.x - scalar , v.y - scalar);
    }

	vec2 operator-(GLfloat scalar, vec2 const& v) {
        return vec2(scalar - v.x, scalar - v.y);
    }

	vec2 operator-(vec2 const& v1, vec2 const& v2) {
        return vec2(v1.x - v2.x, v1.y - v2.y);
    }

	vec2 operator*(vec2 const& v, GLfloat scalar) {
        return vec2(v.x * scalar, v.y * scalar);
    }

	vec2 operator*(GLfloat scalar, vec2 const& v) {
        return vec2(scalar * v.x, scalar * v.y);
    }

	vec2 operator*(vec2 const& v1, vec2 const& v2) {
        return vec2(v1.x * v2.x, v1.y * v2.y);
    }

	vec2 operator/(vec2 const& v, GLfloat scalar) {
        return vec2(v.x / scalar, v.y / scalar);
    }

	vec2 operator/(GLfloat scalar, vec2 const& v) {
        return vec2(scalar / v.x, scalar / v.y);
    }

	vec2 operator/(vec2 const& v1, vec2 const& v2) {
        return vec2(v1.x / v2.x, v1.y / v2.y);
    }

	bool operator==(vec2 const& v1, vec2 const& v2) {
        if (v1.x == v2.x && v1.y == v2.y)
            return true;
        else
            return false;
    }

	bool operator!=(vec2 const& v1, vec2 const& v2) {
        return !(v1 == v2);
    }

};
