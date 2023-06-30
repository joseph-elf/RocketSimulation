#ifndef FUSEE_H
#define FUSEE_H
#include "Integrable.h"
#include "bases/Vecteur.h"
#include "Memoire.h"
#include <cmath>
#define PSI (Orientation[0][0])
#define THETA (Orientation[0][1])
#define PHI (Orientation[0][2])
#define PSIP (Orientation[1][0])
#define THETAP (Orientation[1][1])
#define PHIP (Orientation[1][2])



class Fusee : public Integrable
{
public:
    Fusee();
    Fusee(std::vector<double>data, double rayon, double hauteur, double GP);




    virtual Vecteur eq_evolutionXYZ(std::vector<Vecteur> position, std::vector<Vecteur> angle , double temps = 0) const override;
    virtual Vecteur eq_evolutionAngle(std::vector<Vecteur> position, std::vector<Vecteur> angle , double temps = 0) const override;
    bool fire(double temps);
    double masse(double temps) const;
    double angleVitesse() const;
    bool getParachute()const { return parachute;}
    void boom(){parachute = true;}
    void inverseMotor(){motor = !motor;}
    int signeof(double x) const;





private:
    Vecteur GCCarthesien();
    Vecteur wCarthesien();
    Vecteur vitesseC();
    double rayon, hauteur, Ctrainee, densiteAir, distanceGP, sAileron, tempsCombustion, rayonP;
    bool parachute, motor;
    double forceMoteur(double temps) const;
    double forceG(double temps) const;
    double forceFrot(Vecteur vitesse, Vecteur angle,Vecteur vitesseAng) const;

    double surface(double angle) const;
    double I(double temps) const;

    Vecteur vent;




};

#endif // FUSEE_H
