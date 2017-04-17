#include "qcontrolwidget.h"


QPaintWidget *QControlWidget::getPw() const
{
    return pw;
}

void QControlWidget::setPw(QPaintWidget *value)
{
    pw = value;
}

void QControlWidget::onClickedBtnDrawCircle(bool)
{
    QColor color = color_line->getColor();
    if (rbn_fone_color->isChecked())
        color = color_fone->getColor();
    int a = edit_cercle_r->getEditText().toInt();
    ellipse_t circle = {.pc=cw_cercle_center->getPoint(), .a=a, .b=a, .color=color, .alg=sellected_alg};
    pw->addEllipse(circle);
    pw->repaint();
}

void QControlWidget::onClickedBtnDrawEllipse(bool)
{
    QColor color = color_line->getColor();
    if (rbn_fone_color->isChecked())
        color = color_fone->getColor();
    int a = edit_ellipse_a->getEditText().toInt();
    int b = edit_ellipse_b->getEditText().toInt();
    ellipse_t ellipse = {.pc=cw_ellipse_center->getPoint(), .a=a, .b=b, .color=color, .alg=sellected_alg};
    pw->addEllipse(ellipse);
    pw->repaint();
}

void QControlWidget::onClickedBtnDrawCircleSolar(bool)
{
    QColor color = color_line->getColor();
    if (rbn_fone_color->isChecked())
        color = color_fone->getColor();
    int a = edit_circle_r_beg->getEditText().toInt();
    int da = edit_circle_r_delta->getEditText().toInt();
    int N = edit_circle_count->getEditText().toInt();

    solar_t solar = {};
    solar.alg = sellected_alg;
    solar.color = color;
    solar.a = a;
    solar.b = a;
    solar.da = da;
    solar.N = N;
    pw->addSolar(solar);
    pw->repaint();
}

void QControlWidget::onClickedBtnDrawEllipseSolar(bool)
{
    QColor color = color_line->getColor();
    if (rbn_fone_color->isChecked())
        color = color_fone->getColor();
    int a = edit_ellipse_a_beg->getEditText().toInt();
    int b = edit_ellipse_b_beg->getEditText().toInt();
    int da = edit_ellipse_a_delta->getEditText().toInt();
    int N = edit_ellipse_count->getEditText().toInt();

    solar_t solar = {};
    solar.alg = sellected_alg;
    solar.color = color;
    solar.a = a;
    solar.b = b;
    solar.da = da;
    solar.N = N;
    pw->addSolar(solar);
    pw->repaint();
}

/*
void QControlWidget::onClickedBtnDrawLine(bool)
{
    QColor color = color_line->getColor();
    if (rbn_fone_color->isChecked())
        color = color_fone->getColor();
    line_t line = {.pb=cw_point_1->getPoint(), .pe=cw_point_2->getPoint(), .color=color, .alg=sellected_alg};
    pw->addLine(line);
    pw->repaint();
}
*/

/*
void QControlWidget::onClickedBtnDrawSolar(bool)
{
    double angle = edit_angle_delta->getEditText().toDouble();
    QColor color = color_line->getColor();
    if (rbn_fone_color->isChecked())
        color = color_fone->getColor();
    solar_t solar = {};
    solar.alg = sellected_alg;
    solar.color = color;
    solar.teta = angle;
    pw->addSolar(solar);
    pw->repaint();
}
*/

