#include <QApplication>
#include <QIcon>
#include "mainwindow.h"
#include "qcustomplot.h"

#include <QVector>
#include <QFile>
#include <QString>
#include <QTextStream>
#include <QTextEdit>

#include "PrevisionPlusProchesVoisinsNormeEuclidienne.h"
#include "PrevisionPlusProchesVoisinsNormeUn.h"
#include "Parser.h"

MyWindow::MyWindow()
{
    lines = 500;    //lines is initialized at 500 before the open button is clicked

    // Creation of layouts and widgets
    // Group : File Opening
    ouvrir = new QPushButton("&Ouvrir");  //the name open is already used for the the slot to open text files
    openLayout = new QHBoxLayout;
    openLayout->setAlignment(Qt::AlignLeft);
    openLayout->addWidget(ouvrir);
    path = new QLabel(this);
    path->setText("   Veuillez sélectionner un fichier texte");
    QFont* font = new QFont("Sans Serif");
    font->setItalic(true);
    path->setFont(*font);
    openLayout->addWidget(path);
    QGroupBox *groupOpen = new QGroupBox("Ouverture du fichier source contenant la série temporelle");
    groupOpen->setObjectName("openBox");
    groupOpen->setStyleSheet("QGroupBox#openBox { font-weight:bold }");  //the Group Box title is put in bold
    groupOpen->setLayout(openLayout);

    // Groupe : Parameters
    date = new QSpinBox(this);
    date->setAccelerated(true);
    date->setMinimum(1);  //to avoid starting at 0 which makes no sense and makes the program crash
    horizon = new QSpinBox(this);
    horizon->setAccelerated(true);
    horizon->setMinimum(1);  //to avoid starting at 0 which makes no sense and makes the program crash
    QFormLayout *definitionLayout = new QFormLayout;
    definitionLayout->addRow("&Date de début de prévision :", date);
    definitionLayout->addRow("&Horizon :", horizon);
    QGroupBox *groupDefinition = new QGroupBox("Paramètres de la prévision");
    groupDefinition->setObjectName("paramBox");
    groupDefinition->setStyleSheet("QGroupBox#paramBox { font-weight:bold }"); //the Group Box title is put in bold
    groupDefinition->setLayout(definitionLayout);

    // Groupe : Méthode d'estimation
    liste = new QComboBox;
    liste->addItem("Norme 1");
    liste->addItem("Norme 2");
    QFormLayout *methodeLayout = new QFormLayout;
    methodeLayout->addRow("Méthode des plus proches &voisins :", liste);
    QGroupBox *groupMethod = new QGroupBox("Méthodes d'estimation");
    groupMethod->setObjectName("ForecastBox");
    groupMethod->setStyleSheet("QGroupBox#ForecastBox { font-weight:bold }");  //the Group Box title is put in bold
    groupMethod->setLayout(methodeLayout);

    // Layout : bottom buttons
    generate = new QPushButton("Tracer la &prévision");  //the button that will draw the forecast
    quit = new QPushButton("&quit");                     //this button will quit the program
    QHBoxLayout *boutonsLayout = new QHBoxLayout;
    boutonsLayout->setAlignment(Qt::AlignRight);
    boutonsLayout->addWidget(generate);
    boutonsLayout->addWidget(quit);

    // Definition of main layout, window title, icon and size
    QVBoxLayout *layoutPrincipal = new QVBoxLayout;
    layoutPrincipal->addWidget(groupOpen);
    layoutPrincipal->addWidget(groupDefinition);
    layoutPrincipal->addWidget(groupMethod);
    layoutPrincipal->addLayout(boutonsLayout);
    setLayout(layoutPrincipal);
    setWindowTitle("Prévision Séries Temporelles");
    setWindowIcon(QIcon("icone.png"));
    resize(350, 300);  //the initial size of the main window. It will me modifiable

    // Connexions of signals  slots
    connect(ouvrir, SIGNAL(clicked()), this, SLOT(open()));
    connect(quit, SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(generate, SIGNAL(clicked()), this, SLOT(plotGraph()));
    connect(date, SIGNAL(valueChanged(int)), this, SLOT(changeMaxHorizon(int))); //adjust the maximum for horizon when date (start of forecast) is changed
}

void MyWindow::open()
{
    QString fichier = QFileDialog::getOpenFileName(this, "Ouvrir un fichier",QString(), "Text Files (*.txt)");
    QMessageBox::information(this, "Fichier", "Vous avez sélectionné :\n" + fichier);
    path->setText(QFileInfo(fichier).fileName());
    openLayout->addWidget(path);
    Parser parser;
    lines = parser.Nombredeligne(fichier);
    date->setMaximum(lines);   //date can't exceed the number of values of the time series selected
    data = parser.Lecteur(fichier);
    maxval = parser.MaxValue(fichier);
    minval = parser.MinValue(fichier);
}

void MyWindow::plotGraph()
{
    //On vérifie que le nom du fichire source n'est pas vide, sinon on arrête
    if (path->text() == "   Veuillez sélectionner un fichier texte")
    {
        QMessageBox::critical(this, "Erreur", "Veuillez sélectionner un fichier");
        return; // Arrêt de la méthode
    }
    fenetre = new QDialog(this);
    QVBoxLayout *graphLayout = new QVBoxLayout;
    QVector<double> x(lines), y(lines);
    for (int i=0; i<lines; ++i)
    {
        x[i] = i;
        y[i] = data[i];
    }
    // create graph and assign data to it:
    graphe = new QCustomPlot(fenetre);
    graphe->addGraph();
    graphe->graph(0)->setData(x, y);
    graphe->graph(0)->setName("Série temporelle donnée");
    graphe->graph(0)->setScatterStyle(QCPScatterStyle::ssDisc);
    // give the axes some labels:
    graphe->xAxis->setLabel("x");
    graphe->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    graphe->xAxis->setRange(0, lines);
    graphe->yAxis->setRange(minval-5, maxval+5);
    // graphe->graph(0)->rescaleAxes(true);
    QVector<double> x1(horizon->value()+1), y1(horizon->value()+1);
    y1[0]=data[date->value()-1];
    x1[horizon->value()] = date->value()+horizon->value()-1;
    if (liste->currentIndex() == 0)
    {
        PrevisionPlusProchesVoisinsNormeUn essai;
        QVector<double> estimate = essai.Estimation(data,date->value(),horizon->value());
        for (int j=0; j<horizon->value(); ++j)
        {
            x1[j] = j+date->value()-1;
            y1[j+1] = estimate[j]-1;
        }
        graphe->addGraph();
        QPen pen;
        pen.setStyle(Qt::DotLine);
        pen.setColor(Qt::red);   // line color red for second graph
        graphe->graph(1)->setPen(pen);
        graphe->graph(1)->setData(x1, y1);
        // let the ranges scale themselves so graph 1 fits perfectly in the visible area:
        graphe->graph(1)->rescaleAxes(true);
        graphe->graph(1)->setName("Prévision");
        graphe->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
        //  graphe->graph(1)->setPen(QPen(Qt::DotLine));
        graphe->replot();
        graphe->setFixedSize(1200,600);
        // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
        graphe->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        graphe->legend->setVisible(true);
        QFont legendFont = font();
        legendFont.setPointSize(9); // and make a bit smaller for legend
        graphe->legend->setFont(legendFont);
        graphe->legend->setBrush(QBrush(QColor(255,255,255,230)));
        // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
        graphe->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignLeft);

        graphLayout->addWidget(graphe);

        pointsK = new QLabel(this);
        pointsL = new QLabel(this);
        score = new QLabel(this);
        erreurmoyenne = new QLabel(this);
        QFormLayout *pointsLayout = new QFormLayout;
        double nbK = essai.KLmax(data,date->value(),horizon->value())[1];
        QString nbKstring = QString::number(nbK);
        pointsLayout->addRow("Nombre de points précédant la date de prévision considérés (&k) : " + nbKstring, pointsK);
        double nbL = essai.KLmax(data,date->value(),horizon->value())[2];
        QString nbLstring = QString::number(nbL);
        pointsLayout->addRow("Nombre de proches voisins considérés (&l) : " + nbLstring, pointsL);
        double nbScore = essai.Scoreestimation(estimate,data,nbK,nbL,date->value(),horizon->value());;
        QString nbScoreString = QString::number(nbScore);
        pointsLayout->addRow("Score de la prévision (MAPE : Mean Absolute Percentage Error) : " + nbScoreString, score);
        double nbErreurmoyenne = essai.Erreurmoyenne(estimate,data,nbK,nbL,date->value(),horizon->value());;
        QString nbErreurmoyenneString = QString::number(nbErreurmoyenne);
        pointsLayout->addRow("Erreur moyenne de la prévision : " + nbErreurmoyenneString, erreurmoyenne);
        graphLayout->addLayout(pointsLayout);

        fenetre->setLayout(graphLayout);
        fenetre->setWindowTitle("Représentation graphique de la série temporelle");
        fenetre->setWindowIcon(QIcon("icone.png"));
        fenetre->show();
    }
    else if (liste->currentIndex() == 1)
    {
        PrevisionPlusProchesVoisinsNormeEuclidienne essai;
        QVector<double> estimate = essai.Estimation(data,date->value(),horizon->value());

        for (int j=0; j<horizon->value(); ++j)
        {
            x1[j] = j+date->value()-1;
            y1[j+1] = estimate[j]-1;
        }
        graphe->addGraph();
        QPen pen;
        pen.setStyle(Qt::DotLine);
        pen.setColor(Qt::red);   // line color red for second graph
        graphe->graph(1)->setPen(pen);
        graphe->graph(1)->setData(x1, y1);
        // let the ranges scale themselves so graph 1 fits perfectly in the visible area:
        graphe->graph(1)->rescaleAxes(true);
        graphe->graph(1)->setName("Prévision");
        graphe->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
        graphe->replot();
        graphe->setFixedSize(1200,600);
        // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
        graphe->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        graphe->legend->setVisible(true);
        QFont legendFont = font();
        legendFont.setPointSize(9); // and make a bit smaller for legend
        graphe->legend->setFont(legendFont);
        graphe->legend->setBrush(QBrush(QColor(255,255,255,230)));
        // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
        graphe->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignLeft);
        graphLayout->addWidget(graphe);

        pointsK = new QLabel(this);
        pointsL = new QLabel(this);
        score = new QLabel(this);
        erreurmoyenne = new QLabel(this);
        QFormLayout *pointsLayout = new QFormLayout;
        double nbK = essai.KLmax(data,date->value(),horizon->value())[1];
        QString nbKstring = QString::number(nbK);
        pointsLayout->addRow("Nombre de points précédant la date de prévision considérés (&k) : " + nbKstring, pointsK);
        double nbL = essai.KLmax(data,date->value(),horizon->value())[2];
        QString nbLstring = QString::number(nbL);
        pointsLayout->addRow("Nombre de proches voisins considérés (&l) : " + nbLstring, pointsL);
        double nbScore = essai.Scoreestimation(estimate,data,nbK,nbL,date->value(),horizon->value());    ;
        QString nbScoreString = QString::number(nbScore);
        pointsLayout->addRow("Score de la prévision : " + nbScoreString, score);
        double nbErreurmoyenne = essai.Erreurmoyenne(estimate,data,nbK,nbL,date->value(),horizon->value());;
        QString nbErreurmoyenneString = QString::number(nbErreurmoyenne);
        pointsLayout->addRow("Erreur moyenne de la prévision : " + nbErreurmoyenneString, erreurmoyenne);
        graphLayout->addLayout(pointsLayout);

        fenetre->setLayout(graphLayout);
        fenetre->setWindowTitle("Représentation graphique de la série temporelle");
        fenetre->setWindowIcon(QIcon("icone.png"));
        fenetre->show();
    }
}

void MyWindow::changeMaxHorizon(int)
{
    horizon->setMaximum(lines-date->value());
}


