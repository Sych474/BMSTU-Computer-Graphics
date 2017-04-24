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
    start_p = P;
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

QPoint QPaintWidget::getFill_point() const
{
    return fill_point;
}

void QPaintWidget::setFill_point(const QPoint &value)
{
    need_fill_point = true;
    fill_point = value;
    paint();
}

void QPaintWidget::drawEdge(QPainter &painter, const edge_t &edge)
{
    drawBresenhamLine(edge.p1, edge.p2, edge.color, painter);
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
    if (!need_point) return;

    QPainter painter;
    painter.begin(&image);

    painter.setPen(face_color);
    painter.drawPoint(start_p);

    painter.end();
}

void QPaintWidget::drawFillPoint(QImage &image)
{
    if (!need_fill_point) return;

    QPainter painter;
    painter.begin(&image);

    painter.setPen(fill_color);
    painter.drawPoint(fill_point);

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

void QPaintWidget::_fillPoligon(QPainter &painter, QImage &image, QPoint &start_p)
{
    painter.setPen(fill_color);
    QStack<QPoint> stack;
    stack.push(start_p);

    while (!stack.isEmpty())
    {
        QPoint curr = stack.pop();
        int x_p = curr.x();
        int y_p = curr.y();
        painter.drawPoint(curr);
        int x = x_p - 1;
        while (image.pixelColor(x, y_p) != face_color)
        {
            painter.drawPoint(x, y_p);
            --x;
        }
        int x_left = x + 1;
        x = x_p + 1;
        while (image.pixelColor(x, y_p) != face_color)
        {
            painter.drawPoint(x, y_p);
            ++x;
        }
        int x_right = x - 1;

        bool flag = false;
        QColor tmp_color;
        for (x = x_left; x <= x_right; ++x)
        {
            tmp_color = image.pixelColor(x, y_p + 1);
            if(tmp_color != face_color && tmp_color != fill_color)
            {
                flag = true;
            }
            else
            {
                if (flag)
                {
                    stack.push(QPoint(x - 1, y_p + 1));
                }
                flag = false;
            }
        }
        if (flag)
        {
            stack.push(QPoint(x_right, y_p + 1));
        }
        flag = false;
        for (x = x_left; x <= x_right; ++x)
        {
            tmp_color = image.pixelColor(x, y_p - 1);
            if(tmp_color != face_color && tmp_color != fill_color)
            {
                flag = true;
            }
            else
            {
                if (flag)
                {
                    stack.push(QPoint(x - 1, y_p - 1));
                }
                flag = false;
            }
        }
        if (flag)
        {
            stack.push(QPoint(x_right, y_p - 1));
        }
    }
    repaint();
}

void QPaintWidget::_fillStepPoligon(QPainter &painter, QImage &image, QPoint &start_p)
{
    painter.setPen(fill_color);
    QStack<QPoint> stack;
    stack.push(start_p);

    while (!stack.isEmpty())
    {
        QPoint curr = stack.pop();
        int x_p = curr.x();
        int y_p = curr.y();
        painter.drawPoint(curr);
        int x = x_p - 1;
        while (image.pixelColor(x, y_p) != face_color)
        {
            painter.drawPoint(x, y_p);
            --x;
        }
        int x_left = x + 1;
        x = x_p + 1;
        while (image.pixelColor(x, y_p) != face_color)
        {
            painter.drawPoint(x, y_p);
            ++x;
        }
        int x_right = x - 1;

        bool flag = false;
        QColor tmp_color;
        for (x = x_left; x <= x_right; ++x)
        {
            tmp_color = image.pixelColor(x, y_p + 1);
            if(tmp_color != face_color && tmp_color != fill_color)
            {
                flag = true;
            }
            else
            {
                if (flag)
                {
                    stack.push(QPoint(x - 1, y_p + 1));
                }
                flag = false;
            }
        }
        if (flag)
        {
            stack.push(QPoint(x_right, y_p + 1));
        }
        repaint();
        flag = false;
        for (x = x_left; x <= x_right; ++x)
        {
            tmp_color = image.pixelColor(x, y_p - 1);
            if(tmp_color != face_color && tmp_color != fill_color)
            {
                flag = true;
            }
            else
            {
                if (flag)
                {
                    stack.push(QPoint(x - 1, y_p - 1));
                }
                flag = false;
            }
        }
        if (flag)
        {
            stack.push(QPoint(x_right, y_p - 1));
        }
        repaint();
    }
}

QPaintWidget::QPaintWidget(QWidget *parent) : QWidget(parent)
{
    im = QImage(0, 0, QImage::Format_RGB32);
    im.fill(QColor(fone_color));
}

void QPaintWidget::paint()
{
    im.fill(QColor(fone_color));

    this->drawPoint(im);
    this->drawPoligon(im);
    this->drawFillPoint(im);

    this->repaint();
}

void QPaintWidget::fillPoligon()
{
    state = fill_standard;
    paint();
    QPainter painter;
    painter.begin(&im);
    _fillPoligon(painter, im, fill_point);
    painter.end();
    drawPoligon(im);
}

void QPaintWidget::stepFillPioligon()
{
    state = fill_standard;
    paint();
    QPainter painter;
    painter.begin(&im);
    _fillStepPoligon(painter, im, fill_point);
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

void QPaintWidget::resizeEvent(QResizeEvent *event)
{
    int image_width = this->width();
    int image_height = this->height();
    im = QImage(image_width, image_height, QImage::Format_RGB32);
    paint();
}
