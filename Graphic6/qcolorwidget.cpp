#include "qcolorwidget.h"
#include <qcolordialog.h>

QColorWidget::QColorWidget(QWidget *parent) : QWidget(parent)
{
    this->color = QColor(Qt::white);
    this->setMinimumSize(50, 20);
}

QColor QColorWidget::getColor()
{
    return this->color;
}

void QColorWidget::setColor(const QColor &color)
{
    this->color = color;
}

void QColorWidget::setWidth(int width)
{
    this->setMinimumWidth(width);
    this->setMaximumWidth(width);
}

void QColorWidget::setHeight(int height)
{
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);
}

void QColorWidget::mousePressEvent(QMouseEvent *)
{
    QColor color = QColorDialog::getColor(this->color);
    if (color.isValid())
    {
        this->color = color;
        emit colorChanged(color);
    }
}

void QColorWidget::paintEvent(QPaintEvent *)
{
    int w = this->width();
    int h = this->height();
    QPainter paint(this);

    // draw
    paint.setPen(QColor(Qt::black));
    paint.setBrush(QBrush(this->color, Qt::SolidPattern));
    paint.drawRect(0, 0, w - 1, h - 1);
}

QPaintEngine *QColorWidget::paintEngine() const
{
    return nullptr;
}
