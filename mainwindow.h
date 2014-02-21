#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "qcustomplot.h"


class MyWindow : public QWidget  //class of the program main window
{
    Q_OBJECT

public:
    MyWindow();

public slots:
    void open();                  //open a text file
    void plotGraph();             //plot the graph
    void changeMaxHorizon(int);   //the horizon can't exceed the data available for the time series

private:
    QPushButton *ouvrir;
    QPushButton *quit;
    QPushButton *generate;   //plot the graph
    QSpinBox *horizon;      //horizon in the forecast
    QSpinBox *date;        //date from which the forecast starts
    QComboBox *liste;     //choice of the norm uses in the forecast calculation
    QCustomPlot *graphe;
    QDialog *fenetre;
    QVector<double> data;   //time series data
    QLabel *path;     //path of the folder containing the time series that will be open by the user
    QHBoxLayout *openLayout;
    QLabel *pointsK;
    QLabel *pointsL;
    QLabel *score;
    QLabel *erreurmoyenne;
    int lines;     //number of lines in the text files corresponding to the number of dates in the time series
    int maxval;    //maximum value in the time series
    int minval;    //minimum value in the time series
};

#endif // MAINWINDOW_H
