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
        painter.drawPoint(pb);
        return 0;
    }
    double l = fmax(fabs(dx), fabs(dy));
    double x = pb.x();
    double y = pb.y();
    double delta_x = dx/l;
    double delta_y = dy/l;
    for (int i = 0; (l+1 - i) > EPS; ++i)
    {
        painter.drawPoint(QPointF(x, y));
        x += delta_x;
        y += delta_y;
    }
    return 0;
}

time_t QPaintWidget::drawBresenhamDLine(const QPointF &pb, const QPointF &pe, const QColor &color, QPainter &painter)
{
    painter.setPen(QPen(color));
    double delta_x = (pe.x() - pb.x());
    double delta_y = (pe.y() - pb.y());
    if (this->is_point(round(delta_x), round(delta_y)))
    {
        painter.drawPoint(round(delta_x), round(delta_y));
        return 0;
    }
    //int dx = sign(delta_x);
    //int dy = sign(delta_y);
    double x = pb.x();
    double y = pb.y();

    /*if (dx > dy)
    {

    }
    else
    {

    }
    */
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

void QPaintWidget::drawSolar(const solar_t &solar, QPainter &painter)
{
    double x_c = this->width()/2/pixel_size;
    double y_c = this->height()/2/pixel_size;
    double len = fmin(x_c-4, y_c-4);
    double x = x_c + len;
    double y = y_c;
    double angle = 0;
    int i = 1;
    while (abs(angle - 360) > EPS)
    {
        x = x_c + len * cos(angle/180 * M_PI);
        y = y_c + len * sin(angle/180 * M_PI);
        line_t line = {.pb=QPointF(x_c, y_c), .pe=QPointF(x, y), .color=solar.color, .alg=solar.alg};
        drawLine(line,painter);
        angle += solar.teta;
    }
}

void QPaintWidget::addLine(line_t &line)
{
    lines.push_back(line);
}

void QPaintWidget::addSolar(solar_t &solar)
{
    solars.push_back(solar);
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
    solars.push_back({.color=Qt::black, .alg=alg_CDA, .teta=20});
    //solars.push_back({.color=Qt::green, .alg=alg_Qt_std, .teta=20});

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
    for (int i = 0; i < solars.size(); ++i)
    {
        drawSolar(solars[i], painter);
    }
    painter.end();

    image = image.scaled(image_width * pixel_size, image_height * pixel_size);
    painter.begin(this);
    painter.drawImage(0,0,image);
    painter.end();
}
