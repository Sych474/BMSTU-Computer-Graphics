#include "qlabeledit.h"

QLabelEdit::QLabelEdit(QWidget *parent) : QWidget(parent)
{
    //creating
    label = new QLabel(this);
    edit = new QLineEdit(this);
    layout = new QHBoxLayout(this);

    //adding to layout
    layout->addWidget(label);
    layout->addWidget(edit);

    //configure layout
    layout->setMargin(MARGIN);
    this->setLayout(layout);

    //signals and slots
    connect(this->edit, SIGNAL(textChanged(QString)), this, SLOT(changeEditText(QString)));
}

QLabelEdit::QLabelEdit(const QString text, QWidget *parent) : QWidget(parent)
{
    //creating
    label = new QLabel(this);
    edit = new QLineEdit(this);
    layout = new QHBoxLayout(this);

    label->setText(text);

    //adding to layout
    layout->addWidget(label);
    layout->addWidget(edit);

    //configure layout
    layout->setMargin(MARGIN);
    this->setLayout(layout);

    //signals and slots
    connect(this->edit, SIGNAL(textChanged(QString)), this, SLOT(changeEditText(QString)));
}


void QLabelEdit::setLabelText(const QString str)
{
    this->label->setText(str);
}

void QLabelEdit::setEditText(const QString str)
{
    if (str != string)
    {
        edit->setText(str);
        string = str;
        emit edited(str);
    }
}

void QLabelEdit::setEditValidator(const QValidator *validator)
{
    edit->setValidator(validator);
}


QString QLabelEdit::getEditText(void)
{
    return string;
}

void QLabelEdit::changeEditText(QString str)
{
    string = str;
}
