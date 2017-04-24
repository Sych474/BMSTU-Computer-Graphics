#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Построение Окружностей и Эллипсов");
    w.show();

    return a.exec();
}
