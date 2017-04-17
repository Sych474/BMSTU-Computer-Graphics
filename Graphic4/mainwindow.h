#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QFont>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QDebug>
#include <QStack>

#include <QMainWindow>

#include "qpaintwidget.h"
#include "qcontrolwidget.h"
#include "config.h"
#include "math.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *main_widget;
    QHBoxLayout *main_layout;
    QVBoxLayout *scene_layout;
    QPaintWidget *scene_widget;
    QLabel *ansver_text;
    QControlWidget *control_widget;
private:

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

public slots:

};

#endif // MAINWINDOW_H
