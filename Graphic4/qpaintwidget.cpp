#include "qpaintwidget.h"
#include "math.h"

void QPaintWidget::draw_4_pixels(int x_c, int y_c, int x, int y, QPainter &painter)
{
    painter.drawPoint(x_c+x, y_c+y);
    painter.drawPoint(x_c-x, y_c+y);
    painter.drawPoint(x_c-x, y_c-y);
    painter.drawPoint(x_c+x, y_c-y);
}

time_t QPaintWidget::drawCanonEllipse(const ellipse_t &ellipse, QPainter &painter)
{
    painter.setPen(QPen(ellipse.color));
    int x_c = ellipse.pc.x();
    int y_c = ellipse.pc.y();
    int a2 = ellipse.a * ellipse.a;
    int b2 = ellipse.b * ellipse.b;
    double c1 = (((double) ellipse.b)/((double) ellipse.a));
    double c2 = (((double) ellipse.a)/((double) ellipse.b));

    int x, y;

    int x_max = round( ((double)a2)/sqrt(a2+b2));
    for (x = 0; x <= x_max; ++x)
    {
        y = round(c1 * sqrt(a2 - x*x));
        draw_4_pixels(x_c, y_c, x, y, painter);
    }
    for(y = round(c1 * sqrt(a2 - x_max*x_max)); y >= 0; --y)
    {
        x = round(c2 * sqrt(b2 - y*y));
        draw_4_pixels(x_c, y_c, x, y, painter);
    }

    return 0;
}

time_t QPaintWidget::drawCanonCircle(const ellipse_t &circle, QPainter &painter)
{
    painter.setPen(QPen(circle.color));
    int x_c = circle.pc.x();
    int y_c = circle.pc.y();
    int x, y;
    int r2 = circle.a*circle.a;
    int x_max = round(((double) circle.a)/sqrt(2));
    for (x = 0; x <= x_max; x+= 1)
    {
        y = round(sqrt(r2 - x*x));
        draw_4_pixels(x_c, y_c, x, y, painter);
    }
    for(y = round(sqrt(r2 - x_max*x_max)); y >= 0; y -= 1)
    {
        x = round(sqrt(r2 - y*y));
        draw_4_pixels(x_c, y_c, x, y, painter);
    }
    return 0;
}

time_t QPaintWidget::drawParamEllipse(const ellipse_t &ellipse, QPainter &painter)
{
    painter.setPen(QPen(ellipse.color));
    int x_c = ellipse.pc.x();
    int y_c = ellipse.pc.y();
    int x, y;
    double alpfa = M_PI_2;
    double dx = 1.0/ (double) ellipse.a;
    double dy = 1.0/ (double) ellipse.b;
    double a2 = ellipse.a * ellipse.a;
    double b2 = ellipse.b * ellipse.b;\
    double x_max = a2/sqrt(a2+b2);
    double y_max = round((double) ellipse.b/ (double) ellipse.a * sqrt(a2 - x*x));

    double t_x_max = acos(x_max/sqrt(a2+b2)) + ALG_EPS;

    for (; alpfa >= t_x_max; alpfa -= dx)
    {
        x = round(ellipse.a * cos(alpfa));
        y = round(ellipse.b * sin(alpfa));
        draw_4_pixels(x_c, y_c, x, y, painter);
    }

    for (alpfa = t_x_max; alpfa >= -ALG_EPS ; alpfa -= dy)
    {
        x = round(ellipse.a * cos(alpfa));
        y = round(ellipse.b * sin(alpfa));
        draw_4_pixels(x_c, y_c, x, y, painter);
    }

    return 0;
}

time_t QPaintWidget::drawParamCircle(const ellipse_t &circle, QPainter &painter)
{
    painter.setPen(QPen(circle.color));
    int x_c = circle.pc.x();
    int y_c = circle.pc.y();
    int x, y;
    double dt = 1.0 / circle.a;
    double max = M_PI_2 + ALG_EPS;
    for (double alpfa = 0; alpfa <= max; alpfa += dt)
    {
        x = round(circle.a * cos(alpfa));
        y = round(circle.b * sin(alpfa));
        draw_4_pixels(x_c, y_c, x, y, painter);
    }
    return 0;
}

