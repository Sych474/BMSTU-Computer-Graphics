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

time_t QPaintWidget::drawCDALine(const QPoint &pb,const QPoint &pe,const QColor &color, QPainter &painter)
{
    painter.setPen(QPen(color));

    int dx = (pe.x() - pb.x());
    int dy = (pe.y() - pb.y());
    if (this->is_point(dx, dy))
    {
        painter.drawPoint(pb);
        return 0;
    }
    int l = fmax(abs(dx), abs(dy));
    double x = pb.x();
    double y = pb.y();
    double delta_x = dx/(double)l;
    double delta_y = dy/(double)l;
    for (int i = 0; i < l+1; ++i)
    {
        painter.drawPoint(QPointF(x, y));
        x += delta_x;
        y += delta_y;
    }
    return 0;
}

int sign(double num)
{
    if (fabs(num) < EPS)
        return 0;
    if (num > 0)
        return 1;
    else
        return -1;
}

template <typename T>
void my_swap(T &x, T &y)
{
    T tmp = x;
    x = y;
    y = tmp;
}

time_t QPaintWidget::drawBresenhamDLine(const QPoint &pb, const QPoint &pe, const QColor &color, QPainter &painter)
{
    painter.setPen(QPen(color));
    int dx = (pe.x() - pb.x());
    int dy = (pe.y() - pb.y());
    if (this->is_point(dx, dy))
    {
        painter.drawPoint(pb);
        return 0;
    }
    int sx = sign(dx);
    int sy = sign(dy);
    dx = abs(dx);
    dy = abs(dy);
    bool flag = false;
    if (dx < dy)
    {
        flag = true;
        my_swap(dx, dy);
    }
    double m = dy/(double)dx;
    double e = m - 1/2;
    double x = pb.x();
    double y = pb.y();

    for (int i = 0; i < dx+1; ++i)
    {
        if (i == dx)
        {
            qDebug()<< "draw" << QPoint(round(x), round(y)) << "end" << pe;
            if ((x) == pe.x() && (y) == pe.y()) qDebug() << "GREAT";
            else
            {
                painter.save();
                painter.setPen(Qt::red);
                painter.drawEllipse(QPoint(round(x), round(y)), 2, 2);
                painter.restore();
            }
        }
        painter.drawPoint(QPoint(round(x), round(y)));
        if (fabs(e) > EPS && e > 0)
        {
            if (flag)
                x += sx;
            else
                y += sy;
            e -= 1;
        }
        if (flag)
            y += sy;
        else
            x += sx;
        e += m;
    }
    return 0;
}

time_t QPaintWidget::drawBresenhamILine(const QPoint &pb, const QPoint &pe, const QColor &color, QPainter &painter)
{
    painter.setPen(QPen(color));
    int dx = (pe.x() - pb.x());
    int dy = (pe.y() - pb.y());
    if (this->is_point(dx, dy))
    {
        painter.drawPoint(pb);
        return 0;
    }
    int sx = sign(dx);
    int sy = sign(dy);
    dx = abs(dx);
    dy = abs(dy);
    bool flag = false;
    if (dx < dy)
    {
        flag = true;
        my_swap(dx, dy);
    }
    int e = 2 * dy - dx;
    int x = pb.x();
    int y = pb.y();

    for (int i = 0; i < dx+1; ++i)
    {
        if (i == dx)
        {
            qDebug()<< "draw" << QPoint(round(x), round(y)) << "end" << pe;
            if ((x) == pe.x() && (y) == pe.y()) qDebug() << "GREAT";
            else
            {
                painter.save();
                painter.setPen(Qt::red);
                painter.drawEllipse(QPoint(round(x), round(y)), 2, 2);
                painter.restore();
            }
        }
        painter.drawPoint(QPoint(x, y));
        if (e >= 0)
        {
            if (flag)
                x += sx;
            else
                y += sy;
            e -= dx;
        }
        if (flag)
            y += sy;
        else
            x += sx;
        e += dy;
    }
    return 0;
}

time_t QPaintWidget::drawBresenhamALine(const QPoint &pb, const QPoint &pe, const QColor &color, QPainter &painter)
{
    painter.setPen(QPen(color));
    int dx = (pe.x() - pb.x());
    int dy = (pe.y() - pb.y());
    if (this->is_point(dx, dy))
    {
        painter.drawPoint(pb);
        return 0;
    }
    int sx = sign(dx);
    int sy = sign(dy);
    dx = abs(dx);
    dy = abs(dy);
    bool flag = false;
    if (dx < dy)
    {
        flag = true;
        my_swap(dx, dy);
    }
    double m = dy/(double)dx;
    double I = 255;
    double e = I/2;
    double x = pb.x();
    double y = pb.y();
    m = m * I;
    double w = I - m;
    for (int i = 0; i < dx+1; ++i)
    {
        if (i == dx)
        {
            qDebug()<< "draw" << QPoint(round(x), round(y)) << "end" << pe;
            if ((x) == pe.x() && (y) == pe.y()) qDebug() << "GREAT";
            else
            {
                painter.save();
                painter.setPen(Qt::red);
                painter.drawEllipse(QPoint(round(x), round(y)), 2, 2);
                painter.restore();
            }
        }
        QColor c = color;
        c.setAlpha(e);
        painter.setPen(QPen(c));
        painter.drawPoint(QPoint(round(x), round(y)));
        if (fabs(e  - w) > EPS && e > w)
        {
            if (flag)
                x += sx;
            else
                y += sy;
            e -= w;
        }
        else
            e += m;
        if (flag)
            y += sy;
        else
            x += sx;
    }
    return 0;
}

void QPaintWidget::drawLine(const line_t &line, QPainter &painter)
{
    switch (line.alg)
    {
    case alg_DDA:
        this->drawCDALine(line.pb, line.pe, line.color, painter);
        break;
    case alg_Bresenham_int:
        this->drawBresenhamILine(line.pb, line.pe, line.color, painter);
        break;
    case alg_Bresenham_double:
        this->drawBresenhamDLine(line.pb, line.pe, line.color, painter);
        break;
    case alg_Bresenham_alias:
        this->drawBresenhamALine(line.pb, line.pe, line.color, painter);
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
    double len = fmin(x_c-BORDER, y_c-BORDER);
    double x = x_c + len;
    double y = y_c;
    double angle = 0;
    while (fabs(angle) < 360)
    {
        x = round(x_c + len * cos(angle/180 * M_PI));
        y = round(y_c + len * sin(angle/180 * M_PI));
        line_t line = {.pb=QPoint(x_c, y_c), .pe=QPoint(x, y), .color=solar.color, .alg=solar.alg};
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

void QPaintWidget::clear()
{
    lines.clear();
    solars.clear();
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
