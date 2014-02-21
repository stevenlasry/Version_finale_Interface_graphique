#include <iostream>
#include "ModeleDePrevision.h"
#include "CalculDuScore.h"


// 1. Implementation of a function which returns the absolute value of a number

double ModeleDePrevision::Valeurabsolue(double a)
{
    double resultat;
    resultat = m_calculduscore.Valeurabsolue(a); // We use the instance of CalculDuScore
    return resultat;
}

// 2. Implementation of the function which returns the score of an estimation

double ModeleDePrevision::Scoreestimation(QVector<double> const& estimation, QVector<double> const& donnees, int k, int l, int t, int h)
{
    double resultat;
    resultat = m_calculduscore.CalculDuScore::Scoreestimation(estimation, donnees, k, l, t, h); // We use the instance of CalculDuScore
    return resultat;
}

// 3. Implementation of the function which gives the average error of the estimation

double ModeleDePrevision::Erreurmoyenne(QVector<double> const& estimation, QVector<double> const& donnees, int k, int l, int t, int h)
{
    double resultat;
    resultat = m_calculduscore.CalculDuScore::Erreurmoyenne(estimation, donnees, k, l, t, h); // We use the instance of CalculDuScore
    return resultat;
}

// Définition des getters

QVector<double> ModeleDePrevision::Get_donnees()
{
    return _donnees;
}

int ModeleDePrevision::Get_h()
{
    return _h;
}

int ModeleDePrevision::Get_t()
{
    return _t;
}

// Définition des setters

void ModeleDePrevision::Set_donnees(QVector<double> donnees)
{
    _donnees = donnees;
}

void ModeleDePrevision::Set_h(int h)
{
    _h = h;
}

void ModeleDePrevision::Set_t(int t)
{
    _t = t;
}
