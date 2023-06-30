#ifndef H_SYSTEME
#define H_SYSTEME

#include <iostream>
#include <vector>
#include <cmath> 
#include <stdlib.h>
#include <time.h>

#include "bases/Vecteur.h"

#include "Erreur.h"
#include "fusee.h"


#include "dessinable.h"
#include "support_a_dessin.h"




class Systeme : public Dessinable {
    public:
        Systeme(SupportADessin* vue);
        ~Systeme();

        virtual void dessine() override;


        void evolue(double dt, double temps); //Appelle les integrateurs de chaques integrable du systeme; toupies et balles






        double random(double min=0., double max=1.);//Sort un double aleatoire entre min et max (quand ils sont petits)
        std::vector<double> getData();

        Fusee* getRocket()const{return rocket;}

        void invertTrace(){
            trace = !trace;
            rocket->clearTrace();
          };
        bool getTrace()const{return trace;}

        void openParachute(){rocket->boom();}
        void startMotor(){rocket->inverseMotor();}



        double tempsSysteme;

	protected:
        Fusee* rocket;
        bool trace;


};
double arrondis(double value);
#endif
