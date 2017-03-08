#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include "treangleinfo.h"
#include "config.h"

#define PEN_WIDTH 2

class QPaintWidget : public QWidget
{
    Q_OBJECT

private:

    double k; //к-т масштабирования
    int border;
    TreangleInfo *info;
    bool painting_flag;
private:
    void get_k(void);
    void drawLine(Point *, Point *, QColor);
    void drawPoint(Point *, QColor);

public:
    explicit QPaintWidget(QWidget *parent = 0);

    TreangleInfo *getInfo() const;
    void setInfo(TreangleInfo *value);

    bool getPainting_flag() const;
    void setPainting_flag(bool value);

    int getBorder() const;
    void setBorder(int value);
    void draw(void);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // QPAINTWIDGET_H
