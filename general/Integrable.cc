#include "Integrable.h"

//constructeurs
Integrable::Integrable(){
    PositionXYZ = std::vector<Vecteur>{Vecteur(0.0, 0.0, 0.0), Vecteur(0.0, 0.0, 0.0)};
    Orientation = std::vector<Vecteur>{Vecteur(0.0, 0.1, 0.0), Vecteur(3)};
}

Integrable::Integrable (std::vector<Vecteur> p, std::vector<Vecteur> Angle) {
    PositionXYZ = p;
    Orientation = Angle;
}

Integrable::Integrable(std::vector<double> data){
    PositionXYZ = std::vector<Vecteur>{Vecteur(data[0], data[1], data[2]), Vecteur(data[3], data[4], data[5])};
    Orientation = std::vector<Vecteur>{Vecteur(data[6], data[7], data[8]), Vecteur(data[9], data[10], data[11])};
}

//methodes publiques
const Vecteur Integrable::get_vect_P () const {
    return PositionXYZ[0];
}
const Vecteur Integrable::get_vect_dP () const {
    return PositionXYZ[1];
}

const Vecteur Integrable::get_vect_A () const {
    return Orientation[0];
}
const Vecteur Integrable::get_vect_dA () const {
    return Orientation[1];
}


//intgerateurs
void Integrable::EulerCromer (double dt, double temps) {
        PositionXYZ[1] += dt * eq_evolutionXYZ(PositionXYZ, Orientation ,temps);
        PositionXYZ[0] += dt * PositionXYZ[1];

        Orientation[1] += dt * eq_evolutionAngle(PositionXYZ, Orientation, temps);
        Orientation[0] += dt * Orientation[1];
        Orientation[0][0] = std::fmod(Orientation[0][0], 2*pi);
        Orientation[0][1] = std::fmod(Orientation[0][1], 2*pi);
        Orientation[0][2] = std::fmod(Orientation[0][2], 2*pi);


}


void Integrable::Newmark (double dt, double temps) {
  /*      double T0 = temps;
        double T1 = dt + T0;
        Vecteur P0 = PositionXYZ[0];
        Vecteur P1 = P0;
        Vecteur dP0 = PositionXYZ[1];
        Vecteur dP1 = dP0;
        std::vector<Vecteur> p0 = PositionXYZ;
            p0[0] = P0;
            p0[1] = dP0;
        Vecteur s = eq_evolutionXYZ(p0, T0);
        Vecteur q, r;

        do {
            q = P1;
            std::vector<Vecteur> pr = PositionXYZ;
                pr[0] = P1;
                pr[1] = dP1;
            r = eq_evolutionXYZ(pr, T1);
            dP1 = dP0 + (0.5 * dt * (r + s));
            P1 = P0 + (dt * dP0) + ((1./3.) * dt * dt * ((0.5 * r) + s));
        } while ((P1 - q).norme() >= epsilon);

        PositionXYZ[0] = P1;
        PositionXYZ[1] = dP1;*/
}

void Integrable::RungeKutta (double dt, double temps) {

        Vecteur k1 (PositionXYZ[1]);
        Vecteur k1b (eq_evolutionXYZ(PositionXYZ, Orientation,temps));
        Vecteur k2 (PositionXYZ[1] + ((dt*0.5) * k1b));
        std::vector<Vecteur> pk2b = PositionXYZ;
        pk2b[0] += 0.5 * dt * k1;
        pk2b[1] += 0.5 * dt *k1b;
        Vecteur k2b (eq_evolutionXYZ (pk2b,Orientation, temps + dt*0.5));
        Vecteur k3 (PositionXYZ[1] + ((dt*0.5) * k2b));
        std::vector<Vecteur> pk3b = PositionXYZ;
        pk3b[0] += 0.5 * dt * k2;
        pk3b[1] += 0.5 * dt *k2b;
        Vecteur k3b (eq_evolutionXYZ (pk3b,Orientation, temps + dt*0.5));
        Vecteur k4 (PositionXYZ[1] + (dt * k3b));
        std::vector<Vecteur> pk4b = PositionXYZ;
        pk4b[0] += dt * k3;
        pk4b[1] += dt *k3b;
        Vecteur k4b (eq_evolutionXYZ (pk4b, Orientation, temps));
	
        PositionXYZ[0] += ((dt/6) * (k1 + (2*k2) + (2*k3) + k4));
        PositionXYZ[1] += ((dt/6) * (k1b + (2*k2b) + (2*k3b) + k4b));


        Vecteur o1 (Orientation[1]);
        Vecteur o1b (eq_evolutionAngle(PositionXYZ, Orientation, temps));
        Vecteur o2 (Orientation[1] + ((dt*0.5) * k1b));
        std::vector<Vecteur> po2b = Orientation;
        po2b[0] += 0.5 * dt * o1;
        po2b[1] += 0.5 * dt *o1b;
        Vecteur o2b (eq_evolutionAngle (PositionXYZ,pk2b, temps + dt*0.5));
        Vecteur o3 (Orientation[1] + ((dt*0.5) * k2b));
        std::vector<Vecteur> po3b = Orientation;
        po3b[0] += 0.5 * dt * o2;
        po3b[1] += 0.5 * dt *o2b;
        Vecteur o3b (eq_evolutionAngle (PositionXYZ, po3b, temps + dt*0.5));
        Vecteur o4 (Orientation[1] + (dt * o3b));
        std::vector<Vecteur> po4b = Orientation;
        po4b[0] += dt * o3;
        po4b[1] += dt *o3b;
        Vecteur o4b (eq_evolutionAngle (PositionXYZ, po4b, temps));

        Orientation[0] += ((dt/6) * (o1 + (2*o2) + (2*o3) + o4));
        Orientation[1] += ((dt/6) * (o1b + (2*o2b) + (2*o3b) + o4b));

}

//methodes protegees

//methodes inutiles aux beneficiaires
void Integrable::affiche (std::ostream &flux) const {
    flux << "P: " << PositionXYZ[0] << "\n" << "dP: " << PositionXYZ[1] << "\n";
}


//operateurs externes
std::ostream& operator<<(std::ostream& flux, Integrable const& t) {
	t.affiche(flux);
	return flux;
}




void Integrable::recordTrace(double coeff){
    Vecteur XY(PositionXYZ[0][0], PositionXYZ[0][1], PositionXYZ[0][2]);
    trace.add_vect(XY);
}

Vecteur Integrable::getVectNb(size_t nb) const {
    return trace.get_vect(nb);
}

size_t Integrable::nbVectTrace() const {
    return trace.taille();
}

void Integrable::clearTrace(){
    trace.clear();
}
