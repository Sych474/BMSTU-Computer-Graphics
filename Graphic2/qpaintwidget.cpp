#include "qpaintwidget.h"


bool QPaintWidget::getPainting_flag() const
{
    return painting_flag;
}

void QPaintWidget::setPainting_flag(bool value)
{
    painting_flag = value;
}

int QPaintWidget::getBorder() const
{
    return border;
}

void QPaintWidget::setBorder(int value)
{
    border = value;
}

void QPaintWidget::draw(PrintInfo *info)
{
    QPainter painter(this);
    painter.fillRect(0, 0, this->width()-1, this->height() - 1, Qt::white);
    painter.setPen(QPen(Qt::darkGreen, PEN_WIDTH));
    //qDebug()<<this->width();
    //qDebug()<<this->height();
    if (!painting_flag)
        return;
    if (!current_info)
        return;

//    for (int i = 1; i < info->astroid.count(); i++)
//        painter.drawLine(info->astroid[i].toPoint(), info->astroid[i-1].toPoint());
//    painter.drawLine(info->astroid[0].toPoint(), info->astroid[info->astroid.count()-1].toPoint());
    painter.drawPolygon(info->astroid.toPolygon());
    //for (int i = 1; i < info->cercle.count(); i++)
    //    painter.drawLine(info->cercle[i].toPoint(), info->cercle[i-1].toPoint());
    //painter.drawLine(info->cercle[0].toPoint(), info->cercle[info->cercle.count()-1].toPoint());
    painter.drawPolygon(info->cercle.toPolygon());
    painter.drawLine(info->p1.toPoint(), info->p2.toPoint());
    painter.drawLine(info->p2.toPoint(), info->p3.toPoint());
    painter.drawLine(info->p3.toPoint(), info->p4.toPoint());

    painter.setPen(QPen(Qt::black, OX_PEN_WIDTH));
    QPoint Ox = info->center.toPoint()+QPoint(O_DX, 0);
    QPoint Oy = info->center.toPoint()+QPoint(0, O_DX);

    painter.drawLine(info->center.toPoint(), Ox);
    painter.drawLine(Ox, Ox+QPoint(-O_STR_DX, -O_STR_DY));
    painter.drawLine(Ox, Ox+QPoint(-O_STR_DX, O_STR_DY));
    painter.drawLine(info->center.toPoint(), Oy);
    painter.drawLine(Oy, Oy+QPoint(-O_STR_DY, -O_STR_DX));
    painter.drawLine(Oy, Oy+QPoint(O_STR_DY, -O_STR_DX));
    Ox -= QPoint(200/2, -5);
    Oy -= QPoint(-5, 200/2);
    painter.drawLine(Ox, Ox+QPoint(0, -10));
    painter.drawLine(Oy, Oy+QPoint(-10, 0));
    painter.drawText(QRectF(Ox.x(), Ox.y(), 100, 50),"100");
    painter.drawText(QRectF(Oy.x(), Oy.y(), 100, 50),"100");


}


PrintInfo *QPaintWidget::getCurrent_info() const
{
    return current_info;
}

void QPaintWidget::setCurrent_info(PrintInfo *value)
{
    current_info = value;
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
    draw(current_info);
}
