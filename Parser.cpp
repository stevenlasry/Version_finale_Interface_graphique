#include <QFile>
#include <QString>
#include <QTextStream>
#include <QtWidgets/QApplication>
#include <QTextEdit>
#include "Parser.h"

// 1. Implementation of a function which returns the number of lines of a text file

int Parser::Nombredeligne (QString nomdufichier)
{
    int resultat(0);
    QString texte;
    QFile fichier(nomdufichier);

    // Reading the file
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {   QTextStream flux(&fichier);
        while (!flux.atEnd())
        {
            texte = flux.readLine();
            resultat++;
        }
        fichier.close();
    }
    return resultat;
}

// 2. Implementation of the unction which reads a text file and registers the figures in a vector

QVector <double> Parser::Lecteur(QString nomdufichier)
{
    QFile fichier(nomdufichier);
    int lignes(0);
    // First we get the number of lines
    lignes = Nombredeligne(nomdufichier);
    // We create our data vector
    QVector <double> resultat(lignes);
    if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
    {   QTextStream flux(&fichier);
        // We register the obsevations into the data vector
        for (int i(0) ; i < lignes ; i++)
        {flux >> resultat[i];
        }
        fichier.close();
    }
    return resultat;
}

// 3. Implementation of a function which returns the maximum of the series values given by the source file

int Parser::MaxValue(QString foldername)
{
    int max(0);
    double number(0);
    QString text;
    QFile folder(foldername);
    if(folder.open(QIODevice::ReadOnly | QIODevice::Text))
    {   QTextStream flux(&folder);
        while (!flux.atEnd())
        {
            text = flux.readLine();
            number = text.split(" ")[0].toDouble();
            if (number > max) max = number;
        }
        folder.close();
    }
    return max;
}

// 4. Implementation of a function which returns the minimum of the series values given by the source file

int Parser::MinValue(QString foldername)
{
    int min(0);
    double number(0);
    QString text;
    QFile folder(foldername);
    if(folder.open(QIODevice::ReadOnly | QIODevice::Text))
    {   QTextStream flux(&folder);
        while (!flux.atEnd())
        {
            text = flux.readLine();
            number = text.split(" ")[0].toDouble();
            if (number < min) min = number;
        }
        folder.close();
    }
    return min;
}
