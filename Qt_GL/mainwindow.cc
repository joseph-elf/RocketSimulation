#include "mainwindow.h"

Mainwindow::Mainwindow()
{


    windowsState = false;
    w = new GLWidget;
    w->setFocusPolicy(Qt::StrongFocus);
    layout = new QGridLayout;
    layout->addWidget(w,0,0,3,4);

    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);


    QObject::connect(w, SIGNAL(fullWindow()), this, SLOT(fullWindow()));
    QObject::connect(w, SIGNAL(closeAll()), this, SLOT(close()));



       /*QMenu* info = menuBar()->addMenu("Informations");
       QAction* openInfo = new QAction("Fenetre d'information");
       info -> addAction(openInfo);
       QObject::connect(openInfo, SIGNAL(triggered()), this, SLOT(newInfo()));*/


    newInfo();
    this->move(0,0);
    this->showMaximized();
}


void Mainwindow::newInfo(){

    dataScreen = new Information;
    layout->addWidget(dataScreen, 0,4,1,1);
    QObject::connect(w, SIGNAL(sendEverySecond(std::vector<double>)), dataScreen, SLOT(treatData(std::vector<double>)));
    QObject::connect(w, SIGNAL(closeAll()), dataScreen, SLOT(close()));
}

void Mainwindow::fullWindow(){
    if(!windowsState)
    {showFullScreen();}
    else
    {showNormal();}
    windowsState = !windowsState;
}

