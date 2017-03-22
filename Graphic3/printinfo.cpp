#include "printinfo.h"

PrintInfo::PrintInfo(const PrintInfo &obj)
{
    this->center = obj.center;
    this->p1 = obj.p1;
    this->p2 = obj.p2;
    this->p3 = obj.p3;
    this->p4 = obj.p4;
    this->cercle = obj.cercle;
    this->astroid = obj.astroid;
}

PrintInfo *PrintInfo::Move(QPointF *p)
{
    PrintInfo *new_info = new PrintInfo(this);
    QPointF move = QPointF(p->x(), p->y());
    //move_point += new_info->center;
    this->move(new_info, move);
    return new_info;

}

PrintInfo *PrintInfo::Scale(QPointF *p, double kx, double ky)
{
    PrintInfo *new_info = new PrintInfo(this);
    QPointF move_point = QPointF(-p->x(), -p->y());
    move_point -= new_info->center;
    this->move(new_info, move_point);
    double matr[3][3] = {{kx, 0, 0}, {0, ky, 0}, {0, 0, 1}};
    ScalePoint(new_info->p1, kx, ky, matr);
    ScalePoint(new_info->p2, kx, ky, matr);
    ScalePoint(new_info->p3, kx, ky, matr);
    ScalePoint(new_info->p4, kx, ky, matr);
    /*
    new_info->p1 = *(ScalePoint(new_info->p1, kx, ky));
    new_info->p2 = *(ScalePoint(new_info->p2, kx, ky));
    new_info->p3 = *(ScalePoint(new_info->p3, kx, ky));
    new_info->p4 = *(ScalePoint(new_info->p4, kx, ky));
    */
    for (int i = 0; i < new_info->cercle.count(); ++i)
         //new_info->cercle[i] = *(ScalePoint(new_info->cercle[i], kx, ky));
        ScalePoint(new_info->cercle[i], kx, ky, matr);
    for (int i = 0; i < new_info->astroid.count(); ++i)
        //new_info->astroid[i] = *(ScalePoint(new_info->astroid[i],  kx, ky));
        ScalePoint(new_info->astroid[i],  kx, ky, matr);
    move_point*=-1;
    this->move(new_info, move_point);

    return new_info;
}

PrintInfo *PrintInfo::Rotate(QPointF *p, double angle)
{
    PrintInfo *new_info = new PrintInfo(this);
    QPointF move_point = QPointF(-p->x(), -p->y());
    angle *= M_PI/180;
    double matr[3][3] = {{cos(angle), -sin(angle), 0}, {sin(angle), cos(angle), 0}, {0, 0, 1}};

    move_point -= new_info->center;
    this->move(new_info, move_point);

    Rot1(new_info->p1, angle, matr);
    Rot1(new_info->p2, angle, matr);
    Rot1(new_info->p3, angle, matr);
    Rot1(new_info->p4, angle, matr);
//    new_info->p1 = *(Rot1(new_info->p1, angle, matr));
//    new_info->p2 = *(Rot1(new_info->p2, angle, matr));
//    new_info->p3 = *(Rot1(new_info->p3, angle, matr));
//    new_info->p4 = *(Rot1(new_info->p4, angle, matr));
//    new_info->p1 = *(Rot(new_info->p1, angle));
//    new_info->p2 = *(Rot(new_info->p2, angle));
//    new_info->p3 = *(Rot(new_info->p3, angle));
//    new_info->p4 = *(Rot(new_info->p4, angle));

    for (int i = 0; i < new_info->cercle.count(); ++i)
    //    new_info->cercle[i] = *(Rot(new_info->cercle[i], angle));
        Rot1(new_info->cercle[i], angle, matr);

    for (int i = 0; i < new_info->astroid.count(); ++i)
        //new_info->astroid[i] = *(Rot1(new_info->astroid[i], angle, matr));
        Rot1(new_info->astroid[i], angle, matr);
    move_point*=-1;
    this->move(new_info, move_point);

    return new_info;

}

void PrintInfo::DBGPRINT()
{
    qDebug()<<"p1"<<this->p1;
    qDebug()<<"p2"<<this->p2;
    qDebug()<<"p3"<<this->p3;
    qDebug()<<"p4"<<this->p4;
}

void PrintInfo::move(PrintInfo *info, QPointF move)
{
    for (int i = 0; i < info->astroid.count(); ++i)
        info->astroid[i]+=move;
    for (int i = 0; i < info->cercle.count(); ++i)
        info->cercle[i]+=move;
    info->p1+=move;
    info->p2+=move;
    info->p3+=move;
    info->p4+=move;
}

PrintInfo::PrintInfo()
{

}

PrintInfo::PrintInfo(PrintInfo *obj)
{
    this->p1 = obj->p1;
    this->p2 = obj->p2;
    this->p3 = obj->p3;
    this->p4 = obj->p4;
    this->center = obj->center;
    this->cercle = obj->cercle;
    this->astroid = obj->astroid;
}

