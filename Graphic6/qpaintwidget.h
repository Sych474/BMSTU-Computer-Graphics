#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QPointF>
#include <QDebug>
#include <vector>
#include <QImage>
#include <QStack>

#include "config.h"
#include "errors.h"

struct edge_t
{
    QPoint p1;
    QPoint p2;
    QColor color;
};

enum state_t
{
    fill_no,
    fill_standard,
    fill_step
};


class QPaintWidget : public QWidget
{
    Q_OBJECT


private:
    bool need_point = false;
    bool need_fill_point = false;
    QPoint start_p = QPoint(0, 0);
    QPoint fill_point;

    QVector<edge_t> edges;
    QColor fone_color = Qt::white;
    QColor fill_color = Qt::darkRed;
    QColor face_color = Qt::black;
    state_t state = fill_no;
    QImage im;
private:
    void drawEdge(QPainter &painter, const edge_t &edge);
    void drawPoligon(QImage &image);
    void drawPoint(QImage &image);
    void drawFillPoint(QImage &image);
    void drawBresenhamLine(const QPoint &pb, const QPoint &pe, const QColor &color, QPainter &painter);
    void _fillPoligon(QPainter &painter,QImage &image, QPoint &start_p);
    void _fillStepPoligon(QPainter &painter,QImage &image, QPoint &start_p);
    void paint_point(int x, int y, QPainter &painter,QImage &image);
public:
    explicit QPaintWidget(QWidget *parent = 0);
    void paint();

    void fillPoligon();
    void stepFillPioligon();
    void clear(void);

    QColor getFone_color() const;
    QColor getFill_color() const;
    QColor getFace_color() const;
    void setFone_color(const QColor &value);
    void setFill_color(const QColor &value);
    void setFace_color(const QColor &value);

    void add_point(const QPoint &P);
    void add_edge(edge_t edge);
    void end_poligon();

    state_t getState() const;
    void setState(const state_t &value);


    QPoint getFill_point() const;
    void setFill_point(const QPoint &value);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
};

#endif // QPAINTWIDGET_H
