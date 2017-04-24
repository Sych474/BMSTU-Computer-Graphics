#include "qpaintwidget.h"
#include "math.h"
#include <windows.h>

QColor QPaintWidget::getFill_color() const
{
    return fill_color;
}

void QPaintWidget::setFill_color(const QColor &value)
{
    fill_color = value;
    paint();
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
    paint();
}

void QPaintWidget::clear()
{
    edges.clear();
    need_point =false;
    paint();
}

QColor QPaintWidget::getFace_color() const
{
    return face_color;
}

void QPaintWidget::setFace_color(const QColor &value)
{
    face_color = value;
    for (int i = 0; i < edges.length(); ++i)
    {
        edges[i].color = face_color;
    }
    paint();
}

void QPaintWidget::add_point(const QPoint &P)
{
    need_point = true;
    p = P;
    paint();
}

void QPaintWidget::add_edge(edge_t edge)
{
    need_point = false;
    if (edge.p1.y() > edge.p2.y())
    {
        QPoint tmp = edge.p2;
        edge.p2 = edge.p1;
        edge.p1 = tmp;
    }
    edges.append(edge);
    paint();
}

void QPaintWidget::end_poligon()
{
    for (int i = 0; i < new_edges.length(); ++i)
    {
        edges.append(new_edges[i]);
    }
    new_edges.clear();
    paint();
}

int QPaintWidget::getSeparator_x() const
{
    return separator_x;
}

void QPaintWidget::setSeparator_x(int value)
{
    separator_x = value;
    paint();
}

state_t QPaintWidget::getState() const
{
    return state;
}

void QPaintWidget::setState(const state_t &value)
{
    state = value;
}

QColor QPaintWidget::getSep_color() const
{
    return sep_color;
}

void QPaintWidget::setSep_color(const QColor &value)
{
    sep_color = value;
    paint();
}

void QPaintWidget::drawEdge(QPainter &painter, const edge_t &edge)
{
    drawBresenhamLine(edge.p1, edge.p2, edge.color, painter);
    //painter.setPen(QPen(face_color));
    //painter.drawLine(edge.p1/pixel_size, edge.p2/pixel_size);
}

void QPaintWidget::drawPoligon(QImage &image)
{
    QPainter painter;
    painter.begin(&image);

    for (int i = 0; i < edges.length(); ++i)
    {
        drawEdge(painter, edges[i]);
    }

    painter.end();
}

void QPaintWidget::drawPoint(QImage &image)
{
    if (need_point)
    {
        QPainter painter;
        painter.begin(&image);

        painter.setPen(face_color);
        painter.drawPoint(p);

        painter.end();
    }
}

