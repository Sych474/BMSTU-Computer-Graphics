#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QPointF>
#include <QDebug>
#include <vector>
#include <QImage>

#include "config.h"
#include "errors.h"

enum alg_t
{
    alg_canon,
    alg_param,
    alg_mid_point,
    alg_Bresenham,
    alg_Qt_std,
};

struct ellipse_t
{
    QPoint pc;
    int a;
    int b;
    QColor color;
    alg_t alg;
};

struct solar_t
{
    int a;
    int b;
    int da;
    int N;
    QColor color;
    alg_t alg;
};

class QPaintWidget : public QWidget
{
    Q_OBJECT

private:
    void draw_4_pixels(int x_c, int y_c, int x, int y, QPainter &painter);

    time_t drawCanonEllipse(const ellipse_t &ellipse, QPainter &painter);
    time_t drawCanonCircle(const ellipse_t &circle, QPainter &painter);

    time_t drawParamEllipse(const ellipse_t &ellipse, QPainter &painter);
    time_t drawParamCircle(const ellipse_t &circle, QPainter &painter);

    time_t drawBresenhamEllipse(const ellipse_t &ellipse, QPainter &painter);
    time_t drawBresenhamCircle(const ellipse_t &circle, QPainter &painter);

    time_t drawMidPointEllipse(const ellipse_t &ellipse, QPainter &painter);
    time_t drawMidPointCircle(const ellipse_t &circle, QPainter &painter);

    void drawEllipse(const ellipse_t &ellipse, QPainter &painter);
    void drawCircle(const ellipse_t &circle, QPainter &painter);
    void drawEllipseSpectr(const solar_t &solar, QPainter &painter);
    void drawCircleSpectr(const solar_t &solar, QPainter &painter);

private:
    int pixel_size = 1;
    QColor fone_color = Qt::white;
    std::vector<ellipse_t> ellipses;
    std::vector<solar_t> solars;
public:
    void addEllipse(const ellipse_t &ellipse);
    void addSolar(solar_t &solar);

    explicit QPaintWidget(QWidget *parent = 0);
    void clear(void);


    QColor getFone_color() const;
    void setFone_color(const QColor &value);

    int getPixel_size() const;
    void setPixel_size(int value);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // QPAINTWIDGET_H