void QControlWidget::onClickedBtnClear(bool)
{
    pw->clear();
    pw->repaint();
}

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
    group_colors = new QGroupBox("Настройки", this);
    layout_colors = new QVBoxLayout(this);
    color_fone = new QColorWidget(this);
    color_line = new QColorWidget(this);
    color_fone->setWidth(50);
    color_line->setWidth(50);
    color_line->setColor(Qt::black);
    edit_pixel_size = new QLabelEdit(this);
    edit_pixel_size->setLabelText("Размер пикселя");
    edit_pixel_size->setEditText("1");
    edit_pixel_size->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));
    btn_set_pixel_size = new QPushButton("Установить");
    QHBoxLayout *layout1 = new QHBoxLayout(this);
    layout1->addWidget(edit_pixel_size);
    layout1->addWidget(btn_set_pixel_size);

    lbl_color_fone = new QLabel("Фон");
    lbl_color_line = new QLabel("Линия");
    rbn_fone_color = new QRadioButton("цветом фона");

    QHBoxLayout *layout2 = new QHBoxLayout(this);
    layout2->addWidget(lbl_color_fone);
    layout2->addWidget(color_fone);
    layout2->addWidget(rbn_fone_color);
    layout2->addWidget(lbl_color_line);
    layout2->addWidget(color_line);

    layout_colors->addLayout(layout1);
    layout_colors->addLayout(layout2);
    layout_colors->addStretch();
    group_colors->setLayout(layout_colors);

    //Circule
    group_cercle = new QGroupBox("Рисование окружности", this);
    layout_cercle = new QVBoxLayout(this);
    cw_cercle_center = new QCoordsWidget(this);
    cw_cercle_center->setLabelText("Центр:");
    edit_cercle_r = new QLabelEdit(this);

    edit_cercle_r->setEditText("100");
    edit_cercle_r->setLabelText("R");
    edit_cercle_r->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));
    edit_cercle_r->setMaximumWidth(150);
    btn_draw_cercle = new QPushButton("Нарисовать");

    QHBoxLayout *layout4 = new QHBoxLayout(this);
    layout4->addWidget(cw_cercle_center);
    layout4->addWidget(edit_cercle_r);

    layout_cercle->addLayout(layout4);
    layout_cercle->addWidget(btn_draw_cercle);
    group_cercle->setLayout(layout_cercle);
    layout_cercle->addStretch();

    //Circle_Solar
    group_circle_solar = new QGroupBox("Рисование спектра", this);
    layout_circle_solar = new QVBoxLayout(this);
    edit_circle_r_beg = new QLabelEdit(this);
    edit_circle_r_beg->setLabelText("Rн");
    edit_circle_r_beg->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));
    edit_circle_r_beg->setEditText("100");

    edit_circle_count = new QLabelEdit(this);
    edit_circle_count->setLabelText("N");
    edit_circle_count->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));
    edit_circle_count->setEditText("20");

    edit_circle_r_delta = new QLabelEdit(this);
    edit_circle_r_delta->setLabelText("ΔR");
    edit_circle_r_delta->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));
    edit_circle_r_delta->setEditText("10");

    btn_draw_circle_solar = new QPushButton("Нарисовать");

    QHBoxLayout *layout3 = new QHBoxLayout(this);
    layout3->addWidget(edit_circle_r_beg);
    layout3->addWidget(edit_circle_count);
    layout3->addWidget(edit_circle_r_delta);

    layout_circle_solar->addLayout(layout3);
    layout_circle_solar->addWidget(btn_draw_circle_solar);
    group_circle_solar->setLayout(layout_circle_solar);
    layout_circle_solar->addStretch();

    //Ellipse
    group_ellipse = new QGroupBox("Рисование эллипса", this);
    layout_ellipse = new QVBoxLayout(this);
    cw_ellipse_center = new QCoordsWidget(this);
    cw_ellipse_center->setLabelText("Центр:");
    edit_ellipse_a = new QLabelEdit(this);
    edit_ellipse_b = new QLabelEdit(this);

    edit_ellipse_a->setEditText("100");
    edit_ellipse_a->setLabelText("A");
    edit_ellipse_a->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));
    edit_ellipse_a->setMaximumWidth(150);

    edit_ellipse_b->setEditText("100");
    edit_ellipse_b->setLabelText("B");
    edit_ellipse_b->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));
    edit_ellipse_b->setMaximumWidth(150);

    btn_draw_ellipse = new QPushButton("Нарисовать");

    QHBoxLayout *layout5 = new QHBoxLayout(this);
    //layout5->addWidget(cw_ellipse_center);
    layout5->addWidget(edit_ellipse_a);
    layout5->addWidget(edit_ellipse_b);

    layout_ellipse->addWidget(cw_ellipse_center);
    layout_ellipse->addLayout(layout5);
    layout_ellipse->addWidget(btn_draw_ellipse);
    group_ellipse->setLayout(layout_ellipse);
    layout_ellipse->addStretch();

    //Ellipse_Solar
    group_ellipse_solar = new QGroupBox("Рисование спектра", this);
    layout_ellipse_solar = new QVBoxLayout(this);

    edit_ellipse_a_beg = new QLabelEdit(this);
    edit_ellipse_a_beg->setLabelText("Aн");
    edit_ellipse_a_beg->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));
    edit_ellipse_a_beg->setEditText("100");

    edit_ellipse_b_beg = new QLabelEdit(this);
    edit_ellipse_b_beg->setLabelText("Bн");
    edit_ellipse_b_beg->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));
    edit_ellipse_b_beg->setEditText("100");

    edit_ellipse_count = new QLabelEdit(this);
    edit_ellipse_count->setLabelText("N");
    edit_ellipse_count->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));
    edit_ellipse_count->setEditText("20");

    edit_ellipse_a_delta = new QLabelEdit(this);
    edit_ellipse_a_delta->setLabelText("Δa");
    edit_ellipse_a_delta->setEditValidator(new QRegExpValidator(QRegExp("^[-+]?[0-9]{0,5}$"),0));
    edit_ellipse_a_delta->setEditText("10");

    btn_draw_ellipse_solar = new QPushButton("Нарисовать");

    QHBoxLayout *layout6 = new QHBoxLayout(this);
    layout6->addWidget(edit_ellipse_a_beg);
    layout6->addWidget(edit_ellipse_b_beg);

    QHBoxLayout *layout7 = new QHBoxLayout(this);
    layout7->addWidget(edit_ellipse_a_delta);
    layout7->addWidget(edit_ellipse_count);


    layout_ellipse_solar->addLayout(layout6);
    layout_ellipse_solar->addLayout(layout7);
    layout_ellipse_solar->addWidget(btn_draw_ellipse_solar);
    group_ellipse_solar->setLayout(layout_ellipse_solar);
    layout_ellipse_solar->addStretch();

    //Alg
    group_alg = new QGroupBox("Выбор алгоритма", this);
    layout_alg = new QVBoxLayout(this);
    combobox_alg = new QComboBox(this);
    combobox_alg->addItem("Каноническое уравнение");
    combobox_alg->addItem("Параметрическое уровнение");
    combobox_alg->addItem("Алгоритм средней точки");
    combobox_alg->addItem("Алгоритм Брезенхема");
    combobox_alg->addItem("Стандартный(Qt)");

    layout_alg->addWidget(combobox_alg);
    group_alg->setLayout(layout_alg);

    widget1 = new QWidget(this);
    widget1_layout = new QVBoxLayout(this);

    widget1->setLayout(widget1_layout);
    group_cercle->setMaximumHeight(200);
    group_circle_solar->setMaximumHeight(200);
    widget1_layout->addWidget(group_cercle);
    widget1_layout->addWidget(group_circle_solar);

    widget2 = new QWidget(this);
    widget2_layout = new QVBoxLayout(this);

    widget2->setLayout(widget2_layout);
    group_ellipse->setMaximumHeight(200);
    group_ellipse_solar->setMaximumHeight(200);
    widget2_layout->addWidget(group_ellipse);
    widget2_layout->addWidget(group_ellipse_solar);


    //adding to main_layout
    btn_clear = new QPushButton("Очистить экран");
    main_layout->addWidget(group_alg);
    main_layout->addWidget(group_colors);
    tab_widget = new QTabWidget(this);
    main_layout->addWidget(tab_widget);
    tab_widget->addTab(widget1, "Окружность");
    tab_widget->addTab(widget2, "Эллипс");

    main_layout->addWidget(btn_clear);
    main_layout->addStretch();
    this->setMinimumHeight(700);

    //slots and signals
    connect(this->btn_draw_cercle, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnDrawCircle(bool)));
    connect(this->btn_draw_circle_solar, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnDrawCircleSolar(bool)));
    connect(this->btn_draw_ellipse, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnDrawEllipse(bool)));
    connect(this->btn_draw_ellipse_solar, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnDrawEllipseSolar(bool)));


    connect(this->btn_set_pixel_size, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnSetPixelSize(bool)));
    connect(this->btn_clear, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnClear(bool)));
    connect(this->color_fone, SIGNAL(colorChanged(QColor)), this, SLOT(onFoneColorChanges(QColor)));
    connect(this->combobox_alg, SIGNAL(currentIndexChanged(int)), this, SLOT(onAlgCHange(int)));
}

void QControlWidget::onClickedBtnSetPixelSize(bool)
{
    if (!pw) return;

    pw->setPixel_size(edit_pixel_size->getEditText().toInt());
    pw->repaint();
}

void QControlWidget::onFoneColorChanges(const QColor &color)
{
    pw->setFone_color(color);
    qDebug() << color;
    pw->repaint();
}

void QControlWidget::onAlgCHange(int num)
{
    qDebug()<< num;
    this->sellected_alg =(alg_t) num;
}
