#include <QApplication>
#include "mainwindow.h"
#include <QVector>
#include <QLineEdit>
#include <QFormLayout>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MyWindow myWin;
    myWin.show();
    return app.exec();
}
