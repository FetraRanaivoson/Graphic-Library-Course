//
// Created by Administrator on 8/17/2021.
//

#include "Point.h"

Point::Point() {}
Point::Point(float x, float y, float z) : x(x), y(y), z(z) {}

float Point::sqrDist(const Point &p) const {
    float dx = this->x - p.x;
    float dy = this->y - p.y;
    float dz = this->z - p.z;

    return dx * dx + dy * dy + dz * dz;
}


Point Point::operator+(const Vector& v) const {
    return {this->x + v.x, this->y + v.y,
                 this->z +v.z};
}

Point Point::operator-(const Vector& v) const {
    return {this->x - v.x, this->y - v.y,
                 this->z -v.z};
}

Point& Point::operator+=(const Vector& v) {
    this->x += v.x;
    this->y += v.y;
    this->z += v.z;

    return *this;
}

Point& Point::operator-=(const Vector& v) {
    this->x -= v.x;
    this->y -= v.y;
    this->z -= v.z;

    return *this;
}

//	****************
//	class of vectors
//	****************
//	-	constructors
//Vector::Vector(float angle) : Point(cos(angle), sin(angle)) {
//}
//
Vector::Vector(float x, float y, float z) : Point(x, y,z) {
}



//	-	methodes
void Vector::normalize() {
    float d = this->magnitude();
    this->x /= d;
    this->y /= d;
    this->z /= d;
}

float Vector::magnitude() {
    return sqrt(this->x * this->x + this->y * this->y + this->z * this->z);
}

//	-	operators
//	scalar product and division
Vector Vector::operator*(const float k) const {
    return {k * this->x, k * this->y, k * this->z};
}

Vector Vector::operator/(const float k) const {
    return {this->x / k, this->y / k,  this->z / k};
}

Vector& Vector::operator*=(const float k) {
    this->x *= k;
    this->y *= k;
    this->z = k;

    return *this;
}

Vector& Vector::operator/=(const float k) {
    this->x /= k;
    this->y /= k;
    this->z /= k;

    return *this;
}

Vector Vector::operator-(const Vector& v) {
    return {this->x - v.x, this->y - v.y,
                  this->z -v.z};
}

//	addition and subtraction of 2 vectors
Vector Vector::operator+(const Vector& v2) const {
    return {this->x + v2.x, this->y + v2.y, this->z + v2.z};
}

Vector Vector::operator-(const Vector& v2) const {
    return {this->x - v2.x, this->y - v2.y, this->z - v2.z};
}

Vector& Vector::operator+=(const Vector& v2) {
    this->x += v2.x;
    this->y += v2.y;
    this->z += v2.z;

    return *this;
}

Vector& Vector::operator-=(const Vector& v2) {
    this->x -= v2.x;
    this->y -= v2.y;
    this->z -= v2.z;

    return *this;
}



//	dot product and cross product
double Vector::operator*(const Vector& v2) const {
    return this->x * v2.x + this->y * v2.y + this->z * v2.z;
}

double Vector::operator^(const Vector& v2) const {
    return this->x * v2.y - this->y * v2.x;
}

//	scalar product in regular order
Vector operator*(const float k, const Vector& v) {
    return Vector(k * v.x, k * v.y, k * v.z);
}

