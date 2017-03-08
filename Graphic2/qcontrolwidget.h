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
#include <QFormLayout>
#include <QMessageBox>
#include <QMap>
#include "qcoordswidget.h"
#include "qlabeledit.h"
#include "qcoordswidget.h"
#include "config.h"
#include <float.h>

class QControlWidget : public QWidget
{
    Q_OBJECT
private:
    //widgets and layouts
    QVBoxLayout *main_layout;

    //move
    QGroupBox *group_move;
    QFormLayout *move_layout;
    QLabelEdit *dx_edit;
    QLabelEdit *dy_edit;
    QPushButton *btn_move;

    //change
    QGroupBox *group_change;
    QLabelEdit *kx_edit;
    QLabelEdit *ky_edit;
    QLabelEdit *angle_edit;
    QCoordsWidget *point_edit;
    QPushButton *btn_turn;
    QPushButton *btn_scale;
    QFormLayout *change_layout;


    QPushButton *btn_back;
    QPushButton *btn_draw;
    //information
    QMap<QListWidgetItem *,QCoordsWidget *> map;
private:
    void updateInfo(void);
    QCoordsWidget *getCoordsWidget(int);

public:
    explicit QControlWidget(QWidget *parent = 0);
    QPointF *getMovePoint(void);
    double getAngle(void);
    double getKx(void);
    double getKy(void);
    QPointF *getChangePoint(void);

signals:
    void onMoveSignal(bool);
    void onScaleSignal(bool);
    void onTurnSignal(bool);
    void onBackSignal(bool);
    void onDrawSignal(bool);
public slots:
    void onClickedBtnMove(bool);
    void onClickedBtnScale(bool);
    void onClickedBtnTurn(bool);
    void onClickedBtnBack(bool);
    void onClickedBtnDraw(bool);
};

#endif // QCONTROLWIDGET_H
