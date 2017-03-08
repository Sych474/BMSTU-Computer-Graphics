#ifndef MATH_LIB_H
#define MATH_LIB_H

#include <math.h>
#include <QDebug>
#include "config.h"

#define eps 0.000001

class Point
{
public:
    double x;
    double y;
    Point(double x, double y)
    {
        this->x = x;
        this->y = y;
    }
};


class Treangle
{
public:
    Point p1 = Point(0,0);
    Point p2 = Point(0,0);
    Point p3 = Point(0,0);
    Treangle()
    {
        this->p1 = Point(0,0);
        this->p2 = Point(0,0);
        this->p3 = Point(0,0);
    }
};

void movePoint(Point *p, double dx, double dy);

double orient_s(Point *a, Point *b, Point *c);

int is_triangle(Point *a, Point *b, Point *c);

double get_len(Point *p1, Point *p2);

double get_min_bisector(Point *p1, Point *p2, Point *p3);

double get_bisector(double a, double b, double c);

Point *get_bisector_end(Point *p1, Point *p2, Point *p3);


#endif // MATH_LIB_H
