#include "Vector3.h"

namespace ft {
    vec3::vec3(): x(0.0f), y(0.0f), z(0.0f) {}

    vec3::vec3(vec3 const& v): x(v.x), y(v.y), z(v.z) {}

    vec3::vec3(GLfloat scalar): x(scalar), y(scalar), z(scalar) {}

    vec3::vec3(GLfloat a, GLfloat b, GLfloat c): x(a), y(b), z(c) {}

    vec3::vec3(vec2 _xy, GLfloat z): x(_xy.x), y(_xy.y), z(z) {}

    vec3::vec3(GLfloat x, vec2 _yz): x(x), y(_yz.x), z(_yz.y) {}

    vec3& vec3::operator=(vec3 const& v) {
        this->x = v.x;
        this->y = v.y;
        this->z = v.z;
        
        return *this;
    }

    GLfloat& vec3::operator[](int i) {
        if (i == 0)
            return x;
        else if (i == 1)
            return y;
        else if (i == 2)
            return z;
        else
            std::exit(-1);
    }

    GLfloat const& vec3::operator[](int i) const {
        if (i == 0)
            return x;
        else if (i == 1)
            return y;
        else if (i == 2)
            return z;
        else
            std::exit(-1);
    }

    vec3& vec3::operator+=(GLfloat scalar) {
        this->x += scalar;
        this->y += scalar;
        this->z += scalar;

        return *this;
    }

    vec3& vec3::operator+=(vec3 const& v) {
        this->x += v.x;
        this->y += v.y;
        this->z += v.z;

        return *this;
    }

    vec3& vec3::operator-=(GLfloat scalar) {
        this->x -= scalar;
        this->y -= scalar;
        this->z -= scalar;

        return *this;
    }

    vec3& vec3::operator-=(vec3 const& v) {
        this->x -= v.x;
        this->y -= v.y;
        this->z -= v.z;

        return *this;
    }

    vec3& vec3::operator*=(GLfloat scalar) {
        this->x *= scalar;
        this->y *= scalar;
        this->z *= scalar;

        return *this;
    }

    vec3& vec3::operator*=(vec3 const& v) {
        this->x *= v.x;
        this->y *= v.y;
        this->z *= v.z;

        return *this;
    }

    vec3& vec3::operator/=(GLfloat scalar) {
        this->x /= scalar;
        this->y /= scalar;
        this->z /= scalar;

        return *this;
    }

    vec3& vec3::operator/=(vec3 const& v) {
        this->x /= v.x;
        this->y /= v.y;
        this->z /= v.z;

        return *this;
    }

    vec3 & vec3::operator++() {
        ++this->x;
        ++this->y;
        ++this->z;

        return *this;
    }

    vec3 & vec3::operator--() {
        --this->x;
        --this->y;
        --this->z;

        return *this;
    }

    vec3 vec3::operator++(int) {
        vec3 res(*this);
        ++*this;
        return *this;
    }

    vec3 vec3::operator--(int) {
        vec3 res(*this);
        --*this;
        return *this;
    }

    vec3 operator+(vec3 const& v) {
        return vec3(v.x, v.y, v.z);        
    }

	vec3 operator-(vec3 const& v) {
        return vec3(-v.x, -v.y, -v.z);
    }

	vec3 operator+(vec3 const& v, GLfloat scalar) {
        return vec3(v.x + scalar, v.y + scalar, v.z + scalar);
    }

	vec3 operator+(GLfloat scalar, vec3 const& v) {
        return vec3(scalar + v.x, scalar + v.y, scalar + v.z);
    }

	vec3 operator+(vec3 const& v1, vec3 const& v2) {
        return vec3(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
    }

	vec3 operator-(vec3 const& v, GLfloat scalar) {
        return vec3(v.x - scalar, v.y - scalar, v.z - scalar);
    }

	vec3 operator-(GLfloat scalar, vec3 const& v) {
        return vec3(scalar - v.x, scalar - v.y, scalar - v.z);
    }

	vec3 operator-(vec3 const& v1, vec3 const& v2) {
        return vec3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
    }

	vec3 operator*(vec3 const& v, GLfloat scalar) {
        return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
    }

	vec3 operator*(GLfloat scalar, vec3 const& v) {
        return vec3(scalar * v.x, scalar * v.y, scalar * v.z);
    }

	vec3 operator*(vec3 const& v1, vec3 const& v2) {
        return vec3(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
    }

	vec3 operator/(vec3 const& v, GLfloat scalar) {
        return vec3(v.x / scalar, v.y / scalar, v.z / scalar);
    }

	vec3 operator/(GLfloat scalar, vec3 const& v) {
        return vec3(scalar / v.x, scalar / v.y, scalar / v.z);
    }

	vec3 operator/(vec3 const& v1, vec3 const& v2) {
        return vec3(v1.x / v2.x, v1.y / v2.y, v1.z / v2.z);
    }

	bool operator==(vec3 const& v1, vec3 const& v2) {
        if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
            return true;
        else
            return false;
    }

	bool operator!=(vec3 const& v1, vec3 const& v2) {
        return !(v1 == v2);
    }


}
