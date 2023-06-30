#include "information.h"

Information::Information()
    :maxAlt(0.0), maxSpeed(0.0)
{
    this->resize(300, 400);
    this->move(1100, 400);
    list.push_back(new QLabel("Type : "));
    list.push_back(new QLabel("X : "));
    list.push_back(new QLabel("Y : "));
    list.push_back(new QLabel("Z : "));
    list.push_back(new QLabel("Xp : "));
    list.push_back(new QLabel("Yp : "));
    list.push_back(new QLabel("Zp : "));
    list.push_back(new QLabel("psi : "));
    list.push_back(new QLabel("theta : "));
    list.push_back(new QLabel("phi : "));
    list.push_back(new QLabel("Masse : "));
    list.push_back(new QLabel("AltMax : "));
    list.push_back(new QLabel("Vitesse-Max : "));







    QVBoxLayout* box = new QVBoxLayout;
    for (size_t i(0); i < 13; i++) {
        box->addWidget(list[i]);
    }
    this->setLayout(box);

}



void Information::actuData(std::vector<double> data){  
    list[0]->setText("Time : " + QString::number(data[0]));
    list[1]->setText("X : " + QString::number(data[1]));
    list[2]->setText("Y : " + QString::number(data[2]));
    list[3]->setText("Z : " + QString::number(data[3]));
    list[4]->setText("Xp : " + QString::number(data[4]));
    list[5]->setText("Yp : " + QString::number(data[5]));
    list[6]->setText("Zp : " + QString::number(data[6]));
    list[7]->setText("psi : " + QString::number(data[7]));
    list[8]->setText("theta : " + QString::number(data[8]));
    list[9]->setText("phi : " + QString::number(data[9]));
    list[10]->setText("Masse : " + QString::number(data[10]));

    if(data[3] > maxAlt){
        list[11]->setText("AltMax : " + QString::number(data[3]));
        maxAlt = data[3];
    }

    if(sqrt(data[4]*data[4] + data[5]*data[5] + data[6]*data[6]) > maxSpeed){
        maxSpeed = sqrt(data[4]*data[4] + data[5]*data[5] + data[6]*data[6]);
        list[12]->setText("Vitesse-Max : " + QString::number(maxSpeed));
    }



}

void Information::treatData(std::vector<double> data){
    actuData(data);
}
