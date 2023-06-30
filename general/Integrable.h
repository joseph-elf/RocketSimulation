#ifndef H_INTEGRABLE
#define H_INTEGRABLE

#include <iostream>
#include <vector>
#include <cmath> 

#include "Erreur.h"
#include "bases/Vecteur.h"
#include "bases/constantes.h"
#include "Memoire.h"

#define abs(nb) ((nb) < 0 ? -(nb) : (nb))

class Integrable {
	public: 


		//constructeurs
            Integrable();
            Integrable (std::vector<Vecteur> Position, std::vector<Vecteur>Angle); //verifie si la dimension de Position est == à degre_Position, erreur sinon
            Integrable (std::vector<double> data); //verifie si la dimension de Position est == à degre_Position, erreur sinon

		
   		//destructeur
            virtual ~Integrable()=default;

		
		//methodes 
            virtual Vecteur eq_evolutionXYZ (std::vector<Vecteur> position , std::vector<Vecteur> angle , double temps = 0) const = 0;
            virtual Vecteur eq_evolutionAngle (std::vector<Vecteur> position , std::vector<Vecteur> angle , double temps = 0) const = 0;

            const Vecteur get_vect_P () const; //retourne Position[0]
            const Vecteur get_vect_dP () const; //retourne Position[1]
            const Vecteur get_vect_A () const; //retourne Position[0]
            const Vecteur get_vect_dA () const; //retourne Position[1]

        //integrateurs
            virtual void EulerCromer (double pas_de_temps, double temps = 0); //l'intégrateur numérique de Euler-Crommer de degré 1 et 2
            virtual void Newmark (double pas_de_temps, double temps = 0); //l'intégrateur numérique de Newmark de degré 2
            virtual void RungeKutta (double pas_de_temps, double temps = 0); //l'intégrateur numérique de Runge-Kutta de degré 1 et 2
    
		//operateurs internes
		
		//inutiles aux beneficiaires 
		void affiche (std::ostream&) const;



        void recordTrace(double facteur_multiplicateur= 2.5); //enregistre la trace de OG
        Vecteur getVectNb(size_t nb) const; //retourne le ieme - 1 vecteur de la Memoire trace
        size_t nbVectTrace() const; //retourne la taille de la Memoire trace
        void clearTrace();
			
	protected:
        //attribut
        std::vector<Vecteur> PositionXYZ;
        std::vector<Vecteur> Orientation;

        Memoire trace;

};

//methodes externes
std::ostream& operator<< (std::ostream&, Integrable const&);

#endif
