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

    //Colors
    group_colors = new QGroupBox(this);
    layout_colors = new QVBoxLayout(this);
    color_fone = new QColorWidget(this);
    color_line = new QColorWidget(this);
    color_fone->setWidth(100);
    color_line->setWidth(100);
    edit_pixel_size = new QLabelEdit(this);
    edit_pixel_size->setLabelText("Размер пикселя");
    edit_pixel_size->setEditText("1");
    edit_pixel_size->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));
    lbl_color_fone = new QLabel("Цвет фона");
    lbl_color_line = new QLabel("Цвет линий");
    btn_set_pixel_size = new QPushButton("Установить");

    layout_colors->addWidget(edit_pixel_size);
    layout_colors->addWidget(btn_set_pixel_size);
    QHBoxLayout *layout1 = new QHBoxLayout(this);
    layout1->addWidget(lbl_color_fone);
    layout1->addWidget(color_fone);
    layout_colors->addLayout(layout1);
    QHBoxLayout *layout2 = new QHBoxLayout(this);
    layout2->addWidget(lbl_color_line);
    layout2->addWidget(color_line);
    layout_colors->addLayout(layout2);
    layout_colors->addStretch();
    group_colors->setLayout(layout_colors);

    //Line
    group_line = new QGroupBox(this);
    layout_line = new QVBoxLayout(this);
    cw_point_1 = new QCoordsWidget(this);
    cw_point_2 = new QCoordsWidget(this);
    btn_draw_line = new QPushButton("Нарисовать");

    layout_line->addWidget(cw_point_1);
    layout_line->addWidget(cw_point_2);
    layout_line->addWidget(btn_draw_line);
    group_line->setLayout(layout_line);
    layout_line->addStretch();

    //Solar
    group_solar = new QGroupBox(this);
    layout_solar = new QVBoxLayout(this);
    edit_angle_delta = new QLabelEdit(this);
    edit_angle_delta->setLabelText("Δθ");
    edit_angle_delta->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));
    edit_angle_delta->setEditText("10");
    //QCoordsWidget *cw_solar_senter;
    btn_draw_solar = new QPushButton("Нарисовать");

    layout_solar->addWidget(edit_angle_delta);
    layout_solar->addWidget(btn_draw_solar);
    group_solar->setLayout(layout_solar);
    layout_solar->addStretch();

    //Alg
    group_alg = new QGroupBox(this);
    layout_alg = new QVBoxLayout(this);
    combobox_alg = new QComboBox(this);
    combobox_alg->addItem("CDA");
    combobox_alg->addItem("Брезенхем (int)");
    combobox_alg->addItem("Брезенхем (double)");
    combobox_alg->addItem("Брезенхем со сглаживанием");
    combobox_alg->addItem("Стандартный(Qt)");
    lbl_alg = new QLabel("Алгоритм");
    layout_alg->addWidget(lbl_alg);
    layout_alg->addWidget(combobox_alg);
    group_alg->setLayout(layout_alg);


    //adding to main_layout
    main_layout->addWidget(group_alg);
    main_layout->addWidget(group_colors);
    main_layout->addWidget(group_line);
    main_layout->addWidget(group_solar);
    main_layout->addStretch();
    this->setMinimumHeight(600);

    //slots and signals
    /*connect(this->btn_move, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnMove(bool)));
    connect(this->btn_scale, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnScale(bool)));
    connect(this->btn_turn, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnTurn(bool)));
    connect(this->btn_back, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnBack(bool)));
    connect(this->btn_draw, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnDraw(bool)));*/
}

