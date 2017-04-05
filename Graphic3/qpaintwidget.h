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
#include "config.h"
#include "errors.h"

enum alg_t
{
    alg_DDA,
    alg_Bresenham_double,
    alg_Bresenham_int,
    alg_Bresenham_alias,
    alg_Qt_std,
    alg_Vu,
};

struct line_t
{
    QPoint pb;
    QPoint pe;
    QColor color;
    alg_t alg;

};

struct solar_t
{
    QColor color;
    alg_t alg;
    double teta;
};

class QPaintWidget : public QWidget
{
    Q_OBJECT

private:
    bool is_point(int dx, int dy);
    time_t drawCDALine(const QPoint &pb, const QPoint &pe, const QColor &color, QPainter &painter);
    time_t drawBresenhamDLine(const QPoint &pb, const QPoint &pe, const QColor &color, QPainter &painter);
    time_t drawBresenhamILine(const QPoint &pb, const QPoint &pe, const QColor &color, QPainter &painter);
    time_t drawBresenhamALine(const QPoint &pb, const QPoint &pe, const QColor &color, QPainter &painter);
    //time_t drawVuLine(const QPoint &pb, const QPoint &pe, const QColor &color, QPainter &painter);
    void drawLine(const line_t &line, QPainter &painter);
    void drawSolar(const solar_t &solar, QPainter &painter);
private:
    int pixel_size = 1;
    QColor fone_color = Qt::white;
    std::vector<line_t> lines;
    std::vector<solar_t> solars;
public:
    void addLine(line_t &line);
    void addSolar(solar_t &solar);
    explicit QPaintWidget(QWidget *parent = 0);
    void draw(void);
    QColor getFone_color() const;
    void setFone_color(const QColor &value);
    void clear(void);
    int getPixel_size() const;
    void setPixel_size(int value);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // QPAINTWIDGET_H
