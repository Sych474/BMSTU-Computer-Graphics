#ifndef TREANGLEINFO_H
#define TREANGLEINFO_H

#include "math_lib.h"

class TreangleInfo
{
private:
    //рабочие точки
    Point *p1 = NULL;
    Point *p2 = NULL;
    Point *p3 = NULL;
    Point *lower_bisector = NULL;
    Point *bisector2 = NULL;
    Point *bisector3 = NULL;
    //Строковые значения для вывода реальных координат
    QString str1;
    QString str2;
    QString str3;
    double dx;
    double dy;

private:
    QString *getStrCoord(Point *p);
public:
    TreangleInfo(Point *p1, Point *p2, Point *p3);

    Point *getBisector2() const;
    Point *getBisector3() const;
    Point *getP1() const;
    Point *getP2() const;
    Point *getP3() const;

    QString getAnsverText(void);

    void changeTreangle(Point *p1, Point *p2, Point *p3);
    double getDx() const;
    double getDy() const;
    Point *getLower_bisector() const;
    QString getStr1() const;
    QString getStr2() const;
    QString getStr3() const;
};

#endif // TREANGLEINFO_H