void QPaintWidget::drawSeparator(QImage &image)
{
    QPainter painter;
    painter.begin(&image);

    painter.setPen(sep_color);
    painter.drawLine(separator_x, 0, separator_x, 800);

    painter.end();
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

void QPaintWidget::drawBresenhamLine(const QPoint &pb, const QPoint &pe, const QColor &color, QPainter &painter)
{
    painter.setPen(QPen(color));
    int dx = (pe.x() - pb.x());
    int dy = (pe.y() - pb.y());
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

    for (int i = 0; i < dx; ++i)
    {
        painter.drawPoint(QPoint(x, y));
        if (e >= 0)
        {
            if (flag)
                x += sx;
            else
                y += sy;
            e -= 2 * dx;
        }
        if (flag)
            y += sy;
        else
            x += sx;
        e += 2 * dy;
    }
    painter.drawPoint(QPoint(x, y));
}

void QPaintWidget::paint_point(int x, int y, QPainter &painter, QImage &image)
{
    QColor curr_color = image.pixelColor(x, y);
    if (curr_color == fill_color)
    {
        painter.setPen(fone_color);
    }
    else
    {
        painter.setPen(fill_color);
    }
    painter.drawPoint(x, y);
}

void QPaintWidget::_fillPoligon(QPainter &painter, QImage &image)
{
    for (int i = 0; i < edges.length(); ++i)
    {
        int x1 = edges[i].p1.x()/pixel_size;
        int x2 = edges[i].p2.x()/pixel_size;
        int y1 = edges[i].p1.y()/pixel_size;
        int y2 = edges[i].p2.y()/pixel_size;
        int dy = y2 - y1;
        int dx = x2 - x1;
        int x_separator = separator_x/pixel_size;

        if (dy == 0) drawEdge(painter, edges[i]);

        double k = ((double) dx)/ dy;
        bool f1 = x1 < x_separator;
        bool f2 = x2 < x_separator;

        if (f1 && f2)
        {
            for (int y = y1; y < y2; ++y)
            {
                int x_start = round(k * (y - y1)) + x1;
                for (int x = x_start; x < x_separator; ++x)
                {
                    paint_point(x, y, painter, image);
                }
            }
        }
        else if (!f1 && !f2)
        {
            for (int y = y1; y < y2; ++y)
            {
                int x_start = round(k * (y - y1)) + x1;
                for (int x = x_start; x > x_separator; --x)
                {
                    paint_point(x, y, painter, image);
                }
            }
        }
        else if (f1 && !f2)
        {
            int y_sep = round(1/k * (x_separator - x1)) + y1;
            for (int y = y1; y < y_sep; ++y)
            {
                int x_start = round(k * (y - y1)) + x1;
                for (int x = x_start; x < x_separator; ++x)
                {
                    paint_point(x, y, painter, image);
                }
            }
            for (int y = y_sep; y < y2; ++y)
            {
                int x_start = round(k * (y - y1)) + x1;
                for (int x = x_start; x > x_separator; --x)
                {
                    paint_point(x, y, painter, image);
                }
            }
        }
        else
        {
            int y_sep = round(1/k * (x_separator - x1)) + y1;
            for (int y = y1; y < y_sep; ++y)
            {
                int x_start = round(k * (y - y1)) + x1;
                for (int x = x_start; x > x_separator; --x)
                {
                    paint_point(x, y, painter, image);
                }
            }
            for (int y = y_sep; y < y2; ++y)
            {
                int x_start = round(k * (y - y1)) + x1;
                for (int x = x_start; x < x_separator; ++x)
                {
                    paint_point(x, y, painter, image);
                }
            }
        }
    }
}

void QPaintWidget::_fillStepPoligon(QPainter &painter, QImage &image)
{
    for (int i = 0; i < edges.length(); ++i)
    {
        int x1 = edges[i].p1.x()/pixel_size;
        int x2 = edges[i].p2.x()/pixel_size;
        int y1 = edges[i].p1.y()/pixel_size;
        int y2 = edges[i].p2.y()/pixel_size;
        int dy = y2 - y1;
        int dx = x2 - x1;
        int x_separator = separator_x/pixel_size;

        if (dy == 0) drawEdge(painter, edges[i]);

        double k = ((double) dx)/ dy;
        bool f1 = x1 < x_separator;
        bool f2 = x2 < x_separator;

        if (f1 && f2)
        {
            for (int y = y1; y < y2; ++y)
            {
                int x_start = k * (y - y1) + x1;
                for (int x = x_start; x < x_separator; ++x)
                {
                    paint_point(x, y, painter, image);
                }
                Sleep(SLEEP_TIME);
                repaint();
            }
        }
        else if (!f1 && !f2)
        {
            for (int y = y1; y < y2; ++y)
            {
                int x_start = k * (y - y1) + x1;
                for (int x = x_start; x > x_separator; --x)
                {
                    paint_point(x, y, painter, image);
                }
                Sleep(SLEEP_TIME);
                repaint();
            }
        }
        else if (f1 && !f2)
        {
            int y_sep = 1/k * (x_separator - x1) + y1;
            for (int y = y1; y < y_sep; ++y)
            {
                int x_start = k * (y - y1) + x1;
                for (int x = x_start; x < x_separator; ++x)
                {
                    paint_point(x, y, painter, image);
                }
                Sleep(SLEEP_TIME);
                repaint();
            }
            for (int y = y_sep; y < y2; ++y)
            {
                int x_start = k * (y - y1) + x1;
                for (int x = x_start; x > x_separator; --x)
                {
                    paint_point(x, y, painter, image);
                }
                Sleep(SLEEP_TIME);
                repaint();
            }
        }
        else
        {
            int y_sep = 1/k * (x_separator - x1) + y1;
            for (int y = y1; y < y_sep; ++y)
            {
                int x_start = k * (y - y1) + x1;
                for (int x = x_start; x > x_separator; --x)
                {
                    paint_point(x, y, painter, image);
                }
                Sleep(SLEEP_TIME);
                repaint();
            }
            for (int y = y_sep; y < y2; ++y)
            {
                int x_start = k * (y - y1) + x1;
                for (int x = x_start; x < x_separator; ++x)
                {
                    paint_point(x, y, painter, image);
                }
                Sleep(SLEEP_TIME);
                repaint();
            }
        }
    }
}

QPaintWidget::QPaintWidget(QWidget *parent) : QWidget(parent)
{
    int image_width = this->width()/pixel_size;
    int image_height = this->height()/pixel_size;
    qDebug() << image_width << image_height;
    image_height = 800;
    image_width = 1366;
    im = QImage(image_width, image_height, QImage::Format_RGB32);
    im.fill(QColor(fone_color));
}

void QPaintWidget::paint()
{
    int image_width = this->width()/pixel_size;
    int image_height = this->height()/pixel_size;
    //Debug() << image_width << image_height;
    //im = QImage(image_width, image_height, QImage::Format_RGB32);
    im.fill(QColor(fone_color));

    this->drawPoint(im);
    this->drawPoligon(im);
    this->drawSeparator(im);

    //im = im.scaled(image_width * pixel_size, image_height * pixel_size);

    this->repaint();
}

void QPaintWidget::fillPoligon()
{
    state = fill_standard;
    paint();
    QPainter painter;
    painter.begin(&im);
    _fillPoligon(painter, im);
    painter.end();
    drawPoligon(im);
    this->repaint();
}

void QPaintWidget::stepFillPioligon()
{
    state = fill_standard;
    paint();
    QPainter painter;
    painter.begin(&im);
    _fillStepPoligon(painter, im);
    painter.end();
    drawPoligon(im);
}

void QPaintWidget::paintEvent(QPaintEvent *event)
{
    /*
    int image_width = this->width()/pixel_size;
    int image_height = this->height()/pixel_size;
    QImage image(image_width, image_height, QImage::Format_RGB32);
    image.fill(QColor(fone_color));

    //DRAW
    QPainter painter;
    painter.begin(&image);

    this->drawPoligon(painter);

    painter.setPen(QPen(Qt::red));
    painter.drawLine(separator_x, 0, separator_x, this->height());

    if (state == fill_standard)
    {
        _fillPoligon(painter, image);
    }
    if (state == fill_step)
    {
        _fillStepPoligon(painter, image);
    }

    this->drawPoligon(painter);

    painter.drawPoint(p/pixel_size);
    painter.end();

    image = image.scaled(image_width * pixel_size, image_height * pixel_size);
    painter.begin(this);
    painter.drawImage(0,0,image);
    state = fill_no;
    painter.end();
    */
    QPainter painter;
    painter.begin(this);
    painter.drawImage(0,0,im);
    painter.end();
    state = fill_no;
}