time_t QPaintWidget::drawBresenhamEllipse(const ellipse_t &ellipse, QPainter &painter)
{
    painter.setPen(QPen(ellipse.color));
    int x_c = ellipse.pc.x();
    int y_c = ellipse.pc.y();

    int a2 = ellipse.a * ellipse.a;
    int b2 = ellipse.b * ellipse.b;
    int a22 = 2 * a2;
    int b22 = 2 * b2;

    int x = 0, y = ellipse.b;

    long long int err = a2 + b2 - a22 * y;
    long long int err1, err2;
    while (y >= 0)
    {
        draw_4_pixels(x_c, y_c, x, y, painter);
        if (err < 0)
        {
            err1 = 2 * err + a22 * y - a2;
            if (err1 < 0)
            {
                ++x;
                err += b22*x + b2;
            }
            else
            {
                --y;
                ++x;
                err += b22*x + b2 + a2 - a22*y;
            }
        }
        else if (err > 0)
        {
            err2 = 2 * err - b22 * x - b2;
            if (err2 <= 0)
            {
                --y;
                ++x;
                err += b22*x + b2 + a2 - a22*y;
            }
            else
            {
                --y;
                err += a2 - a22*y;
            }
        }
        else
        {
            --y;
            ++x;
            err += b22*x + b2 + a2 - a22*y;
        }
    }

    return 0;
}

time_t QPaintWidget::drawBresenhamCircle(const ellipse_t &circle, QPainter &painter)
{
    painter.setPen(QPen(circle.color));
    int x_c = circle.pc.x();
    int y_c = circle.pc.y();
    int x = 0, y = circle.a;

    int err = 2 * (1 - circle.a);
    int err1, err2;
    while (y >= 0)
    {
        draw_4_pixels(x_c, y_c, x, y, painter);
        if (err < 0)
        {
            err1 = 2 * err + 2 * y - 1;
            if (err1 <= 0)
            {
                x++;
                err += 2*x + 1;
            }
            else
            {
                x++;
                y--;
                err += 2 * (x - y + 1);
            }
        }
        else if (err > 0)
        {
            err2 = 2 * err - 2 * x - 1;
            if (err2 <= 0)
            {
                x++;
                y--;
                err += 2 * (x - y + 1);
            }
            else
            {
                y--;
                err += -2*y + 1;
            }
        }
        else
        {
            x++;
            y--;
            err += 2 * (x - y + 1);
        }
    }

    return 0;
}

time_t QPaintWidget::drawMidPointEllipse(const ellipse_t &ellipse, QPainter &painter)
{
    painter.setPen(QPen(ellipse.color));
    int x_c = ellipse.pc.x();
    int y_c = ellipse.pc.y();
    int a2 = ellipse.a * ellipse.a;
    int b2 = ellipse.b * ellipse.b;\
    int a22 = 2 * a2;
    int b22 = 2 * b2;
    int x_max = a2/sqrt(a2+b2);

    int x = 0, y = ellipse.b;
    int dx = 0;
    int teta = - a22 * y;
    int f = (b2 - a2*y + 0.25 * a2);
    for (x = 0; x <= x_max; ++x)
    {
        draw_4_pixels(x_c, y_c, x, y, painter);
        if (f >= 0)
        {
            y--;
            teta += a22;
            f += teta;
        }
        dx += b22;
        f += b2 + dx;
    }
    teta = b22 * x;
    int dy = -a22 * y;
    f += -b2 * (x+0.75) - a2 * (y-0.75);
    for (; y >= 0; --y)
    {
        draw_4_pixels(x_c, y_c, x, y, painter);
        if (f < 0)
        {
            x++;
            teta += b22;
            f += teta;
        }
        dy += a22;
        f += a2 + dy;
    }
    return 0;
}

