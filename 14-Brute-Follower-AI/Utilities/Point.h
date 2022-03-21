//
// Created by Administrator on 8/17/2021.
//

#ifndef ENEMY_POINT_H
#define ENEMY_POINT_H

#include "math.h"

class Vector;

class Point {

public:
    //	members
    float x, y, z;

    //  constructors
    Point();
    Point(float x, float y, float z);

    //  Methods
    float sqrDist(const Point& p) const;


    Point operator+(const Vector& v) const;
    Point operator-(const Vector& v) const;
    Point& operator+=(const Vector& v);
    Point& operator-=(const Vector& v);

};


class Vector : public Point {
public:
    //	-	constructors
    Vector(float angle);
    Vector(float x, float y, float z);
    Vector(Point p1, Point p2);

    //	-	methodes
    void normalize();
    float magnitude();

    //	-	operators
    //	scalar product and division
    Vector operator*(const float k) const;
    Vector operator/(const float k) const;
    Vector& operator*=(const float k);
    Vector& operator/=(const float k);
    Vector operator-(const Vector& v);

    //	addition and subtraction of 2 vectors
    Vector operator+(const Vector& v2) const;
    Vector operator-(const Vector& v2) const;
    Vector& operator+=(const Vector& v2);
    Vector& operator-=(const Vector& v2);

    //	dot product and cross product
    double operator*(const Vector& v2) const;
    double operator^(const Vector& v2) const;
};

//	scalar product in regular order
Vector operator*(const float k, const Vector& v);


#endif //ENEMY_POINT_H
