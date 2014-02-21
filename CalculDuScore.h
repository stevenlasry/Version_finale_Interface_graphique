#ifndef CALCULDUSCORE_H
#define CALCULDUSCORE_H

#include <QVector>

class CalculDuScore
{
    // Les méthodes :
public :

    // Return the absolute value of a number

    double Valeurabsolue(double a);

    // Change the denominator when it is equal to 0

    double Denominateur(double a);

    // Define the distance we will use to compute the score

    double NormeScore(QVector<double> const& a, QVector<double> const& b);

    // Function which returns the score of an estimation

    double Scoreestimation(QVector<double> const& estimation, QVector<double> const& donnees, int k, int l, int t, int h);

    // Return the average error of the estimation

    double Erreurmoyenne(QVector<double> const& estimation, QVector<double> const& donnees, int k, int l, int t, int h);
};

#endif // CALCULDUSCORE_H
