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
#include <QComboBox>
#include <QMessageBox>
#include <QMap>
#include <float.h>
#include "qcoordswidget.h"
#include "qlabeledit.h"
#include "qcoordswidget.h"
#include "qcolorwidget.h"
#include "qpaintwidget.h"
#include "config.h"

class QControlWidget : public QWidget
{
    Q_OBJECT
private:
    //main
    QVBoxLayout *main_layout;

    //Colors
    QGroupBox *group_colors;
    QVBoxLayout *layout_colors;
    QColorWidget *color_fone;
    QColorWidget *color_line;
    QLabel *lbl_color_fone;
    QLabel *lbl_color_line;
    QLabelEdit *edit_pixel_size;
    QPushButton *btn_set_pixel_size;

    //Line
    QGroupBox *group_line;
    QVBoxLayout *layout_line;
    QCoordsWidget *cw_point_1;
    QCoordsWidget *cw_point_2;
    QPushButton *btn_draw_line;

    //Solar
    QGroupBox *group_solar;
    QVBoxLayout *layout_solar;
    QLabelEdit *edit_angle_delta;
    QPushButton *btn_draw_solar;\

    QPushButton *btn_clear;


    //Alg
    QGroupBox *group_alg;
    QVBoxLayout *layout_alg;
    QLabel *lbl_alg;
    QComboBox *combobox_alg;
    //information
    QMap<QListWidgetItem *,QCoordsWidget *> map;
    QPaintWidget *pw = NULL;
    alg_t sellected_alg = alg_DDA;
private:
    void updateInfo(void);

public:
    explicit QControlWidget(QWidget *parent = 0);


    QPaintWidget *getPw() const;
    void setPw(QPaintWidget *value);

signals:

public slots:
    void onClickedBtnDrawLine(bool);
    void onClickedBtnDrawSolar(bool);
    void onClickedBtnClear(bool);
    //void onClickedBtnBack(bool);
    void onClickedBtnSetPixelSize(bool);
    void onFoneColorChanges(const QColor &color);
    void onAlgCHange(int);
};

#endif // QCONTROLWIDGET_H
