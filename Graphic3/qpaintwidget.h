#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QDebug>

#include "printinfo.h"
//#include "config.h"

class QPaintWidget : public QWidget
{
    Q_OBJECT

private:

public:
    explicit QPaintWidget(QWidget *parent = 0);
    void draw(void);
signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // QPAINTWIDGET_H
