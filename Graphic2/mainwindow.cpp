#include "mainwindow.h"
#include "ui_mainwindow.h"

PrintInfo *MainWindow::generate_start_info(PrintInfo *info)
{
    double x = scene_widget->width()/2;
    double y = scene_widget->height()/2;
    info->center = QPointF(x, y);
    //double x = X_DEFAULT_CENTER;
    //double y = Y_DEFAULT_CENTER;
    //qDebug()<<x;
    //qDebug()<<y;
    //qDebug()<<scene_widget->width();
    //qDebug()<<scene_widget->height();
    info->p1 = (QPointF(x - B, y));
    info->p2 = (QPointF(x - B, y + D));
    info->p3 = (QPointF(x + B, y + D));
    info->p4 = (QPointF(x + B, y));
    info->astroid = (QPolygonF());
    double phi = 0;
    double x_i, y_i;
    for (int i = 1; i < COUNT; ++i)
    {
        x_i = B * pow(sin(phi), 3) + x;
        y_i = B * pow(cos(phi), 3) + y;
        phi = 2 * M_PI * i/COUNT;
        info->astroid.append(QPointF(x_i,y_i));
    }
    phi = 0;
    for (int i = 1; i < COUNT; ++i)
    {
        x_i = R * sin(phi) + x;
        y_i = R * cos(phi) + y;
        phi = 2 * M_PI * i/COUNT;
        info->cercle.append(QPointF(x_i,y_i));
    }
    return info;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(50,50, 1000, 600);
    QFont font = this->font();
    font.setPointSize(FONT_SIZE);
    this->setFont(font);

    main_widget = new QWidget(this);
    main_widget->setMinimumSize(600,300);
    setCentralWidget(main_widget);

    main_layout = new QHBoxLayout(this);
    main_widget->setLayout(main_layout);

    // Левая колонка с управлением
    control_widget = new QControlWidget(this);
    control_widget->setFixedWidth(CONTROL_WIDGET_X);
    main_layout->addWidget(control_widget);

    scene_layout = new QVBoxLayout(this);
    // Правая часть для отрисовки
    scene_widget = new QPaintWidget(this);
    scene_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    scene_widget->setBorder(BORDER);

    ansver_text = new QLabel(this);
    ansver_text->setMaximumWidth(ANS_MAX_WIDTH);
    ansver_text->setWordWrap(true);

    main_layout->addLayout(scene_layout);
    scene_layout->addWidget(scene_widget);
    scene_layout->addWidget(ansver_text);
    scene_widget->setPainting_flag(true);
    stack = new QStack<PrintInfo *>();

    //slots and signals
    connect(this->control_widget, SIGNAL(onMoveSignal(bool)), this, SLOT(onBtnMove(bool)));
    connect(this->control_widget, SIGNAL(onScaleSignal(bool)), this, SLOT(onBtnScale(bool)));
    connect(this->control_widget, SIGNAL(onTurnSignal(bool)), this, SLOT(onBtnRot(bool)));
    connect(this->control_widget, SIGNAL(onBackSignal(bool)), this, SLOT(onBtnBack(bool)));
    connect(this->control_widget, SIGNAL(onDrawSignal(bool)), this, SLOT(onBtnDraw(bool)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onBtnMove(bool)
{

    qDebug()<<"Move";
    PrintInfo *old_info = this->scene_widget->getCurrent_info();
    stack->push(old_info);
    QPointF *point = control_widget->getMovePoint();
    PrintInfo *new_info = this->scene_widget->getCurrent_info()->Move(point);
    scene_widget->setCurrent_info(new_info);
    scene_widget->repaint();
}

void MainWindow::onBtnScale(bool)
{
    qDebug()<<"Scale";
    PrintInfo *old_info = this->scene_widget->getCurrent_info();
    stack->push(old_info);

    double kx = control_widget->getKx();
    double ky = control_widget->getKy();
    QPointF *point = control_widget->getChangePoint();
    PrintInfo *new_info = this->scene_widget->getCurrent_info()->Scale(point, kx, ky);
    scene_widget->setCurrent_info(new_info);
    scene_widget->repaint();
}

void MainWindow::onBtnRot(bool)
{
    qDebug()<<"Rotate";
    PrintInfo *old_info = this->scene_widget->getCurrent_info();
    stack->push(old_info);

    double angle = control_widget->getAngle();
    QPointF *point = control_widget->getChangePoint();
    PrintInfo *new_info = this->scene_widget->getCurrent_info()->Rotate(point, angle);
    scene_widget->setCurrent_info(new_info);
    scene_widget->repaint();
}

void MainWindow::onBtnBack(bool)
{
    PrintInfo *old_info = NULL;
    if (stack->count() > 0)
        old_info = stack->pop();
    scene_widget->setCurrent_info(old_info);
    scene_widget->repaint();
}

void MainWindow::onBtnDraw(bool)
{
    PrintInfo *info = new PrintInfo();
    info = generate_start_info(info);
    scene_widget->setCurrent_info(info);
    scene_widget->repaint();
}
