#ifndef PARSER_H
#define PARSER_H
#include<limits>
#include<iostream>
#include<QVector>
#include <QFile>
#include <QTextStream>
#include <QtWidgets/QApplication>
#include <QTextEdit>
#include <vector>
#include <QString>

class Parser
{
    // Les méthodes :

public :

    // Return the number of lines of a text file (consequently, the number of observations of the serie)

    int Nombredeligne (QString nomdufichier);

    // Function which reads a text file and registers the figures in a vector

    QVector <double> Lecteur (QString nomdufichier);

    // Function which returns the maximum of the series values given by the source folder

    int MaxValue(QString foldername);

    // Function which returns the minimum of the series values given by the source folder

    int MinValue(QString foldername);
};

#endif // PARSER_H
