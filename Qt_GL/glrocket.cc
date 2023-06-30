#include "glrocket.h"

GlRocket::GlRocket(std::size_t nb_coins)
{
double pi(3.1416);
double a(2*pi/nb_coins);
for(std::size_t i(0); i < nb_coins ; i++){
    coordX.push_back(cos(i * a));
    coordY.push_back(sin(i * a));
}
}

void GlRocket::draw(QOpenGLShaderProgram &prog, double rayon, double hauteur, bool fire){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    for(size_t i(0); i<coordX.size()-1; i++ ){
        prog.setAttributeValue(CouleurId, 0.9, 0.9, 0.9);
        prog.setAttributeValue(SommetId,rayon * coordX[i],rayon * coordY[i], 0.0);
        prog.setAttributeValue(SommetId,rayon * coordX[i+1],rayon * coordY[i+1], 0.0);
        prog.setAttributeValue(SommetId,rayon * coordX[i+1],rayon * coordY[i+1],  0.85*hauteur);
        prog.setAttributeValue(SommetId,rayon * coordX[i],rayon * coordY[i], 0.85* hauteur);
    }
    prog.setAttributeValue(CouleurId, 0.2, 0.2, 0.2);
    prog.setAttributeValue(SommetId,rayon * coordX[coordX.size()-1],rayon * coordY[coordX.size()-1], 0.0);
    prog.setAttributeValue(SommetId,rayon *  coordX[0],rayon * coordY[0], 0.0);
    prog.setAttributeValue(SommetId,rayon * coordX[0],rayon * coordY[0],  0.85*hauteur);
    prog.setAttributeValue(SommetId,rayon * coordX[coordX.size()-1],rayon * coordY[coordX.size()-1], 0.85* hauteur);
    glEnd();



    glBegin(GL_QUADS);
    for(size_t i(0); i<coordX.size()-1; i++ ){
        prog.setAttributeValue(CouleurId, (i+1)%2, (i+1)%2, (i+1)%2);
        prog.setAttributeValue(SommetId, rayon * coordX[i], rayon * coordY[i], 0.85*hauteur );
        prog.setAttributeValue(SommetId, rayon * coordX[i+1],rayon * coordY[i+1], 0.85*hauteur );
        prog.setAttributeValue(SommetId,rayon * coordX[i+1], rayon * coordY[i+1], 0.88*hauteur );
        prog.setAttributeValue(SommetId, rayon * coordX[i], rayon * coordY[i], 0.88*hauteur);
    }
    prog.setAttributeValue(CouleurId, coordX.size()%2, coordX.size()%2, coordX.size()%2);
    prog.setAttributeValue(SommetId,rayon * coordX[coordX.size()-1],rayon * coordY[coordX.size()-1], 0.85*hauteur );
    prog.setAttributeValue(SommetId, rayon *  coordX[0],rayon * coordY[0], 0.85*hauteur);
    prog.setAttributeValue(SommetId, rayon * coordX[0],rayon * coordY[0], 0.88*hauteur );
    prog.setAttributeValue(SommetId,rayon * coordX[coordX.size()-1], rayon * coordY[coordX.size()-1], 0.88*hauteur);
    glEnd();

    glBegin(GL_QUADS);
    for(size_t i(0); i<coordX.size()-1; i++ ){
        prog.setAttributeValue(CouleurId, i%2, i%2, i%2);
        prog.setAttributeValue(SommetId, rayon * coordX[i],rayon * coordY[i], 0.88*hauteur );
        prog.setAttributeValue(SommetId, rayon * coordX[i+1], rayon * coordY[i+1], 0.88*hauteur );
        prog.setAttributeValue(SommetId, rayon * coordX[i+1], rayon * coordY[i+1], 0.91*hauteur );
        prog.setAttributeValue(SommetId, rayon * coordX[i], rayon * coordY[i], 0.91*hauteur);
    }
    prog.setAttributeValue(CouleurId, coordX.size()-1%2, coordX.size()-1%2, coordX.size()-1%2);
    prog.setAttributeValue(SommetId, rayon * coordX[coordX.size()-1], rayon * coordY[coordX.size()-1], 0.88*hauteur );
    prog.setAttributeValue(SommetId, rayon *  coordX[0], rayon * coordY[0], 0.88*hauteur);
    prog.setAttributeValue(SommetId,rayon * coordX[0], rayon * coordY[0], 0.91*hauteur );
    prog.setAttributeValue(SommetId, rayon * coordX[coordX.size()-1], rayon * coordY[coordX.size()-1], 0.91*hauteur);
    glEnd();

    glBegin(GL_QUADS);
    for(size_t i(0); i<coordX.size()-1; i++ ){
        prog.setAttributeValue(CouleurId, (i+1)%2, (i+1)%2, (i+1)%2);
        prog.setAttributeValue(SommetId, rayon * coordX[i], rayon * coordY[i], 0.94*hauteur );
        prog.setAttributeValue(SommetId, rayon * coordX[i+1],rayon * coordY[i+1], 0.94*hauteur );
        prog.setAttributeValue(SommetId,rayon * coordX[i+1], rayon * coordY[i+1], 0.91*hauteur );
        prog.setAttributeValue(SommetId, rayon * coordX[i], rayon * coordY[i], 0.91*hauteur);
    }
    prog.setAttributeValue(CouleurId, coordX.size()%2, coordX.size()%2, coordX.size()%2);
    prog.setAttributeValue(SommetId,rayon * coordX[coordX.size()-1],rayon * coordY[coordX.size()-1], 0.94*hauteur );
    prog.setAttributeValue(SommetId, rayon *  coordX[0],rayon * coordY[0], 0.94*hauteur);
    prog.setAttributeValue(SommetId, rayon * coordX[0],rayon * coordY[0], 0.91*hauteur );
    prog.setAttributeValue(SommetId,rayon * coordX[coordX.size()-1], rayon * coordY[coordX.size()-1], 0.91*hauteur);
    glEnd();

    glBegin(GL_QUADS);
    for(size_t i(0); i<coordX.size()-1; i++ ){
        prog.setAttributeValue(CouleurId, 0.9, 0.9, 0.9);
        prog.setAttributeValue(SommetId, rayon * coordX[i], rayon * coordY[i], 0.94*hauteur );
        prog.setAttributeValue(SommetId, rayon * coordX[i+1], rayon * coordY[i+1], 0.94*hauteur );
        prog.setAttributeValue(SommetId, rayon * coordX[i+1], rayon * coordY[i+1], hauteur );
        prog.setAttributeValue(SommetId, rayon * coordX[i], rayon * coordY[i], hauteur);
    }
    prog.setAttributeValue(CouleurId, 0.2, 0.2, 0.2);
    prog.setAttributeValue(SommetId, rayon * coordX[coordX.size()-1],rayon * coordY[coordX.size()-1], 0.94*hauteur );
    prog.setAttributeValue(SommetId, rayon *  coordX[0], rayon * coordY[0], 0.94*hauteur);
    prog.setAttributeValue(SommetId, rayon * coordX[0], rayon * coordY[0], hauteur );
    prog.setAttributeValue(SommetId, rayon * coordX[coordX.size()-1], rayon * coordY[coordX.size()-1], hauteur);
    glEnd();






   double hauteurCone(0.125 * hauteur);
    glBegin(GL_QUADS);
    for(size_t i(0); i<coordX.size()-1; i++ ){
        prog.setAttributeValue(CouleurId, 1.0, 0.5, 0.0);
        prog.setAttributeValue(SommetId,rayon * coordX[i],rayon * coordY[i], hauteur);
        prog.setAttributeValue(SommetId,rayon * coordX[i+1],rayon * coordY[i+1], hauteur);
        prog.setAttributeValue(SommetId,0.8 * rayon * coordX[i+1],0.8 * rayon * coordY[i+1], hauteur + 0.5*hauteurCone);
        prog.setAttributeValue(SommetId,0.8 * rayon * coordX[i],0.8 * rayon * coordY[i], hauteur + 0.5*hauteurCone);
    }
    prog.setAttributeValue(CouleurId, 1.0, 0.5, 0.0);
    prog.setAttributeValue(SommetId,rayon * coordX[coordX.size()-1],rayon * coordY[coordX.size()-1], hauteur);
    prog.setAttributeValue(SommetId,rayon *  coordX[0],rayon * coordY[0], hauteur);
    prog.setAttributeValue(SommetId,0.8 * rayon * coordX[0],0.8 * rayon * coordY[0], hauteur + 0.5*hauteurCone);
    prog.setAttributeValue(SommetId,0.8 * rayon * coordX[coordX.size()-1],0.8 * rayon * coordY[coordX.size()-1], hauteur + 0.5*hauteurCone);
    glEnd();


    glBegin(GL_QUADS);
    for(size_t i(0); i<coordX.size()-1; i++ ){
        prog.setAttributeValue(CouleurId, 1.0, 0.5, 0.0);
        prog.setAttributeValue(SommetId,0.8 * rayon * coordX[i],0.8 * rayon * coordY[i], hauteur + 0.5*hauteurCone);
        prog.setAttributeValue(SommetId,0.8 * rayon * coordX[i+1],0.8 * rayon * coordY[i+1], hauteur + 0.5*hauteurCone);
        prog.setAttributeValue(SommetId,0.4 * rayon * coordX[i+1],0.4 * rayon * coordY[i+1], hauteur + 0.8*hauteurCone);
        prog.setAttributeValue(SommetId,0.4 * rayon * coordX[i],0.4 * rayon * coordY[i], hauteur + 0.8*hauteurCone);
    }
    prog.setAttributeValue(CouleurId, 1.0, 0.5, 0.0);
    prog.setAttributeValue(SommetId,0.8 * rayon * coordX[coordX.size()-1],0.8 * rayon * coordY[coordX.size()-1], hauteur + 0.5*hauteurCone);
    prog.setAttributeValue(SommetId,0.8 * rayon *  coordX[0],0.8 * rayon * coordY[0], hauteur + 0.5*hauteurCone);
    prog.setAttributeValue(SommetId,0.4 * rayon * coordX[0],0.4 * rayon * coordY[0], hauteur + 0.8*hauteurCone);
    prog.setAttributeValue(SommetId,0.4 * rayon * coordX[coordX.size()-1],0.4 * rayon * coordY[coordX.size()-1], hauteur + 0.8*hauteurCone);
    glEnd();


    glBegin(GL_TRIANGLES);
    for(size_t i(0); i<coordX.size()-1; i++ ){
        prog.setAttributeValue(CouleurId, 1.0, 0.5, 0.0);
        prog.setAttributeValue(SommetId,0.4 * rayon * coordX[i],0.4 * rayon * coordY[i], hauteur + 0.8*hauteurCone);
        prog.setAttributeValue(SommetId,0.4 * rayon * coordX[i+1],0.4 * rayon * coordY[i+1], hauteur + 0.8*hauteurCone);
        prog.setAttributeValue(SommetId,0.0 ,0.0 , hauteur + hauteurCone);
    }
    prog.setAttributeValue(CouleurId, 1.0, 0.5, 0.0);
    prog.setAttributeValue(SommetId,0.4 * rayon * coordX[coordX.size()-1],0.4 * rayon * coordY[coordX.size()-1], hauteur + 0.8*hauteurCone);
    prog.setAttributeValue(SommetId,0.4 * rayon *  coordX[0],0.4 * rayon * coordY[0], hauteur + 0.8*hauteurCone);
    prog.setAttributeValue(SommetId,0.0 ,0.0 , hauteur + hauteurCone);
    glEnd();


    glBegin(GL_POLYGON);

    prog.setAttributeValue(CouleurId, 1.0, 0.5, 0.0);
    prog.setAttributeValue(SommetId,0.0 ,rayon , 0.16*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,2.7 * rayon , 0.1*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,2.7 * rayon , 0.01*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,rayon, 0.0);

    prog.setAttributeValue(SommetId,0.0 ,-rayon, 0.0);
    prog.setAttributeValue(SommetId,0.0 ,-2.7 * rayon , 0.01*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,-2.7 * rayon , 0.1*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,-rayon , 0.16*hauteur);

    glEnd();


    glBegin(GL_POLYGON);

    prog.setAttributeValue(CouleurId, 1.0, 0.5, 0.0);
    prog.setAttributeValue(SommetId,rayon ,0.0 , 0.16*hauteur);
    prog.setAttributeValue(SommetId,2.7 * rayon ,0.0 , 0.1*hauteur);
    prog.setAttributeValue(SommetId,2.7 * rayon ,0.0 , 0.01*hauteur);
    prog.setAttributeValue(SommetId,rayon ,0.0, 0.0);

    prog.setAttributeValue(SommetId,-rayon ,0.0, 0.0);
    prog.setAttributeValue(SommetId,-2.7 * rayon ,0.0 , 0.01*hauteur);
    prog.setAttributeValue(SommetId,-2.7 * rayon ,0.0 , 0.1*hauteur);
    prog.setAttributeValue(SommetId,-rayon ,0.0 , 0.16*hauteur);
    glEnd();




    glBegin(GL_QUADS);
    for(size_t i(0); i<coordX.size()-1; i++ ){
        prog.setAttributeValue(CouleurId, 1.0, 0.5, 0.0);
        prog.setAttributeValue(SommetId,rayon * coordX[i],rayon * coordY[i], 0.0);
        prog.setAttributeValue(SommetId,rayon * coordX[i+1], rayon * coordY[i+1], 0.0);
        prog.setAttributeValue(SommetId,0.8 * rayon * coordX[i+1],0.8 * rayon * coordY[i+1], -0.01 * hauteur);
        prog.setAttributeValue(SommetId,0.8 * rayon * coordX[i],0.8 * rayon * coordY[i], -0.01 * hauteur);
    }
    prog.setAttributeValue(CouleurId, 1.0, 0.5, 0.0);
    prog.setAttributeValue(SommetId,rayon * coordX[coordX.size()-1], rayon * coordY[coordX.size()-1], 0.0);
    prog.setAttributeValue(SommetId,rayon *  coordX[0], rayon * coordY[0], 0.0);
    prog.setAttributeValue(SommetId,0.8 * rayon * coordX[0],0.8 * rayon * coordY[0], -0.01 * hauteur);
    prog.setAttributeValue(SommetId,0.8 * rayon * coordX[coordX.size()-1],0.8 * rayon * coordY[coordX.size()-1],-0.01 * hauteur);
    glEnd();


    glBegin(GL_POLYGON);
    prog.setAttributeValue(CouleurId,  0.0,0.0,0.0);
    for(size_t i(0); i<coordX.size(); i++){
    prog.setAttributeValue(SommetId,0.8 * rayon * coordX[i],0.8 * rayon * coordY[i], -0.01 * hauteur);
    }
    glEnd();

    if(fire)
    GlRocket::fire(prog, rayon, hauteur);

}

