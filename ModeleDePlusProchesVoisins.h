#ifndef PLUSPROCHESVOISINS_H
#define PLUSPROCHESVOISINS_H

#include "ModeleDePrevision.h"

class ModeleDePlusProchesVoisins : public ModeleDePrevision
{
    // Les méthodes :

public:
    // ModeleDePlusProchesVoisins();

    // Function which separates the K observations before T (including T) from the rest of the serie

    QVector<double> Isoleleskdernieres(QVector<double> const& x, int k, int t);

    // Function which sorts matrix in a decreasing way

    QVector<QVector<double> > Trieurtableau(QVector<QVector<double> > tableau);

    // Function which provides the average of the L nearest neighbors for the H predictions

    QVector<double> Moyenne(QVector< QVector<double> > const& m, int h);

};

#endif // PLUSPROCHESVOISINS_H
