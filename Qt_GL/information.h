#ifndef INFORMATION_H
#define INFORMATION_H
#include <QtWidgets>
#include <QComboBox>
#include <QVBoxLayout>



class Information : public QWidget
{
    Q_OBJECT

public:
    Information();

public slots:
    void treatData(std::vector<double> data); //Recoit les données et adapte la liste de QLabel en appelant actuData

private:
    std::vector<QLabel*> list;

    QString theta = QChar(0xb8, 0x03);
    QString psi = QChar(0xc8, 0x03);
    QString phi = QChar(0xc6, 0x03);

    double maxSpeed, maxAlt;


    void actuData(std::vector<double> data); //Actualise les QLabel
};

#endif // INFORMATION_H
