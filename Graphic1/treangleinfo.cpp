#include "treangleinfo.h"

double TreangleInfo::getDx() const
{
    return dx;
}


double TreangleInfo::getDy() const
{
    return dy;
}


Point *TreangleInfo::getLower_bisector() const
{
    return lower_bisector;
}

QString TreangleInfo::getStr1() const
{
    return str1;
}

QString TreangleInfo::getStr2() const
{
    return str2;
}

QString TreangleInfo::getStr3() const
{
    return str3;
}


QString *TreangleInfo::getStrCoord(Point *p)
{

}

TreangleInfo::TreangleInfo(Point *p1, Point *p2, Point *p3)
{
    changeTreangle(p1, p2, p3);
}

Point *TreangleInfo::getP1() const
{
    return p1;
}


Point *TreangleInfo::getP2() const
{
    return p2;
}

Point *TreangleInfo::getP3() const
{
    return p3;
}

QString TreangleInfo::getAnsverText()
{
    QString str = "Наименьшая биссектриса длиной: " + QString::number(get_min_bisector(p1,p2,p3));
    str += " найдена в треугольнике составленном из точек: ";
    str += "(" + getStr1() + "), ";
    str += "(" + getStr2() + "), ";
    str += "(" + getStr3() + ")";
    str += " Наименьшая биссектриса выделена красным цветом";
    return str;
}


Point *TreangleInfo::getBisector2() const
{
    return bisector2;
}


Point *TreangleInfo::getBisector3() const
{
    return bisector3;
}

void TreangleInfo::changeTreangle(Point *p1, Point *p2, Point *p3)
{
    str1 = QString::number(p1->x) +", " + QString::number(p1->y);
    str2 = QString::number(p2->x) +", " + QString::number(p2->y);
    str3 = QString::number(p3->x) +", " + QString::number(p3->y);
    double max_x = fmax(fmax(p1->x, p2->x), p3->x);
    double min_x = fmin(fmin(p1->x, p2->x), p3->x);

    double max_y = fmax(fmax(p1->y, p2->y), p3->y);
    double min_y = fmin(fmin(p1->y, p2->y), p3->y);

    dx = max_x - min_x;
    dy = max_y - min_y;
    double x0 = dx/2 + min_x;
    double y0 = dy/2 + min_y;

    movePoint(p1, -x0, -y0);
    movePoint(p2, -x0, -y0);
    movePoint(p3, -x0, -y0);

    //инвертируем по y
    p1->y =  - p1->y;
    p2->y =  - p2->y;
    p3->y =  - p3->y;

    double a = get_len(p1, p2);
    double b = get_len(p1, p3);
    double c = get_len(p2, p3);
    double len1 = get_bisector(a, b, c); //биссектриса из p1
    double len2 = get_bisector(a, c, b); //биссектриса из p2
    double len3 = get_bisector(b, c, a); //биссектриса из p3
    double min = fmin(fmin(len1, len2), len3);
    if (min==len1)
    {
        this->p1 = p1;
        this->p2 = p2;
        this->p3 = p3;
    }
    if (min==len2)
    {
        this->p1 = p2;
        this->p2 = p3;
        this->p3 = p1;

        QString tmp1 = this->str1;
        this->str1 = str2;
        this->str2 = str3;
        this->str3 = tmp1;
    }
    if (min==len3)
    {
        this->p1 = p3;
        this->p2 = p1;
        this->p3 = p2;
        QString tmp1 = this->str1;
        this->str1 = str3;
        this->str3 = str2;
        this->str2 = tmp1;
    }
    this->lower_bisector = get_bisector_end(this->p1, this->p2,this->p3);
    this->bisector2 = get_bisector_end(this->p2, this->p1,this->p3);
    this->bisector3 = get_bisector_end(this->p3, this->p2,this->p1);
}
