#ifndef QCOORDSWIDGET_H
#define QCOORDSWIDGET_H

#include <QLabel>
#include <QHBoxLayout>
#include <QString>
#include "qlabeledit.h"
#include "config.h"

class QCoordsWidget : public QWidget
{
    Q_OBJECT

private:
    QHBoxLayout *layout;
    QLabelEdit *edit_x;
    QLabelEdit *edit_y;
    QLabel *label;

public:
    explicit QCoordsWidget(QWidget *parent = 0);
    QCoordsWidget(const QString text, QWidget *parent = 0);
    void setX(double);
    void setY(double);
    void setLabelText(QString);
    double getX(void);
    double getY(void);
    QPointF getPointF(void);
    QPoint getPoint(void);

signals:
    void edited(void);
public slots:
    void changeEditText(QString);
};

#endif // QCOORDSWIDGET_H
