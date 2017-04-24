#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(MAIN_X1, MAIN_Y1, MAIN_X2, MAIN_Y2);

    QFont font = this->font();
    font.setPointSize(FONT_SIZE);
    this->setFont(font);

    main_widget = new QWidget(this);
    main_widget->setMinimumSize(600,300);
    setCentralWidget(main_widget);

    main_layout = new QHBoxLayout(this);
    main_widget->setLayout(main_layout);

    scene_widget = new QPaintWidget(main_widget);
    scene_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    control_widget = new QWidget(this);
    control_widget->setFixedWidth(CONTROL_WIDGET_X);
    main_layout->addWidget(control_widget);
    main_layout->addWidget(scene_widget);

    //creating
    control_layout = new QVBoxLayout(this);

    //setting main_layout of widget
    control_widget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    control_widget->setLayout(control_layout);

    //adding to main_layout
    CreateSettingsGroup();
    CreatePoligonInputGroup();
    CreatePaintGroup();
    control_layout->addWidget(group_colors);
    control_layout->addWidget(group_input);
    control_layout->addWidget(group_paint);
    control_layout->addStretch();

    scene_widget->paint();
    //slots and signals
    connect(this->btn_next_point, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnSetPoint(bool)));
    connect(this->btn_close_poligon, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnClosePoligon(bool)));
    connect(this->btn_fill, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnPaint(bool)));
    connect(this->btn_step_fill, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnStepPaint(bool)));
    connect(this->btn_set_separator, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnSetSeparator(bool)));

    connect(this->btn_clear, SIGNAL(clicked(bool)), this, SLOT(onClickedBtnClear(bool)));
    connect(this->color_fill, SIGNAL(colorChanged(QColor)), this, SLOT(onFillColorChanges(QColor)));
    connect(this->color_face, SIGNAL(colorChanged(QColor)), this, SLOT(onFaceColorChanges(QColor)));
    connect(this->color_sep, SIGNAL(colorChanged(QColor)), this, SLOT(onSepColorChanges(QColor)));
}

void MainWindow::CreatePaintGroup()
{
    group_paint = new QGroupBox("", this);
    layout_paint = new QVBoxLayout(this);
    btn_fill = new QPushButton("Залить");
    btn_step_fill = new QPushButton("Залить с задержкой");
    btn_clear = new QPushButton("Очистить экран");

    layout_paint->addWidget(btn_fill);
    layout_paint->addWidget(btn_step_fill);
    layout_paint->addWidget(btn_clear);

    group_paint->setLayout(layout_paint);
}

void MainWindow::CreateSettingsGroup()
{
    group_colors = new QGroupBox("Настройки", this);
    layout_colors = new QVBoxLayout(this);
    color_fill = new QColorWidget(this);
    color_fill->setWidth(50);
    color_fill->setColor(Qt::darkRed);
    lbl_color_fill = new QLabel("Цвет закраски");

    QHBoxLayout *layout1 = new QHBoxLayout(this);
    layout1->addWidget(lbl_color_fill);
    layout1->addWidget(color_fill);

    color_face = new QColorWidget(this);
    color_face->setWidth(50);
    color_face->setColor(Qt::black);
    lbl_color_face = new QLabel("Цвет границы");

    QHBoxLayout *layout2 = new QHBoxLayout(this);
    layout2->addWidget(lbl_color_face);
    layout2->addWidget(color_face);

    color_sep = new QColorWidget(this);
    color_sep->setWidth(50);
    color_sep->setColor(Qt::red);
    lbl_color_sep = new QLabel("Цвет перегородки");

    QHBoxLayout *layout3 = new QHBoxLayout(this);
    layout3->addWidget(lbl_color_sep);
    layout3->addWidget(color_sep);

    layout_colors->addLayout(layout1);
    layout_colors->addLayout(layout2);
    layout_colors->addLayout(layout3);
    layout_colors->addStretch();
    group_colors->setLayout(layout_colors);
}

void MainWindow::setPoint(const QPoint &point)
{
    qDebug() << "In";
    if (new_poligon)
    {
        scene_widget->add_point(point);
        new_poligon = false;
        start_point = point;
    }
    else
    {
        edge_t edge = {prev_point, point};
        scene_widget->add_edge(edge);
    }
    prev_point = point;
    scene_widget->repaint();
}

void MainWindow::closePoligon()
{
    if (new_poligon) return;

    new_poligon = true;
    edge_t edge = {prev_point, start_point};
    scene_widget->add_edge(edge);
    scene_widget->repaint();
}

void MainWindow::CreatePoligonInputGroup()
{
    group_input = new QGroupBox("Ввод", this);
    layout_input = new QVBoxLayout(this);
    cw_point = new QCoordsWidget();
    edit_separator_x = new QLabelEdit("Разделитель:");
    edit_separator_x->setEditText(QString::number(SEPARATOR_X));
    btn_set_separator = new QPushButton("Установить перегородку");
    btn_next_point = new QPushButton("Поставить точку");
    btn_close_poligon = new QPushButton("Закончить многоугольник");

    layout_input->addWidget(cw_point);
    layout_input->addWidget(btn_next_point);
    layout_input->addWidget(btn_close_poligon);
    layout_input->addWidget(edit_separator_x);
    layout_input->addWidget(btn_set_separator);

    group_input->setLayout(layout_input);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onClickedBtnPaint(bool)
{
    scene_widget->fillPoligon();
}

void MainWindow::onClickedBtnStepPaint(bool)
{
    scene_widget->stepFillPioligon();
}

void MainWindow::onClickedBtnSetPoint(bool)
{
    this->setPoint(cw_point->getPoint());
}

void MainWindow::onClickedBtnClosePoligon(bool)
{
    closePoligon();
}

void MainWindow::onClickedBtnSetSeparator(bool)
{
    int x = edit_separator_x->getEditText().toInt();
    if (x >= 0 && x <= scene_widget->width())
        scene_widget->setSeparator_x(x);
}

void MainWindow::onFillColorChanges(const QColor &color)
{
    scene_widget->setFill_color(color);
}

void MainWindow::onFaceColorChanges(const QColor &color)
{
    scene_widget->setFace_color(color);
}

void MainWindow::onSepColorChanges(const QColor &color)
{
    scene_widget->setSep_color(color);
}

void MainWindow::onClickedBtnClear(bool)
{
    scene_widget->clear();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint p = scene_widget->mapFromGlobal(QCursor::pos());
    if (event->button() == Qt::LeftButton)
    {
        if (shift_pressed && !ctrl_pressed)
        {
            p.setY(prev_point.y());
        }
        if (ctrl_pressed && !shift_pressed)
        {
            p.setX(prev_point.x());
        }
        setPoint(p);
    }
    else
    {
        closePoligon();
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    int key = event->key();
    if (key == Qt::Key_Shift)
    {
        shift_pressed = true;
    }
    if (key == Qt::Key_Control)
    {
        ctrl_pressed = true;
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    int key = event->key();
    if (key == Qt::Key_Shift)
    {
        shift_pressed = false;
    }
    if (key == Qt::Key_Control)
    {
        ctrl_pressed = false;
    }
}

