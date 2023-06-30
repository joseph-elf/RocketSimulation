#ifndef GLROCKET_H
#define GLROCKET_H
#include "vector"
#include <cmath>
#include <QOpenGLShaderProgram>
#include "vertex_shader.h"


class GlRocket
{
public:
    GlRocket(std::size_t nb_coins = 12);
    void draw(QOpenGLShaderProgram& prog, double rayon, double hauteur, bool fire = false); //dessine le cone
    void fire(QOpenGLShaderProgram& prog, double rayon, double hauteur); //dessine le cone

    void parachute(QOpenGLShaderProgram& prog, double rayon); //dessine le cone



private:
    std::vector<double> coordX, coordY;
};

#endif // GLROCKET_H
