#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>
#include "glwidget.h"
#include "information.h"
#include <QGridLayout>
#include <QPushButton>


class Mainwindow : public QMainWindow
{
    Q_OBJECT

public:
    Mainwindow();

signals:
   void delClicked(size_t id); //est lié a GLWidget::delToupie et supprime donc une toupie quand est emis

public slots:
    void fullWindow(); //Active desactive le mode plein ecran
    void newInfo(); //Affiche une nouvelle fenetre Information


private:
    GLWidget* w;
    QGridLayout* layout;

    Information* dataScreen;
    bool windowsState;
};

#endif // MAINWINDOW_H
