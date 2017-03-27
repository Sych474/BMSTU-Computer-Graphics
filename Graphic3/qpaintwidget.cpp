#include "qpaintwidget.h"
#include "math.h"

void QPaintWidget::draw(void)
{
    QPainter painter(this);
    painter.fillRect(0, 0, this->width()-1, this->height() - 1, Qt::white);
}

bool QPaintWidget::is_point(int dx, int dy)
{
    if (dx != 0 || dy != 0) return false;

    return true;
}

time_t QPaintWidget::drawCDALine(const QPointF &pb,const QPointF &pe,const QColor &color, QPainter &painter)
{
    painter.setPen(QPen(color));

    double dx = (pe.x() - pb.x());
    double dy = (pe.y() - pb.y());
    if (this->is_point(round(dx), round(dy)))
    {
        painter.drawPoint(round(dx), round(dy));
        return 0;
    }
    int l = fmax(round(dx), round(dy));
    double x = pb.x();
    double y = pb.y();
    double delta_x = dx/l;
    double delta_y = dy/l;
    for (int i = 0; i < l+1; ++i)
    {
        painter.drawPoint(round(x), round(y));
        x += delta_x;
        y += delta_y;
    }
    return 0;
}

time_t QPaintWidget::drawBresenhamILine(const QPointF &pb, const QPointF &pe, const QColor &color, QPainter &painter)
{

}

time_t QPaintWidget::drawBresenhamALine(const QPointF &pb, const QPointF &pe, const QColor &color, QPainter &painter)
{

}

void QPaintWidget::drawLine(const line_t &line, QPainter &painter)
{
    switch (line.alg)
    {
    case alg_CDA:
        this->drawCDALine(line.pb, line.pe, line.color, painter);
        break;
    case alg_Bresenham_int:
        break;
    case alg_Bresenham_double:
        break;
    case alg_Bresenham_alias:
        break;
    case alg_Qt_std:
        painter.setPen(QPen(line.color));
        painter.drawLine(line.pb, line.pe);
        break;
    }
}

int QPaintWidget::getPixel_size() const
{
    return pixel_size;
}

void QPaintWidget::setPixel_size(int value)
{
    pixel_size = value;
}

QColor QPaintWidget::getFone_color() const
{
    return fone_color;
}

void QPaintWidget::setFone_color(const QColor &value)
{
    fone_color = value;
}

QPaintWidget::QPaintWidget(QWidget *parent) : QWidget(parent)
{

}

void QPaintWidget::paintEvent(QPaintEvent *event)
{
    int image_width = this->width()/pixel_size;
    int image_height = this->height()/pixel_size;
    QImage image(image_width, image_height, QImage::Format_RGB32);
    image.fill(QColor(fone_color));

    //DRAW
    QPainter painter;
    painter.begin(&image);
    for (int i = 0; i < lines.size(); ++i)
    {
        drawLine(lines[i], painter);
    }
    painter.setPen(QPen(line_color));
    painter.drawLine(QPointF(10, 10), QPointF(50, 50));
    drawLine({.pb=QPointF(10, 10), .pe=QPointF(20, 70), .color=Qt::red, .alg=alg_CDA}, painter);
    painter.end();


    image = image.scaled(image_width * pixel_size, image_height * pixel_size);
    painter.begin(this);
    painter.drawImage(0,0,image);
    painter.end();
}