void GlRocket::fire(QOpenGLShaderProgram &prog, double rayon, double hauteur){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glBegin(GL_POLYGON);

    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId,0.0 ,0.0 , 0.0);

    prog.setAttributeValue(SommetId,0.7*rayon ,0.0 , 0.0);
    prog.setAttributeValue(SommetId,1.5 * rayon ,0.0 , -0.08*hauteur);
    prog.setAttributeValue(SommetId,1.0 * rayon ,0.0 , -0.075*hauteur);
    prog.setAttributeValue(SommetId,1.4 * rayon ,0.0 , -0.15*hauteur);
    prog.setAttributeValue(SommetId,1.0 * rayon ,0.0 , -0.14*hauteur);
    prog.setAttributeValue(SommetId,1.0 * rayon ,0.0 , -0.23*hauteur);
    prog.setAttributeValue(SommetId,0.7 * rayon ,0.0 , -0.2*hauteur);

    prog.setAttributeValue(SommetId,0.0 ,0.0 , -0.34*hauteur);

    prog.setAttributeValue(SommetId,-0.7 * rayon ,0.0 , -0.2*hauteur);
    prog.setAttributeValue(SommetId,-1.0 * rayon ,0.0 , -0.23*hauteur);
    prog.setAttributeValue(SommetId,-1.0 * rayon ,0.0 , -0.14*hauteur);
    prog.setAttributeValue(SommetId,-1.4 * rayon ,0.0 , -0.15*hauteur);
    prog.setAttributeValue(SommetId,-1.0 * rayon ,0.0 , -0.075*hauteur);
    prog.setAttributeValue(SommetId,-1.5 * rayon ,0.0 , -0.08*hauteur);
    prog.setAttributeValue(SommetId,-0.7*rayon ,0.0 , 0.0);
    glEnd();


    glBegin(GL_POLYGON);

    prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0);
    prog.setAttributeValue(SommetId,0.0 ,0.005 , 0.0);

    prog.setAttributeValue(SommetId,0.4 * rayon ,0.005 , 0.0);
    prog.setAttributeValue(SommetId,0.7 * rayon ,0.005 , -0.13 * hauteur);
    prog.setAttributeValue(SommetId,0.0 ,0.005 , -0.26 * hauteur);
    prog.setAttributeValue(SommetId,-0.7 * rayon ,0.005 , -0.13 * hauteur);
    prog.setAttributeValue(SommetId,-0.4 * rayon ,0.005 , 0.0);
    glEnd();


    glBegin(GL_POLYGON);

    prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0);
    prog.setAttributeValue(SommetId,0.0 ,-0.005 , 0.0);

    prog.setAttributeValue(SommetId,0.4 * rayon ,-0.005 , 0.0);
    prog.setAttributeValue(SommetId,0.7 * rayon ,-0.005 , -0.13 * hauteur);
    prog.setAttributeValue(SommetId,0.0 ,-0.005 , -0.26 * hauteur);
    prog.setAttributeValue(SommetId,-0.7 * rayon ,-0.005 , -0.13 * hauteur);
    prog.setAttributeValue(SommetId,-0.4 * rayon ,-0.005 , 0.0);
    glEnd();




    glBegin(GL_POLYGON);

    prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0);
    prog.setAttributeValue(SommetId,0.005 ,0.0 , 0.0);

    prog.setAttributeValue(SommetId,0.005 ,0.4 * rayon , 0.0);
    prog.setAttributeValue(SommetId,0.005 ,0.7 * rayon , -0.13 * hauteur);
    prog.setAttributeValue(SommetId,0.005 ,0.0 , -0.26 * hauteur);
    prog.setAttributeValue(SommetId,0.005 ,-0.7 * rayon , -0.13 * hauteur);
    prog.setAttributeValue(SommetId,0.005 ,-0.4 * rayon , 0.0);
    glEnd();


    glBegin(GL_POLYGON);

    prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.0);
    prog.setAttributeValue(SommetId,-0.005 ,0.0 , 0.0);

    prog.setAttributeValue(SommetId,-0.005 ,0.4 * rayon , 0.0);
    prog.setAttributeValue(SommetId,-0.005 ,0.7 * rayon , -0.13 * hauteur);
    prog.setAttributeValue(SommetId,-0.005 ,0.0 , -0.26 * hauteur);
    prog.setAttributeValue(SommetId,-0.005 ,-0.7 * rayon , -0.13 * hauteur);
    prog.setAttributeValue(SommetId,-0.005 ,-0.4 * rayon , 0.0);
    glEnd();





    glBegin(GL_POLYGON);

    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId,0.0 ,0.0 , 0.0);

    prog.setAttributeValue(SommetId,0.0 ,0.7*rayon , 0.0);
    prog.setAttributeValue(SommetId,0.0 ,1.5*rayon , -0.08*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,1.0*rayon , -0.075*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,1.4*rayon , -0.15*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,1.0*rayon , -0.14*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,1.0*rayon , -0.23*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,0.7*rayon , -0.2*hauteur);

    prog.setAttributeValue(SommetId,0.0 ,0.0 , -0.34*hauteur);

    prog.setAttributeValue(SommetId,0.0 ,-0.7*rayon , -0.2*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,-1.0*rayon , -0.23*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,-1.0*rayon , -0.14*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,-1.4*rayon , -0.15*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,-1.0*rayon , -0.075*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,-1.5*rayon , -0.08*hauteur);
    prog.setAttributeValue(SommetId,0.0 ,-0.7*rayon , 0.0);


    glEnd();
}


