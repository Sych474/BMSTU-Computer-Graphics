#ifndef MATH_LIB_H
#define MATH_LIB_H

#include <QDebug>
#include <QPointF>

#include <math.h>
#include "printinfo.h"


QPointF *Rot(QPointF p, double angle);

void Rot1(QPointF &p, double angle, const double matr[3][3]);

void ScalePoint(QPointF &p, double kx, double ky, const double matr[3][3]);
#endif // MATH_LIB_H
