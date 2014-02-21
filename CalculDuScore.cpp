#include <iostream>
#include "CalculDuScore.h"


// 1. Implementation of a function which returns the absolute value of a number

double CalculDuScore::Valeurabsolue(double a)
{
    if (a < 0)
    {
        return -a;
    }
    else
    {
        return a;
    }
}

// 2. Implementation of a function which changes the denominator when it is equal to 0

double CalculDuScore::Denominateur(double a)
{
    if (a != 0)
    {
        return a;
    }
    else
    {
        return a+0.1;
    }
}

// 3. Implementation of the distance of the score

double CalculDuScore::NormeScore(QVector<double> const& a, QVector<double> const& b)
{
    double resultat(0);
    int const taille(a.size());
    // Creation of the difference vector between a and b
    QVector<double> difference(taille);
    // We use the MAPE formula to define the norm
    for (int i(0) ; i < taille ; ++i)
    {   difference[i]= Valeurabsolue(a[i]-b[i])/Denominateur(Valeurabsolue(b[i]));
    }
    for(int i(0) ; i < taille ; ++i)
    {resultat += difference[i];
    }
    resultat /= taille; // We take the average
    return resultat;
}

// 4. Implementation of the function which returns the score of an estimation

double CalculDuScore::Scoreestimation(QVector<double> const& estimation, QVector<double> const& donnees, int k, int l, int t, int h)
{
    double resultat(0);
    QVector<double> x(h);
    // We get the vector of the H observations following T
    for (int i(0) ; i < h ; ++i)
    {   x[i]=donnees[t+i] ;
    }
    resultat=NormeScore(estimation, x);
    return resultat;
}

// 5. Implementation of the function which gives the average error of the estimation

double CalculDuScore::Erreurmoyenne(QVector<double> const& estimation, QVector<double> const& donnees, int k, int l, int t, int h)
{
    double resultat(0);
    QVector<double> x(h);
    // We get the vector of the H observations following T
    for (int i(0) ; i < h ; ++i)
    {   x[i]=donnees[t+i] ;
    }
    // We take the average of the errors
    for(int i(0); i< h; ++i)
    {
        resultat += Valeurabsolue(estimation[i]-x[i]);
    }
    resultat/=h;
    return resultat;
}
