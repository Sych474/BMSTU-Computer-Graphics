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
#include <QGroupBox>
#include <QRadioButton>

#include <QMainWindow>

#include "qpaintwidget.h"
#include "qlabeledit.h"
#include "qcoordswidget.h"
#include "qcolorwidget.h"
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
    QWidget *control_widget;

    //Control
    QVBoxLayout *control_layout;

    //Colors
    QGroupBox *group_colors;
    QVBoxLayout *layout_colors;
    QColorWidget *color_fill;
    QColorWidget *color_sep;
    QColorWidget *color_face;

    QLabel *lbl_color_fill;
    QLabel *lbl_color_sep;
    QLabel *lbl_color_face;


    //Poligon Input
    QGroupBox *group_input;
    QVBoxLayout *layout_input;
    QCoordsWidget *cw_point;
    QLabelEdit *edit_separator_x;

    QPushButton *btn_set_separator;
    QPushButton *btn_next_point;
    QPushButton *btn_close_poligon;

    //Paint
    QGroupBox *group_paint;
    QVBoxLayout *layout_paint;
    QPushButton *btn_fill;
    QPushButton *btn_step_fill;
    QPushButton *btn_clear;

    //info
    bool new_poligon = true;
    bool shift_pressed = false;
    bool ctrl_pressed = false;
    QPoint prev_point;
    QPoint start_point;

private:
    void updateInfo(void);
    void CreatePoligonInputGroup(void);
    void CreatePaintGroup(void);
    void CreateSettingsGroup(void);
    void setPoint(const QPoint &point);
    void closePoligon();
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onClickedBtnPaint(bool);
    void onClickedBtnStepPaint(bool);
    void onClickedBtnSetPoint(bool);
    void onClickedBtnClosePoligon(bool);
    void onClickedBtnSetSeparator(bool);

    void onClickedBtnClear(bool);
    void onFillColorChanges(const QColor &color);
    void onFaceColorChanges(const QColor &color);
    void onSepColorChanges(const QColor &color);

protected:
    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

private:
    Ui::MainWindow *ui;

public slots:

};

#endif // MAINWINDOW_H
