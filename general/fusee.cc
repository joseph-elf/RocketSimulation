#include "fusee.h"

Fusee::Fusee()
    :Integrable(), rayon(0.05), hauteur(1.7), distanceGP(0.5), Ctrainee(0.3), densiteAir(1.292), sAileron(0.1),
      tempsCombustion(2.0), rayonP(1.5),parachute(false), motor(true), vent(3)
{
}

Fusee::Fusee(std::vector<double>data, double r, double h, double GP)
    :Integrable(data), rayon(r), hauteur(h), distanceGP(GP), Ctrainee(1.0), densiteAir(1.0), sAileron(1.0), rayonP(1.0),parachute(false)
{}

double Fusee::forceFrot(Vecteur vitesse, Vecteur angle ,Vecteur vitesseAng) const{
    if(!parachute)
    return 0.5 * Ctrainee * densiteAir * surface(angleVitesse()) * sqrt(vitesse[0]*vitesse[0]  +  vitesse[1]*vitesse[1]  +  vitesse[2]*vitesse[2] );

    return 0.5 * Ctrainee * densiteAir * (surface(angleVitesse()) + pi * rayonP * rayonP) * sqrt(vitesse[0]*vitesse[0]  +  vitesse[1]*vitesse[1]  +  vitesse[2]*vitesse[2]);
}
double Fusee::forceG(double temps) const{
    return masse(temps) * g;
}
double Fusee::forceMoteur(double temps) const{
    if(motor) return 1000.0;
    return 0.0;
}

double Fusee::masse(double temps) const{
    if(temps < tempsCombustion)
        return 10.0 - 2.0/tempsCombustion * temps;
    return 8.0;
}

bool Fusee::fire(double temps){
    if(motor)return true;
    return false;
}

double Fusee::surface(double angle) const{
    return (2.0* rayon * hauteur + sAileron) * abs(sin(angle)) + (rayon*rayon * pi) * abs(cos(angle));
}
double Fusee::I(double temps) const{
    return masse(temps) * (0.25*rayon*rayon + 0.083333 * hauteur*hauteur);
}

Vecteur Fusee::eq_evolutionXYZ(std::vector<Vecteur> position, std::vector<Vecteur> angle, double temps) const{
    Vecteur retour(3);
    retour[0] = (forceMoteur(temps) * sin(angle[0][1]) - forceFrot(position[1],angle[0], angle[1])* position[1][0])/masse(temps)  ;
    retour[2] = (forceMoteur(temps) * cos(angle[0][1]) - forceFrot(position[1],angle[0], angle[1])* position[1][2] - forceG(temps) ) /masse(temps)  ;

    return retour;
}

Vecteur Fusee::eq_evolutionAngle(std::vector<Vecteur> position, std::vector<Vecteur> angle, double temps) const{

    Vecteur retour(3);
    /*if(position[0].norme() <3.0)
        return retour;*/
    retour[1] = (-forceFrot(position[1], angle[0], angle[1]) * distanceGP * (position[1][2] * sin(angle[0][1]) - position[1][0] * cos(angle[0][1])) -  signeof(angle[1][1])*(0.25 * sAileron + 0.666*rayon*hauteur)*densiteAir*Ctrainee*hauteur*hauteur*angle[1][1]*angle[1][1] )/I(temps);
    return retour;
}


double Fusee::angleVitesse() const{

    if(abs(PositionXYZ[1][0]) < epsilon && abs(PositionXYZ[1][1]) < epsilon && abs(PositionXYZ[1][2]) < epsilon)
        return 0.0;
    if(PositionXYZ[1][2] < 0)
    return asin(-PositionXYZ[1][0] / sqrt(PositionXYZ[1][0]*PositionXYZ[1][0] + PositionXYZ[1][1]*PositionXYZ[1][1] + PositionXYZ[1][2]*PositionXYZ[1][2]));

    return pi-asin(-PositionXYZ[1][0] / sqrt(PositionXYZ[1][0]*PositionXYZ[1][0] + PositionXYZ[1][1]*PositionXYZ[1][1] + PositionXYZ[1][2]*PositionXYZ[1][2]));
}
int Fusee::signeof(double x) const{
    if(x>0)return 1;
    return -1;
}
//traces
Vecteur Fusee::GCCarthesien(){
    return Vecteur(-distanceGP * sin(THETA) * cos(PSI), -distanceGP * sin(THETA) * sin(PSI), -distanceGP * cos(THETA));
}
Vecteur Fusee::wCarthesien(){
    return Vecteur(THETAP*cos(PSI), THETAP*sin(PSI), PSIP);
}
Vecteur Fusee::vitesseC(){
    return PositionXYZ[1]+vent + wCarthesien()^GCCarthesien();
}
