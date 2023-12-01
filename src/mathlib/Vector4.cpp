#include "Vector4.h"

namespace ft {
    vec4::vec4(): x{0.0f}, y(0.0f), z(0.0f), w(0.0f) {}
    vec4::vec4(vec4 const& v): x(v.x), y(v.y), z(v.z), w(v.w) {}
    vec4::vec4(GLfloat scalar): x(scalar), y(scalar), z(scalar), w(scalar) {}
    vec4::vec4(GLfloat x, GLfloat y, GLfloat z, GLfloat w): x(x), y(y), z(z), w(w) {}

    vec4::vec4(vec2 const& _xy, GLfloat _z, GLfloat _w): x(_xy.x), y(_xy.y), z(_z), w(_w) {}
    vec4::vec4(GLfloat _x, vec2 const& _yz, GLfloat _w): x(_x), y(_yz.x), z(_yz.y), w(_w) {}
    vec4::vec4(GLfloat _x, GLfloat _y, vec2 const& _zw): x(_x), y(_y), z(_zw.x), w(_zw.y) {}
    vec4::vec4(vec3 const& _xyz, GLfloat _w): x(_xyz.x), y(_xyz.y), z(_xyz.z), w(_w) {}
    vec4::vec4(GLfloat _x, vec3 const& _yzw): x(_x), y(_yzw.x), z(_yzw.y), w(_yzw.z) {}
    vec4::vec4(vec2 const& _xy, vec2 const& _zw): x(_xy.x), y(_xy.y), z(_zw.x), w(_zw.y) {}

    vec4& vec4::operator=(vec4 const& v) {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        this->w = v.w;

        return *this;
    }

    GLfloat & vec4::operator[](int i) {
        if (i == 0)
            return x;
        else if (i == 1)
            return y;
        else if (i == 2)
            return z;
        else if (i == 3)
            return w;
        else
            std::exit(-1);
    }

    GLfloat const& vec4::operator[](int i) const {
        if (i == 0)
            return x;
        else if (i == 1)
            return y;
        else if (i == 2)
            return z;
        else if (i == 3)
            return w;
        else
            std::exit(-1);
    }
    
    vec4& vec4::operator+=(GLfloat scalar) {
        this->x += scalar;
        this->y += scalar;
        this->z += scalar;
        this->w += scalar;

        return *this;
    }

    vec4& vec4::operator+=(vec4 const& v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;
        this->w += v.w;

        return *this;
    }

    vec4& vec4::operator-=(GLfloat scalar) {
        this->x -= scalar;
        this->y -= scalar;
        this->z -= scalar;
        this->w -= scalar;

        return *this;
    }

    vec4& vec4::operator-=(vec4 const& v) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;
        this->w -= v.w;

        return *this;
    }

    vec4& vec4::operator*=(GLfloat scalar) {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;
        this->w *= scalar;

        return *this;
    }

    vec4& vec4::operator*=(vec4 const& v) {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;
        this->w *= v.w;

        return *this;
    }

    vec4& vec4::operator/=(GLfloat scalar) {
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;
        this->w /= scalar;

        return *this;
    }

    vec4& vec4::operator/=(vec4 const& v) {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;
        this->w /= v.w;

        return *this;
    }

    vec4& vec4::operator++() {
		++this->x;
		++this->y;
		++this->z;
		++this->w;
		return *this;
    }

    vec4& vec4::operator--() {
		--this->x;
		--this->y;
		--this->z;
		--this->w;
		return *this;
    }

    vec4 vec4::operator++(int) {
        vec4 Result(*this);
		++*this;
		return Result;
    }

    vec4 vec4::operator--(int) {
		vec4 Result(*this);
		--*this;
		return Result;
    }

	vec4 operator+(vec4 const& v) {
        return vec4(v.x, v.y, v.z, v.w);
    }

	vec4 operator-(vec4 const& v) {
        return vec4(-v.x, -v.y, -v.z, -v.w);
    }

	vec4 operator+(vec4 const& v, GLfloat const & scalar) {
        return vec4(v.x + scalar, v.y + scalar, v.z + scalar, v.w + scalar);
    }

	vec4 operator+(GLfloat scalar, vec4 const& v) {
        return vec4(scalar + v.x, scalar + v.y, scalar + v.z, scalar + v.w);
    }

	vec4 operator+(vec4 const& v1, vec4 const& v2) {
        return vec4(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z, v1.w + v2.w);
    }

	vec4 operator-(vec4 const& v, GLfloat const & scalar) {
        return vec4(v.x - scalar, v.y - scalar, v.z - scalar, v.w - scalar);
    }

	vec4 operator-(GLfloat scalar, vec4 const& v) {
        return vec4(scalar - v.x, scalar - v.y, scalar - v.z, scalar - v.w);
    }

	vec4 operator-(vec4 const& v1, vec4 const& v2) {
        return vec4(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z, v1.w - v2.w);
    }

	vec4 operator*(vec4 const& v, GLfloat const & scalar) {
        return vec4(v.x * scalar, v.y * scalar, v.z * scalar, v.w * scalar);
    }

	vec4 operator*(GLfloat scalar, vec4 const& v) {
        return vec4(scalar * v.x, scalar * v.y, scalar * v.z, scalar * v.w);
    }

	vec4 operator*(vec4 const& v1, vec4 const& v2) {
        return vec4(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z, v1.w * v2.w);
    }

	vec4 operator/(vec4 const& v, GLfloat const & scalar) {
        return vec4(v.x / scalar, v.y / scalar, v.z / scalar, v.w / scalar);
    }

	vec4 operator/(GLfloat scalar, vec4 const& v) {
        return vec4(scalar / v.x, scalar / v.y, scalar / v.z, scalar / v.w);
    }

	vec4 operator/(vec4 const& v1, vec4 const& v2) {
        return vec4(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z, v1.w / v2.w);
    }

	bool operator==(vec4 const& v1, vec4 const& v2) {
        if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z && v1.w == v2.w)
            return true;
        else
            return false;
    }

	bool operator!=(vec4 const& v1, vec4 const& v2) {
        return !(v1 == v2);
    }

}