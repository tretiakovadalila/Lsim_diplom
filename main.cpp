#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle(QString::fromLocal8Bit("Моделирование работы РЛС в метеообразованиях"));
    //w.setWindowTitle("Моделирование работы РЛС в метеообразованиях");
    w.show();
    return a.exec();
}
