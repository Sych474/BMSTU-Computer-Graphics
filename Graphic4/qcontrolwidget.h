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
#include <QRadioButton>
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
    QTabWidget *tab_widget;
    QWidget *widget1;
    QWidget *widget2;
    QVBoxLayout *widget1_layout;
    QVBoxLayout *widget2_layout;

    //Colors
    QGroupBox *group_colors;
    QVBoxLayout *layout_colors;
    QColorWidget *color_fone;
    QColorWidget *color_line;
    QLabel *lbl_color_fone;
    QLabel *lbl_color_line;
    QLabelEdit *edit_pixel_size;
    QPushButton *btn_set_pixel_size;
    QRadioButton *rbn_fone_color;

    //Circle
    QGroupBox *group_cercle;
    QVBoxLayout *layout_cercle;
    QCoordsWidget *cw_cercle_center;
    QLabelEdit *edit_cercle_r;
    QPushButton *btn_draw_cercle;

    //Circle_Solar
    QGroupBox *group_circle_solar;
    QVBoxLayout *layout_circle_solar;
    QLabelEdit *edit_circle_r_beg;
    QLabelEdit *edit_circle_r_delta;
    QLabelEdit *edit_circle_count;
    QPushButton *btn_draw_circle_solar;

    //Ellipse
    QGroupBox *group_ellipse;
    QVBoxLayout *layout_ellipse;
    QCoordsWidget *cw_ellipse_center;
    QLabelEdit *edit_ellipse_a;
    QLabelEdit *edit_ellipse_b;
    QPushButton *btn_draw_ellipse;

    //Ellipse_solar
    QGroupBox *group_ellipse_solar;
    QVBoxLayout *layout_ellipse_solar;
    QLabelEdit *edit_ellipse_a_beg;
    QLabelEdit *edit_ellipse_b_beg;
    QLabelEdit *edit_ellipse_a_delta;
    QLabelEdit *edit_ellipse_count;
    QPushButton *btn_draw_ellipse_solar;

    QPushButton *btn_clear;


    //Alg
    QGroupBox *group_alg;
    QVBoxLayout *layout_alg;
    QLabel *lbl_alg;
    QComboBox *combobox_alg;
    //information
    QPaintWidget *pw = NULL;
    alg_t sellected_alg = alg_canon;
private:
    void updateInfo(void);

public:
    explicit QControlWidget(QWidget *parent = 0);

    QPaintWidget *getPw() const;
    void setPw(QPaintWidget *value);

signals:

public slots:
    void onClickedBtnDrawCircle(bool);
    void onClickedBtnDrawEllipse(bool);

    void onClickedBtnDrawCircleSolar(bool);
    void onClickedBtnDrawEllipseSolar(bool);

    void onClickedBtnClear(bool);
    void onClickedBtnSetPixelSize(bool);
    void onFoneColorChanges(const QColor &color);
    void onAlgCHange(int);
};

#endif // QCONTROLWIDGET_H
