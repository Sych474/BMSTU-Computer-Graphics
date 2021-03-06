#include "qcontrolwidget.h"


QPaintWidget *QControlWidget::getPw() const
{
    return pw;
}

void QControlWidget::setPw(QPaintWidget *value)
{
    pw = value;
}

void QControlWidget::onClickedBtnDrawLine(bool)
{
    QColor color = color_line->getColor();
    if (rbn_fone_color->isChecked())
        color = color_fone->getColor();
    line_t line = {.pb=cw_point_1->getPoint(), .pe=cw_point_2->getPoint(), .color=color, .alg=sellected_alg};
    pw->addLine(line);
    pw->repaint();
}

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
    lbl_color_fone = new QLabel("Цвет фона");
    lbl_color_line = new QLabel("Цвет линий");
    btn_set_pixel_size = new QPushButton("Установить");

    layout_colors->addWidget(edit_pixel_size);
    layout_colors->addWidget(btn_set_pixel_size);
    QHBoxLayout *layout1 = new QHBoxLayout(this);
    layout1->addWidget(lbl_color_fone);
    layout1->addStretch(10);
    layout1->addWidget(color_fone);
    layout1->addStretch(70);
    layout_colors->addLayout(layout1);
    rbn_fone_color = new QRadioButton("фоном");
    QHBoxLayout *layout2 = new QHBoxLayout(this);
    layout2->addWidget(lbl_color_line);
    layout2->addWidget(color_line);
    layout2->addWidget(rbn_fone_color);
    layout_colors->addLayout(layout2);
    layout_colors->addStretch();
    group_colors->setLayout(layout_colors);

    //Line
    group_line = new QGroupBox("Рисование линии", this);
    layout_line = new QVBoxLayout(this);
    cw_point_1 = new QCoordsWidget(this);
    cw_point_1->setLabelText("Точка 1:");
    cw_point_2 = new QCoordsWidget(this);
    cw_point_2->setLabelText("Точка 2:");
    btn_draw_line = new QPushButton("Нарисовать");

    layout_line->addWidget(cw_point_1);
    layout_line->addWidget(cw_point_2);
    layout_line->addWidget(btn_draw_line);
    group_line->setLayout(layout_line);
    layout_line->addStretch();

    //Solar
    group_solar = new QGroupBox("Рисование спектра", this);
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
    group_alg = new QGroupBox("Выбор алгоритма", this);
    layout_alg = new QVBoxLayout(this);
    combobox_alg = new QComboBox(this);
    combobox_alg->addItem("ЦДА");
    combobox_alg->addItem("Брезенхем (double)");
    combobox_alg->addItem("Брезенхем (int)");
    combobox_alg->addItem("Брезенхем со сглаживанием");
    combobox_alg->addItem("Стандартный(Qt)");

    layout_alg->addWidget(combobox_alg);
    group_alg->setLayout(layout_alg);


    //adding to main_layout
    btn_clear = new QPushButton("Очистить экран");
    main_layout->addWidget(group_alg);
    main_layout->addWidget(group_colors);
    main_layout->addWidget(group_line);
    main_layout->addWidget(group_solar);
    main_layout->addWidget(btn_clear);
    main_layout->addStretch();
    this->setMinimumHeight(700);

    //slots and signals
    connect(this->btn_draw_line, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnDrawLine(bool)));
    connect(this->btn_draw_solar, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnDrawSolar(bool)));
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
