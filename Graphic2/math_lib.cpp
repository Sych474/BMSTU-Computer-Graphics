#include "math_lib.h"

QPointF *Rot(QPointF p, double angle)
{
    qDebug()<<"deg"<<angle;
    angle *= M_PI/180;
    qDebug()<<"rad"<<angle;
    double matr[3][3] = {{cos(angle), -sin(angle), 0}, {sin(angle), cos(angle), 0}, {0, 0, 1}};
    double point[3] = {(double) p.x(),(double)  p.y(), 1};
    double ans[3] = {0,0,0};
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            ans[i] += point[j]*matr[i][j];
    QPointF *res_point = new QPointF(ans[0], ans[1]);
    return res_point;
}


void Rot1(QPointF &p, double angle, const double matr[3][3])
{
    double point[3] = {(double) p.x(),(double)  p.y(), 1};
    double ans[3] = {0,0,0};
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            ans[i] += point[j]*matr[i][j];
    p.setX(ans[0]);
    p.setY(ans[1]);
    //return res_point;
}

void ScalePoint(QPointF &p, double kx, double ky, const double matr[3][3])
{
    //double matr[3][3] = {{kx, 0, 0}, {0, ky, 0}, {0, 0, 1}};
    double point[3] = {(double) p.x(),(double)  p.y(), 1};
    double ans[3] = {0,0,0};
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            ans[i] += point[j]*matr[i][j];
    p.setX(ans[0]);
    p.setY(ans[1]);
    //QPointF *res_point = new QPointF(ans[0], ans[1]);
    //return res_point;
}
