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
#include "printinfo.h"
#include "math.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QWidget *main_widget;
    QPaintWidget *scene_widget;
    QHBoxLayout *main_layout;
    QVBoxLayout *scene_layout;
    QLabel *ansver_text;
    QPaintWidget *paint_widget;
    QControlWidget *control_widget;
    QStack<PrintInfo *> *stack;
private:
    PrintInfo *generate_start_info(PrintInfo *);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;

public slots:
    void onBtnMove(bool);
    void onBtnScale(bool);
    void onBtnRot(bool);
    void onBtnBack(bool);
    void onBtnDraw(bool);
};

#endif // MAINWINDOW_H