time_t QPaintWidget::drawMidPointCircle(const ellipse_t &circle, QPainter &painter)
{
    painter.setPen(QPen(circle.color));
    int x_c = circle.pc.x();
    int y_c = circle.pc.y();
    int r2 = circle.a * circle.a;
    int r22 = 2 * r2;
    int x_max = circle.a/sqrt(2);

    int x = 0, y = circle.b;
    int dx = 0;
    int teta = - r22*y;
    int f = (r2 - r2*y + 0.25 * r2);
    for (x = 0; x <= x_max; ++x)
    {
        draw_4_pixels(x_c, y_c, x, y, painter);
        if (f >= 0)
        {
            y--;
            teta += r22;
            f += teta;
        }
        dx += r22;
        f += r2 + dx;
    }
    teta = r22 * x;
    int dy = -r22 * y;
    f += -r2 * (x+0.75) - r2 * (y-0.75);
    for (; y >= 0; --y)
    {
        draw_4_pixels(x_c, y_c, x, y, painter);
        if (f < 0)
        {
            x++;
            teta += r22;
            f += teta;
        }
        dy += r22;
        f += r2 + dy;
    }
    return 0;
}

void QPaintWidget::drawEllipse(const ellipse_t &ellipse, QPainter &painter)
{
    switch (ellipse.alg)
    {
    case alg_canon:
        this->drawCanonEllipse(ellipse, painter);
        break;
    case alg_param:
        this->drawParamEllipse(ellipse, painter);
        break;
    case alg_Bresenham:
        this->drawBresenhamEllipse(ellipse, painter);
        break;
    case alg_mid_point:
        this->drawMidPointEllipse(ellipse, painter);
        break;
    case alg_Qt_std:
        painter.setPen(QPen(ellipse.color));
        painter.drawEllipse(ellipse.pc, ellipse.a, ellipse.b);
        break;
    }
}

void QPaintWidget::drawCircle(const ellipse_t &circle, QPainter &painter)
{
    switch (circle.alg)
    {
    case alg_canon:
        this->drawCanonCircle(circle, painter);
        break;
    case alg_param:
        this->drawParamCircle(circle, painter);
        break;
    case alg_Bresenham:
        this->drawBresenhamCircle(circle, painter);
        break;
    case alg_mid_point:
        this->drawMidPointCircle(circle, painter);
        break;
    case alg_Qt_std:
        painter.setPen(QPen(circle.color));
        painter.drawEllipse(circle.pc, circle.a, circle.b);
        break;
    }
}

void QPaintWidget::drawEllipseSpectr(const solar_t &solar, QPainter &painter)
{
    double x_c = this->width()/2/pixel_size;
    double y_c = this->height()/2/pixel_size;
    QPoint center(x_c, y_c);
    int a = solar.a;
    int b = solar.b;
    for (int i = 0; i < solar.N; ++i)
    {
        drawEllipse({.pc=center, .a=a, .b=b, .color=solar.color, .alg=solar.alg}, painter);
        a += solar.da;
        b += (double) solar.b/solar.a * solar.da;
    }
}

void QPaintWidget::drawCircleSpectr(const solar_t &solar, QPainter &painter)
{
    double x_c = this->width()/2/pixel_size;
    double y_c = this->height()/2/pixel_size;
    QPoint center(x_c, y_c);
    int a = solar.a;
    for (int i = 0; i < solar.N; ++i)
    {
        drawCircle({.pc=center, .a=a, .b=a, .color=solar.color, .alg=solar.alg}, painter);
        a += solar.da;
    }
}

void QPaintWidget::addEllipse(const ellipse_t &ellipse)
{
    ellipses.push_back(ellipse);
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
    ellipses.clear();
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

    for (int i = 0; i < ellipses.size(); ++i)
    {
        if (ellipses[i].a == ellipses[i].b)
            drawCircle(ellipses[i], painter);
        else
            drawEllipse(ellipses[i], painter);
    }

    for (int i = 0; i < solars.size(); ++i)
    {
        if (solars[i].a == solars[i].b)
            drawCircleSpectr(solars[i], painter);
        else
            drawEllipseSpectr(solars[i], painter);
    }

    painter.end();

    image = image.scaled(image_width * pixel_size, image_height * pixel_size);
    painter.begin(this);
    painter.drawImage(0,0,image);
    painter.end();
}