void GlRocket::parachute(QOpenGLShaderProgram &prog, double rayon){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBegin(GL_QUADS);
    for(size_t i(0); i<coordX.size()-2; i+=2 ){

        if(i/2 %2 ==1){
            prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);

        }else{
            prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);

        }
        prog.setAttributeValue(SommetId,rayon * coordX[i],rayon * coordY[i], 0.0);
        prog.setAttributeValue(SommetId,rayon * coordX[i+2],rayon * coordY[i+2], 0.0);
        prog.setAttributeValue(SommetId,0.75*rayon * coordX[i+2],0.75*rayon * coordY[i+2], 0.4 * rayon);
        prog.setAttributeValue(SommetId,0.75*rayon * coordX[i],0.75*rayon * coordY[i], 0.4 * rayon);
    }
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId,rayon * coordX[coordX.size()-2],rayon * coordY[coordX.size()-2], 0.0);
    prog.setAttributeValue(SommetId,rayon *  coordX[0],rayon * coordY[0], 0.0);
    prog.setAttributeValue(SommetId,0.75*rayon * coordX[0],0.75*rayon * coordY[0],  0.4 * rayon);
    prog.setAttributeValue(SommetId,0.75*rayon * coordX[coordX.size()-2],0.75*rayon * coordY[coordX.size()-2], 0.4 * rayon);
    glEnd();


    glBegin(GL_QUADS);
    for(size_t i(0); i<coordX.size()-2; i+=2 ){

        if(i/2 %2 ==1){
            prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);

        }else{
            prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);

        }
        prog.setAttributeValue(SommetId,0.75*rayon * coordX[i],0.75*rayon * coordY[i], 0.4 * rayon);
        prog.setAttributeValue(SommetId,0.75*rayon * coordX[i+2],0.75*rayon * coordY[i+2], 0.4 * rayon);
        prog.setAttributeValue(SommetId,0.45*rayon * coordX[i+2],0.45*rayon * coordY[i+2], 0.6 * rayon);
        prog.setAttributeValue(SommetId,0.45*rayon * coordX[i],0.45*rayon * coordY[i], 0.6 * rayon);
    }
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId,0.75*rayon * coordX[coordX.size()-2],0.75*rayon * coordY[coordX.size()-2], 0.4 * rayon);
    prog.setAttributeValue(SommetId,0.75*rayon *  coordX[0],0.75*rayon * coordY[0], 0.4 * rayon);
    prog.setAttributeValue(SommetId,0.45*rayon * coordX[0],0.45*rayon * coordY[0],  0.6 * rayon);
    prog.setAttributeValue(SommetId,0.45*rayon * coordX[coordX.size()-2],0.45*rayon * coordY[coordX.size()-2], 0.6 * rayon);
    glEnd();


    glBegin(GL_QUADS);
    for(size_t i(0); i<coordX.size()-2; i+=2 ){

        if(i/2 %2 ==1){
            prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);

        }else{
            prog.setAttributeValue(CouleurId, 1.0, 1.0, 1.0);

        }
        prog.setAttributeValue(SommetId,0.45*rayon * coordX[i],0.45*rayon * coordY[i], 0.6 * rayon);
        prog.setAttributeValue(SommetId,0.45*rayon * coordX[i+2],0.45*rayon * coordY[i+2], 0.6 * rayon);
        prog.setAttributeValue(SommetId,0.1*rayon * coordX[i+2],0.1*rayon * coordY[i+2], 0.7 * rayon);
        prog.setAttributeValue(SommetId,0.1*rayon * coordX[i],0.1*rayon * coordY[i], 0.7 * rayon);
    }
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId,0.45*rayon * coordX[coordX.size()-2],0.45*rayon * coordY[coordX.size()-2], 0.6 * rayon);
    prog.setAttributeValue(SommetId,0.45*rayon *  coordX[0],0.45*rayon * coordY[0], 0.6 * rayon);
    prog.setAttributeValue(SommetId,0.1*rayon * coordX[0],0.1*rayon * coordY[0],  0.7 * rayon);
    prog.setAttributeValue(SommetId,0.1*rayon * coordX[coordX.size()-2],0.1*rayon * coordY[coordX.size()-2], 0.7 * rayon);
    glEnd();

    glBegin(GL_LINES);
    prog.setAttributeValue(CouleurId, 1.0, 1.0, 0.2);

    for(size_t i(0); i<coordX.size(); i+=2 ){
    prog.setAttributeValue(SommetId, rayon * coordX[i], rayon * coordY[i], 0.0);
    prog.setAttributeValue(SommetId, 0.0, 0.0, -1.6 * rayon);
    }
    prog.setAttributeValue(SommetId, 0.0, 0.0, -1.6 * rayon);
    prog.setAttributeValue(SommetId, 0.0, 0.0, -3.5 * rayon);

    glEnd();

}
