#include "ModeleDePlusProchesVoisins.h"

// 1. Implementation of the function which separates the K observations before T (including T)
// from the rest of the serie

QVector<double> ModeleDePlusProchesVoisins::Isoleleskdernieres(QVector<double> const& x, int k, int t)
{
    QVector<double> resultat(k);
    // We get the last K observation onto a vector

    for (int i(0) ; i < k ; ++i)
    {   resultat[i]= x[t-k+i];
    }
    return resultat;
}

// 2. Implementation of a function which sorts matrix in a decreasing way

QVector< QVector<double> > ModeleDePlusProchesVoisins::Trieurtableau(QVector< QVector<double> > matrice)
{
    int taille(matrice.size());
    int taillevecteursecondaire(matrice[0].size());
    QVector<double> t(taillevecteursecondaire);
    for(int i(1) ; i < taille ; ++i)
    {
        // We compare the observations in succession

        for(int j(taille-1) ; j >=i ; --j)
        {
            if(matrice[j - 1][0] > matrice[j][0]) {
                t = matrice[j - 1]; // If required we exchange the oservations
                matrice[j - 1]= matrice[j];
                matrice[j] = t; // We need to change also the secondary vector
            }
        }
    }
    return matrice;
}

// 3. Implementation of the function which provides the average of the L nearest neighbors for the H predictions

QVector<double> ModeleDePlusProchesVoisins::Moyenne(QVector< QVector<double> > const& m, int h)
{
    QVector<double> resultat(h);
    for(int j(0); j<h; ++j)
    {
        double previsionj(0);
        for(int i(0); i<m.size(); ++i)
        {
            previsionj += m[i][j+2];
        }
        previsionj/=m.size(); // We compute each prediction as the average of the nearest neighbors
        resultat[j]=previsionj; // We put the predictions into a vector
    }
    return resultat;
}
