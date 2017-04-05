#include "qcoordswidget.h"

QCoordsWidget::QCoordsWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QHBoxLayout(this);
    setLayout(layout);

    QFont font = this->font();
    font.setPointSize(FONT_SIZE);
    this->setFont(font);

    label = new QLabel(this);

    edit_x = new QLabelEdit(this);
    edit_x->setLabelText("X:");
    edit_x->setEditText("0");
    edit_x->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));

    edit_y = new QLabelEdit(this);
    edit_y->setLabelText("Y:");
    edit_y->setEditText("0");
    edit_y->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));

    layout->setSpacing(0);
    layout->addWidget(label);
    layout->addWidget(edit_x);
    layout->addWidget(edit_y);

    //Slots and Signals
    connect(this->edit_x, SIGNAL(edited(QString)), this, SLOT(changeEditText(QString)));
    connect(this->edit_y, SIGNAL(edited(QString)), this, SLOT(changeEditText(QString)));
}

void QCoordsWidget::setX(double x)
{
    edit_x->setEditText(QString::number(x));
}

void QCoordsWidget::setY(double y)
{
    edit_y->setEditText(QString::number(y));
}

void QCoordsWidget::setLabelText(QString str)
{
    label->setText(str);
}

double QCoordsWidget::getX(void)
{
    return edit_x->getEditText().replace(",", ".").toDouble();
}

double QCoordsWidget::getY(void)
{
    return edit_y->getEditText().replace(",",".").toDouble();
}

QPointF QCoordsWidget::getPointF()
{
    return QPointF(edit_x->getEditText().toDouble(), edit_y->getEditText().toDouble());
}

QPoint QCoordsWidget::getPoint()
{
    return QPoint(round(edit_x->getEditText().toDouble()), round(edit_y->getEditText().toDouble()));
}

void QCoordsWidget::changeEditText(QString str)
{
    emit edited();
}
