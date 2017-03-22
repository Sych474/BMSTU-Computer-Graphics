#ifndef QCOLORWIDGET_H
#define QCOLORWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

class QColorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QColorWidget(QWidget *parent = 0);
    QColor getColor(void);
    void setColor(const QColor &color);
    void setWidth(int width);
    void setHeight(int height);
private:
    QColor color;
signals:
    void colorChanged(const QColor &color);
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
public:
    QPaintEngine *paintEngine() const;
};

#endif // QCOLORWIDGET_H
