#ifndef QPAINTWIDGET_H
#define QPAINTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QPoint>
#include <QDebug>

#include "printinfo.h"
#include "config.h"

class QPaintWidget : public QWidget
{
    Q_OBJECT

private:
    int border;
    bool painting_flag;
    PrintInfo *current_info = NULL;
private:

public:
    explicit QPaintWidget(QWidget *parent = 0);

    bool getPainting_flag() const;
    void setPainting_flag(bool value);

    int getBorder() const;
    void setBorder(int value);
    void draw(PrintInfo *);
    PrintInfo *getCurrent_info() const;
    void setCurrent_info(PrintInfo *value);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);
};

#endif // QPAINTWIDGET_H
