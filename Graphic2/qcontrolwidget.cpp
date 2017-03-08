#include "qcontrolwidget.h"


void QControlWidget::updateInfo()
{

}


QControlWidget::QControlWidget(QWidget *parent) : QWidget(parent)
{
    //creating
    main_layout = new QVBoxLayout(this);

    //setting main_layout of widget
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setLayout(main_layout);

    //move group
    group_move = new QGroupBox("Перенос");
    move_layout = new QFormLayout(this);
    dx_edit = new QLabelEdit(this);
    dy_edit = new QLabelEdit(this);
    btn_move = new QPushButton("Перенести");

    dx_edit->setLabelText("dx: ");
    dx_edit->setEditText("0.0");
    dx_edit->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}(\\.|,|$)[0-9]{0,4}$"),0));
    dy_edit->setLabelText("dy: ");
    dy_edit->setEditText("0.0");
    dy_edit->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}(\\.|,|$)[0-9]{0,4}$"),0));
    QHBoxLayout *row = new QHBoxLayout(this);
    row->addWidget(dx_edit);
    row->addWidget(dy_edit);
    move_layout->addRow(row);
    move_layout->addRow(btn_move);
    group_move->setLayout(move_layout);

    //change group
    group_change = new QGroupBox("Преобразования");
    kx_edit = new QLabelEdit(this);
    kx_edit->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}(\\.|$)[0-9]{0,4}$"),0));

    ky_edit = new QLabelEdit(this);
    ky_edit->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}(\\.|$)[0-9]{0,4}$"),0));
    angle_edit  = new QLabelEdit(this);
    point_edit  = new QCoordsWidget(this);
    btn_turn = new QPushButton("Поворот");
    btn_scale = new QPushButton("Масштаб.");
    change_layout = new QFormLayout(this);
    group_move->setFixedHeight(130);

    group_change->setLayout(change_layout);
    group_change->setFixedHeight(270);
    point_edit->setLabelText("M");
    kx_edit->setEditText("1");
    kx_edit->setLabelText("kx");
    ky_edit->setEditText("1");
    ky_edit->setLabelText("ky");

    angle_edit->setLabelText("θ(град): ");
    angle_edit->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}(\\.|$)[0-9]{0,4}$"),0));
    angle_edit->setEditText("0.0");
    QVBoxLayout *column_1 = new QVBoxLayout(this);
    column_1->addWidget(kx_edit);
    column_1->addWidget(ky_edit);
    QHBoxLayout *row_1 = new QHBoxLayout(this);
    row_1->addLayout(column_1);
    row_1->addWidget(btn_scale);

    QHBoxLayout *row_2 = new QHBoxLayout(this);
    row_2->addWidget(angle_edit);
    row_2->addWidget(btn_turn);
    change_layout->addRow(point_edit);
    change_layout->addRow(row_1);
    change_layout->addRow(row_2);

    btn_back = new QPushButton("Назад", this);
    btn_draw = new QPushButton("Нарисовать", this);
    //adding to main_layout
    main_layout->addWidget(group_move);
    main_layout->addWidget(group_change);
    main_layout->addWidget(btn_draw);
    main_layout->addWidget(btn_back);
    main_layout->addStretch();
    //this->setMaximumHeight(460);
    this->setMinimumHeight(460);

    //slots and signals
    connect(this->btn_move, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnMove(bool)));
    connect(this->btn_scale, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnScale(bool)));
    connect(this->btn_turn, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnTurn(bool)));
    connect(this->btn_back, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnBack(bool)));
    connect(this->btn_draw, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnDraw(bool)));
}

QPointF *QControlWidget::getMovePoint()
{
    QPointF *p = new QPointF();
    p->setX(dx_edit->getEditText().toDouble());
    p->setY(dy_edit->getEditText().toDouble());
    return p;
}

double QControlWidget::getAngle()
{
    return angle_edit->getEditText().toDouble();
}

double QControlWidget::getKx()
{
    return kx_edit->getEditText().toDouble();
}

double QControlWidget::getKy()
{
    return ky_edit->getEditText().toDouble();
}

QPointF *QControlWidget::getChangePoint()
{
    QPointF *p = new QPointF(point_edit->getX(), point_edit->getY());
    return p;
}

void QControlWidget::onClickedBtnMove(bool val)
{
    emit onMoveSignal(val);
}

void QControlWidget::onClickedBtnScale(bool val)
{
    emit onScaleSignal(val);
}

void QControlWidget::onClickedBtnTurn(bool val)
{
    emit onTurnSignal(val);
}

void QControlWidget::onClickedBtnBack(bool val)
{
    emit onBackSignal(val);
}

void QControlWidget::onClickedBtnDraw(bool val)
{
    emit onDrawSignal(val);
}

