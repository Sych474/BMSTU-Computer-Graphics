#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QPointF>
#include <QDebug>
#include <vector>
#include <QImage>

#include "printinfo.h"
//#include "config.h"
#include "errors.h"

enum alg_t
{
    alg_CDA,
    alg_Bresenham_int,
    alg_Bresenham_double,
    alg_Bresenham_alias,
    alg_Qt_std,
};

struct line_t
{
    QPointF pb;
    QPointF pe;
    QColor color;
    alg_t alg;

};


class QPaintWidget : public QWidget
{
    Q_OBJECT

private:
    bool is_point(int dx, int dy);
    time_t drawCDALine(const QPointF &pb, const QPointF &pe, const QColor &color, QPainter &painter);
    time_t drawBresenhamDLine(const QPointF &pb, const QPointF &pe, const QColor &color, QPainter &painter);
    time_t drawBresenhamILine(const QPointF &pb, const QPointF &pe, const QColor &color, QPainter &painter);
    time_t drawBresenhamALine(const QPointF &pb, const QPointF &pe, const QColor &color, QPainter &painter);
    void drawLine(const line_t &line, QPainter &painter);
private:
    int pixel_size = 1;
    QColor fone_color = Qt::white;
    QColor line_color = Qt::black;
    std::vector<line_t> lines;
public:
    explicit QPaintWidget(QWidget *parent = 0);
    void draw(void);
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
