#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(40,40, 1300, 650);
    QFont font = this->font();
    font.setPointSize(FONT_SIZE);
    this->setFont(font);

    main_widget = new QWidget(this);
    main_widget->setMinimumSize(600,300);
    setCentralWidget(main_widget);

    main_layout = new QHBoxLayout(this);
    main_widget->setLayout(main_layout);

    scene_layout = new QVBoxLayout(this);
    // Правая часть для отрисовки
    scene_widget = new QPaintWidget(this);
    scene_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    // Левая колонка с управлением
    control_widget = new QControlWidget(this);
    control_widget->setFixedWidth(CONTROL_WIDGET_X);
    control_widget->setPw(scene_widget);
    main_layout->addWidget(control_widget);


    ansver_text = new QLabel(this);
    ansver_text->setMaximumWidth(ANS_MAX_WIDTH);
    ansver_text->setWordWrap(true);

    main_layout->addLayout(scene_layout);
    scene_layout->addWidget(scene_widget);
    scene_layout->addWidget(ansver_text);

    //slots and signals


}

MainWindow::~MainWindow()
{
    delete ui;
}

