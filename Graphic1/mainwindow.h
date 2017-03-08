#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QGraphicsScene>
#include <QHBoxLayout>
#include <QLabel>
#include <QGraphicsView>
#include <QMainWindow>
#include <QDebug>
#include <QFont>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPushButton>
#include "qlabeledit.h"
#include "qpaintwidget.h"
#include "qcoordswidget.h"
#include "qcontrolwidget.h"
#include "math_lib.h"
#include "config.h"
#include "treangleinfo.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *main_widget;
    QPaintWidget *scene_widget;
    QWidget *ansver_widget;
    QControlWidget *control_widget;
    QHBoxLayout *main_layout;
    QVBoxLayout *scene_layout;
    QGraphicsScene *scene;
    QGraphicsView *gv;
    QLabel *ansver_text;
    Ui::MainWindow *ui;

public slots:
    void on_clicked_btn_run(bool);
};

#endif // MAINWINDOW_H
