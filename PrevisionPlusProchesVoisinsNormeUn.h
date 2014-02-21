#ifndef PrevisionPlusProchesVoisinsNORMEUN_H
#define PrevisionPlusProchesVoisinsNORMEUN_H

#include "ModeleDePlusProchesVoisins.h"
#include <QVector>

class PrevisionPlusProchesVoisinsNormeUn : public ModeleDePlusProchesVoisins
{
    // Méthodes :

public :

    // Return the One Norm

    double Normeun(QVector<double> const& a, QVector<double> const& b);

    // Return the L nearest neighbors for a given K.
    // Each subvector is made up of the distance with the last K values,
    // the observation and the H observations which follow the nearest neighbor

    QVector<QVector<double> > Lplusprochesvoisins(QVector<double> const& donnees, int k, int l, int t, int h);

    // Return the prediction for K and L given

    QVector<double> EstimationKL(QVector<double> const& donnees, int k, int l, int t, int h);

    // Return the vector (K,L) which gives the optimal prediction on the history of the serie

    QVector<double> KLmax(QVector<double> const& donnees,int t, int h);

    // Return the estimation given by the optimal vector (K,L)

    QVector<double> Estimation(QVector<double> const& donnees, int t, int h);
};

#endif // PrevisionPlusProchesVoisinsNORMEUN_H
