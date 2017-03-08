#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setGeometry(50, 50, 1000, 500);
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
    // Правая часть с панелью
    scene_widget = new QPaintWidget(this);
    scene_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    scene_widget->setBorder(BORDER);

    ansver_widget = new QWidget(this);
    //ansver_widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    //ansver_widget->setFixedHeight(ANSVER_WIDGET_Y);
    ansver_text = new QLabel(this);
    ansver_text->setMaximumWidth(ANS_MAX_WIDTH);
    ansver_text->setWordWrap(true);

    main_layout->addLayout(scene_layout);
    scene_layout->addWidget(scene_widget);
    scene_layout->addWidget(ansver_text);

    connect(control_widget->btn_run, SIGNAL(clicked(bool)), this, SLOT(on_clicked_btn_run(bool)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_clicked_btn_run(bool)
{
    Treangle *tr = this->control_widget->getTreangle();
    if (tr==NULL)
    {
        QMessageBox::warning(this, "Message", "It is impossible to construct a triangle!");
        qDebug()<<"No Treangle!";
        return;
    }
    TreangleInfo *tr_info = new TreangleInfo(&(tr->p1), &(tr->p2), &(tr->p3));
    this->scene_widget->setInfo(tr_info);
    this->scene_widget->setPainting_flag(true);
    this->scene_widget->update();
    this->scene_widget->draw();
    this->ansver_text->setText(tr_info->getAnsverText());
}
