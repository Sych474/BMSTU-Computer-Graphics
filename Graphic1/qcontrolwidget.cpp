#include "qcontrolwidget.h"

void QControlWidget::createItem(double x, double y)
{

    QCoordsWidget *cw = new QCoordsWidget(this);

    cw->setLabelText(QString::number(map.count()+1)+")");
    cw->setX(x);
    cw->setY(y);

    QListWidgetItem *item = new QListWidgetItem(list);
    item->setSizeHint(QSize(ITEMWIDTH, cw->sizeHint().height()));
    list->setItemWidget(item,cw);
    map.insert(item, cw);

}

void QControlWidget::updateListNums()
{
    for (int i = 0; i < map.count(); ++i)
    {
        QCoordsWidget *widget = this->getCoordsWidget(i);
        if (!widget)
            break;
        widget->setLabelText(QString::number(i+1)+")");
    }
}

void QControlWidget::updateInfo()
{

}

QCoordsWidget *QControlWidget::getCoordsWidget(int row)
{
    QListWidgetItem *item = list->item(row);
    if (!item)
        return NULL;
    return map.value(item);
}

void QControlWidget::get_points_list()
{
    for (int i = 0; i < map.count(); ++i)
    {
        QCoordsWidget *widget = this->getCoordsWidget(i);
        if (!widget)
            break;
        Point *p = new Point(widget->getX(), widget->getY());
        points.push_back(p);
        qDebug()<<p->x<<p->y;
    }
}

void QControlWidget::btn_run_enabeled()
{
    if (map.size() >= 3)
        btn_run->setEnabled(true);
    else
        btn_run->setEnabled(false);
}

QControlWidget::QControlWidget(QWidget *parent) : QWidget(parent)
{
    //creating
    label_list = new QLabel("Список точек:");
    main_layout = new QVBoxLayout(this);
    //group_box = new QGroupBox(tr("Control"),this);
    list = new QListWidget(this);
    button_layout = new QGridLayout(this);
    btn_add = new QPushButton(tr("Добавить"), this);
    btn_del = new QPushButton(tr("Удалить"), this);
    btn_del_all = new QPushButton(tr("Очистить"), this);
    btn_run = new QPushButton(tr("Рассчитать и построить"), this);
    btn_run->setEnabled(false);

    //setting main_layout of widget
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    list->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setLayout(main_layout);
    //group_box->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //group_box->setLayout(main_layout);

    //button layout
    button_layout->addWidget(btn_add, 0,0);
    button_layout->addWidget(btn_del, 0,1);
    button_layout->addWidget(btn_del_all, 0,2);
    button_layout->addWidget(btn_run, 1, 0, 1, 3);
    //btn_run->setFixedWidth(BTN_RUN_MAX_WIDTH);

    //adding to main_layout
    main_layout->addWidget(label_list);
    main_layout->addWidget(list);
    main_layout->addLayout(button_layout);

    //slots and signals
    connect(this->btn_add, SIGNAL(clicked(bool)), this, SLOT(on_clicked_btn_add(bool)));
    connect(this->btn_del, SIGNAL(clicked(bool)), this, SLOT(on_clicked_btn_del(bool)));
    connect(this->btn_del_all, SIGNAL(clicked(bool)), this, SLOT(on_clicked_btn_del_all(bool)));
}

int QControlWidget::getListLen()
{
    return map.count();
}

Treangle *QControlWidget::getTreangle()
{
    points.clear();
    get_points_list();
    Treangle *ans = new Treangle();
    double min = FLT_MAX;
    double tmp;
    for (int i = 0; i < points.size(); ++i)
        for (int j = i+1; j < points.size(); ++j)
            for (int k = j+1; k < points.size(); ++k)
                if (is_triangle(points[i], points[j], points[k]))
                {
                    tmp = get_min_bisector(points[i], points[j], points[k]);
                    if (min > tmp)
                    {
                        min = tmp;
                        ans->p1 = *(points[i]);
                        ans->p2 = *(points[j]);
                        ans->p3 = *(points[k]);
                    }
                }

    if (!is_triangle(&(ans->p1), &(ans->p2), &(ans->p3)))
    {
        delete ans;
        return NULL;
    }
    return ans;
}


void QControlWidget::on_clicked_btn_add(bool)
{
    this->createItem();
    btn_run_enabeled();
}

void QControlWidget::on_clicked_btn_del(bool)
{
    QModelIndex index = list->currentIndex();
    if (!index.isValid())
    {
        QMessageBox::warning(this, "Message", "Точка не выбрана");
    }
    if (QListWidgetItem *item = list->takeItem(index.row()))
    {
        map.remove(item);
        delete item;
    }
    //else
        //cant do it
    updateListNums();
    btn_run_enabeled();
}

void QControlWidget::on_clicked_btn_del_all(bool)
{
    list->clear();
    map.clear();
    btn_run_enabeled();
}

