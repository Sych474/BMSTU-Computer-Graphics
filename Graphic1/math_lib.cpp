#include "math_lib.h"

double orient_s(Point *a, Point *b, Point *c)
{
    qDebug()<< "Orient S"<<((a->x*b->y - a->y*b->x) + (a->x*c->y - a->y*c->x) + (b->x*c->y - b->y*c->x))/2;

    return ((a->x*b->y - a->y*b->x) + (a->x*c->y - a->y*c->x) + (b->x*c->y - b->y*c->x))/2;
}

int is_triangle(Point *a, Point *b, Point *c)
{
    return (fabs((c->x - a->x) * (b->y - a->y) - (c->y - a->y) * (b->x - a->x)) > EPS);
    if (fabs(orient_s(a, b, c)) < eps)
        return 0;
    qDebug()<<"Good";
    return 1;
}

double get_len(Point *p1, Point *p2)
{
    return sqrt(pow((p2->x - p1->x), 2) + pow((p2->y - p1->y), 2));
}

//биссектриса к стороне с
double get_bisector(double a, double b, double c)
{
    return sqrt(a*b * (a+b+c) * (a+b-c))/(a+b);
}


double get_min_bisector(Point *p1, Point *p2, Point *p3)
{
    double a = get_len(p1, p2);
    double b = get_len(p1, p3);
    double c = get_len(p2, p3);
    double min = get_bisector(a, b, c);
    min = fmin(min, get_bisector(a, c, b));
    min = fmin(min, get_bisector(b, c, a));
    qDebug()<<"min bisector: "<<min;
    return min;
}

void movePoint(Point *p, double dx, double dy)
{
    p->x += dx;
    p->y += dy;
}

// биссектрису строим от p1 к стороне p2-p3
Point *get_bisector_end(Point *p1, Point *p2, Point *p3)
{
    double k = get_len(p1, p2)/get_len(p1, p3);//k=a/b
    Point *res = new Point((p2->x + p3->x*k)/(k+1), (p2->y + p3->y*k)/(k+1));
    qDebug()<<"bisect_end_x: "<<res->x;
    qDebug()<<"bisect_end_y: "<<res->y;
    return res;
}
