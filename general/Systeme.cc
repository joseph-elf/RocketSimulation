#include "Systeme.h"
//constructeur
Systeme::Systeme(SupportADessin* vue) :
    Dessinable(vue), rocket(new Fusee)
{
    srand (time(NULL));
}

Systeme::~Systeme(){
}

void Systeme::dessine()
{ support->dessine(*this);}


void Systeme::evolue(double dt, double temps){
    tempsSysteme=temps;
    rocket->EulerCromer(dt, temps);
    //if (temps > 12) rocket->boom();

    if(trace){
        rocket->recordTrace();
    }
}

//########################################################################################"


double Systeme::random(double min, double max){
    return min + fmod(1./1000. * rand(), max-min);
}

std::vector<double> Systeme::getData(){
    std::vector<double> retour;
    retour.push_back(tempsSysteme);
    retour.push_back(rocket->get_vect_P()[0]);
    retour.push_back(rocket->get_vect_P()[1]);
    retour.push_back(rocket->get_vect_P()[2]);
    retour.push_back(rocket->get_vect_dP()[0]);
    retour.push_back(rocket->get_vect_dP()[1]);
    retour.push_back(rocket->get_vect_dP()[2]);

    retour.push_back(rocket->get_vect_A()[0]);
    retour.push_back(rocket->get_vect_A()[1]);
    retour.push_back(rocket->get_vect_A()[2]);

    retour.push_back(rocket->masse(tempsSysteme));



    return retour;
}

//###############################################################################################
