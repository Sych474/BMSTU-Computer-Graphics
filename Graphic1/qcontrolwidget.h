#ifndef QCONTROLWIDGET_H
#define QCONTROLWIDGET_H

#define ITEMWIDTH 40
#define BTN_RUN_MAX_WIDTH 50


#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QMap>
#include "qcoordswidget.h"
#include "config.h"
#include "math_lib.h"
#include <float.h>

class QControlWidget : public QWidget
{
    Q_OBJECT
private:
    //widgets and layouts
    QLabel *label_list;
    QListWidget *list;
    QVBoxLayout *main_layout;
    QGridLayout *button_layout;
    QPushButton *btn_add;
    QPushButton *btn_del;
    QPushButton *btn_del_all;
    QGroupBox *group_box;
    //information
    QMap<QListWidgetItem *,QCoordsWidget *> map;
    std::vector<Point *> points;
private:
    void createItem(double x = 0.0, double y = 0.0);
    void updateListNums(void);
    void updateInfo(void);
    QCoordsWidget *getCoordsWidget(int);
    void get_points_list(void);
    void btn_run_enabeled(void);

public:
    QPushButton *btn_run;
    explicit QControlWidget(QWidget *parent = 0);
    int getListLen(void);
    struct Treangle *getTreangle(void);


signals:

public slots:
    void on_clicked_btn_add(bool);
    void on_clicked_btn_del(bool);
    void on_clicked_btn_del_all(bool);

};

#endif // QCONTROLWIDGET_H
