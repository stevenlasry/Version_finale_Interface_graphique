#ifndef MODELEDEPREVISION_H
#define MODELEDEPREVISION_H

#include "CalculDuScore.h"

class ModeleDePrevision
{
    // Les méthodes :

public:

    // Return the absolute value of a number

    double Valeurabsolue(double a);

    // Function which returns the score of an estimation

    double Scoreestimation(QVector<double> const& estimation, QVector<double> const& donnees, int k, int l, int t, int h);

    // Return the average error of the estimation

    double Erreurmoyenne(QVector<double> const& estimation, QVector<double> const& donnees, int k, int l, int t, int h);

    // Déclaration des getters

    QVector<double> Get_donnees();
    int Get_h();
    int Get_t();

    // Déclaration des setters

    void Set_donnees(QVector<double>);
    void Set_h(int);
    void Set_t(int);

    // Les champs :

private :

    // An object from the class CalculDuScore

    CalculDuScore m_calculduscore;

    // The data

    QVector <double> _donnees;

    // The prediction horizon

    int _h;

    // The moment when prediction starts

    int _t;
};

#endif // MODELEDEPREVISION_H
