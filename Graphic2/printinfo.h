#ifndef PRINTINFO_H
#define PRINTINFO_H

#include "math_lib.h"

#include <QDebug>
#include <QPointF>
#include <QPolygonF>

class PrintInfo
{
public:
    QPointF center;
    QPointF p1;
    QPointF p2;
    QPointF p3;
    QPointF p4;
    QPolygonF cercle;
    QPolygonF astroid;
private:
    void move(PrintInfo *, QPointF);
public:
    PrintInfo();
    PrintInfo(PrintInfo *);
    PrintInfo(const PrintInfo &obj);
    PrintInfo *Move(QPointF *);
    PrintInfo *Scale(QPointF *p, double kx, double ky);
    PrintInfo *Rotate(QPointF *p, double angle);

    void DBGPRINT(void);
};

#endif // PRINTINFO_H
