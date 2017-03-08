#include "qpaintwidget.h"



TreangleInfo *QPaintWidget::getInfo() const
{
    return info;
}

void QPaintWidget::setInfo(TreangleInfo *value)
{
    info = value;
}

bool QPaintWidget::getPainting_flag() const
{
    return painting_flag;
}

void QPaintWidget::setPainting_flag(bool value)
{
    painting_flag = value;
    if (!info)
        painting_flag = false;
}

int QPaintWidget::getBorder() const
{
    return border;
}

void QPaintWidget::setBorder(int value)
{
    border = value;
}

void QPaintWidget::draw()
{
    QPainter painter(this);
    painter.fillRect(0, 0, this->width()-1, this->height() - 1, Qt::white);
    if (!painting_flag)
        return;
    get_k();
    painter.setPen(QPen(Qt::black, PEN_WIDTH));
    int x1 = round(info->getP1()->x*k) + this->width()/2;
    int x2 = round(info->getP2()->x*k) + this->width()/2;
    int x3 = round(info->getP3()->x*k) + this->width()/2;

    int y1 = round(info->getP1()->y*k) + (this->height())/2;
    int y2 = round(info->getP2()->y*k)+ (this->height())/2;
    int y3 = round(info->getP3()->y*k)+ (this->height())/2;

    qDebug()<<x1<<x1;
    qDebug()<<x2<<x2;
    qDebug()<<x3<<x3;
    painter.drawLine(x1, y1, x2, y2);
    painter.drawLine(x1, y1, x3, y3);
    painter.drawLine(x3, y3, x2, y2);

    int bx_min = round(info->getLower_bisector()->x*k) + this->width()/2;
    int bx2 = round(info->getBisector2()->x*k) + this->width()/2;
    int bx3 = round(info->getBisector3()->x*k) + this->width()/2;

    int by_min = round(info->getLower_bisector()->y*k)+ (this->height())/2;
    int by2 = round(info->getBisector2()->y*k)+ (this->height())/2;
    int by3 = round(info->getBisector3()->y*k)+ (this->height())/2;

    painter.setPen(QPen(Qt::darkGreen, PEN_WIDTH));
    painter.drawLine(x2, y2, bx2, by2);
    painter.drawLine(x3, y3, bx3, by3);
    painter.setPen(QPen(Qt::darkRed, PEN_WIDTH));
    painter.drawLine(x1, y1, bx_min, by_min);

    QRect rect1 = QRect(x1 - PAINTER_TEXT_WIDTH/3, y1 - PAINTER_TEXT_HEIGHT/6, PAINTER_TEXT_WIDTH, PAINTER_TEXT_HEIGHT);
    QRect rect2 = QRect(x2 - PAINTER_TEXT_WIDTH/3, y2 - PAINTER_TEXT_HEIGHT/6, PAINTER_TEXT_WIDTH, PAINTER_TEXT_HEIGHT);
    QRect rect3 = QRect(x3 - PAINTER_TEXT_WIDTH/3, y3 - PAINTER_TEXT_HEIGHT/6, PAINTER_TEXT_WIDTH, PAINTER_TEXT_HEIGHT);
    // draw text
    painter.drawText(rect1, Qt::AlignCenter, info->getStr1());
    painter.drawText(rect2, Qt::AlignCenter, info->getStr2());
    painter.drawText(rect3, Qt::AlignCenter, info->getStr3());

    painter.setPen(QPen(Qt::darkRed, PEN_WIDTH));
    //draw points
}

void QPaintWidget::get_k()
{
    if (!info)
        return;

    double kx = (this->width()-border*2)/info->getDx();
    double ky = (this->height()-border*2)/info->getDy();
    this->k = fmin(kx, ky);

    qDebug()<<"k = "<<k;
}

void QPaintWidget::drawLine(Point *p1, Point *p2, QColor color)
{
    QPainter painter(this);
    painter.setPen(QPen(color, PEN_WIDTH));
    painter.drawLine(p1->x,p1->y,p2->x,p2->y);
}


QPaintWidget::QPaintWidget(QWidget *parent) : QWidget(parent)
{
    painting_flag = false;
    QFont font = this->font();
    font.setPointSize(PAINT_FONT_SIZE);
    this->setFont(font);


}

void QPaintWidget::paintEvent(QPaintEvent *event)
{
    draw();
}
