#include <iostream>
#include "PrevisionPlusProchesVoisinsNormeEuclidienne.h"
#include <QVector>

// 1. Implementation of a function which returns the Euclidean Norm

double PrevisionPlusProchesVoisinsNormeEuclidienne::Normeeuclidienne(QVector<double> const& a, QVector<double> const& b)
{
    double resultat(0);
    int const taille(a.size());
    // Creation of a difference vector between a and b
    QVector<double> difference(taille);
    for (int i(0) ; i < taille ; ++i)
    {   difference[i]= (a[i]-b[i])*(a[i]-b[i]);
    }
    for(int i(0) ; i < taille ; ++i)
    {resultat += difference[i];
    }
    return resultat;
}

// 2. Implementation of the function which returns the L nearest neighbors for a given K.
// Each subvector is made up of the distance with the last K values,
// the observation and the H observations which follow the nearest neighbor

QVector< QVector<double> > PrevisionPlusProchesVoisinsNormeEuclidienne::Lplusprochesvoisins(QVector<double> const& donnees, int k, int l, int t, int h)
{  QVector<double> kdernieres(k);
    // We separate the last K observations from the rest of the serie
    kdernieres=Isoleleskdernieres(donnees, k, t);
    QVector< QVector<double> > resultat(l, QVector<double>(2+h));
    // We create a matrix  with the L nearest neighbors,
    // in each subvector we have 1) The Euclidean distance 2) the observation 3) the H following observations
    for (int g(0) ; g < l ; ++g)
    {resultat[g][0]=10000000000;
    }
    for (int i(k-1) ; i < t-h ; ++i)
    {QVector<double> x(h+2);
        x[1]=donnees[i]; // We register the observation
        for (int g(2) ; g < h+2 ; ++g)
        {x[g]=donnees[i+g-1];
        }
        QVector<double> kvaleursprecedantsi(k);
        // For each i, we create a vector with the observation i and K-1 observations before i
        kvaleursprecedantsi=Isoleleskdernieres(donnees, k, i+1);
        // In the first column we have the Euclidean distance
        x[0]=Normeeuclidienne(kdernieres,kvaleursprecedantsi);
        if (x[0]<resultat[l-1][0]) // If the observation is nearer we replace it
        {
            resultat[l-1][0]=x[0];
            resultat[l-1][1]=x[1];
            for (int g(2) ; g < h+2 ; ++g)
            {
                resultat[l-1][g]=x[g];
            }
            resultat=Trieurtableau(resultat); // we always have to sort the matrix to have the farther nearet
            // neighbor at the end of the matrix
        }
    }
    return resultat;
}

// 3. Implementation of a function which returns the prediction for K and L given

QVector<double> PrevisionPlusProchesVoisinsNormeEuclidienne::EstimationKL(QVector<double> const& donnees, int k, int l, int t, int h)
{
    QVector<double> resultat(h);
    QVector< QVector<double> > y(l, QVector<double>(h+2));
    y=Lplusprochesvoisins(donnees, k, l, t, h);
    resultat=Moyenne(y, h);
    return resultat;
}

// 4. Implementation of the function which returns the vector (K,L) which gives the optimal prediction on the history of the serie

QVector<double> PrevisionPlusProchesVoisinsNormeEuclidienne::KLmax(QVector<double> const& donnees, int t, int h)
{
    QVector<double> resultat(3, 1000000);
    double borne(0);
    borne=t/5;   // Creation of a boundary for K and L
    int kmax(0);
    kmax = borne;
    kmax = qMin(kmax+1,11);
    kmax=qMin(kmax, t-h+1);
    // First we consider K as given
    for(int k(2) ; k < kmax; ++k)
    {
        // We create a vector which will contains the value L which maximizes the prediction for K. The
        // vector also contains the score of this estimation
        QVector<double> x(3);
        x[0]=10000000;  // We initiliaze a very high score to start the function if
        x[1]=k;
        x[2]=1;
        double lmax(0); // L must be bounded
        lmax=qMin(kmax,t-k+2-h);
        for(int l(1) ; l < lmax; ++l)
        {
            double scoreKL(0);
            // For K and L we estimate the score of such a prediction method
            // To do this, we compute the average score for predictions from all the past values
            for(int j(k+l) ; j < t-h+1 ; ++j)
            {
                QVector<double> estimationKLJ(h);
                estimationKLJ=EstimationKL(donnees, k, l, j, h);
                scoreKL += Scoreestimation(estimationKLJ, donnees, k, l, j, h);
            }
            scoreKL/=(t-k-h-l+1);
            if (scoreKL < x[0]) // We replace the former L if the estimation is better
            {
                x[0]=scoreKL;
                x[2]=l;
            }  // We get for a given K the better L and the score of the (K,L) method
        }
        if (x[0]<resultat[0]) // We replace the former vector (K,L) if the new one provides a better estimation
        {
            resultat[0]=x[0];
            resultat[1]=x[1];
            resultat[2]=x[2];
        }
    }
    return resultat;
}

// 5. Implementation of a function which returns the estimation given by the optimal vector (K,L)

QVector<double> PrevisionPlusProchesVoisinsNormeEuclidienne::Estimation(QVector<double> const& donnees, int t, int h)
{
    QVector<double> resultat(h);
    QVector<double> x(3);
    x=KLmax(donnees, t, h);
    resultat=EstimationKL(donnees, x[1], x[2], t, h);
    return resultat;
}
