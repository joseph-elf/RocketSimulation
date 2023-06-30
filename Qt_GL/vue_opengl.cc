#include "vue_opengl.h"
#include "vertex_shader.h" // Identifiants Qt de nos différents attributs


// ======================================================================
VueOpenGL::~VueOpenGL()
{
  // Libère la mémoire des textures
  QGLContext* context =  const_cast<QGLContext*>(QGLContext::currentContext());
  context->deleteTexture(textureDeChat);
  context->deleteTexture(textureBlanche);
  context->deleteTexture(texturenous);
  context->deleteTexture(epfl);
}

void VueOpenGL::dessine(Systeme const& systeme)
{
  loadWhiteTexture();
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  X = systeme.getRocket()->get_vect_P()[0];
  Y = systeme.getRocket()->get_vect_P()[1];
  Z = systeme.getRocket()->get_vect_P()[2];

  theta = systeme.getRocket()->get_vect_A()[1];

  updatePosition();

  dessineRepere();
  drawFloor();


  QMatrix4x4 matriceFusee;
  matriceFusee.translate(systeme.getRocket()->get_vect_P()[0], systeme.getRocket()->get_vect_P()[1], systeme.getRocket()->get_vect_P()[2]);
double normevit(sqrt(systeme.getRocket()->get_vect_dP()[0]*systeme.getRocket()->get_vect_dP()[0] + systeme.getRocket()->get_vect_dP()[1]*systeme.getRocket()->get_vect_dP()[1] +systeme.getRocket()->get_vect_dP()[02]*systeme.getRocket()->get_vect_dP()[2]));
  prog.setUniformValue("vue_modele", matrice_vue * matriceFusee);
  glBegin(GL_LINES);
  prog.setAttributeValue(CouleurId, 0.8, 0.8, 0.8);
  prog.setAttributeValue(SommetId, 0.0, -1.0, 0.0);
  prog.setAttributeValue(SommetId, systeme.getRocket()->get_vect_dP()[0]/normevit, -1.0, systeme.getRocket()->get_vect_dP()[2]/normevit);
  glEnd();


  matriceFusee.rotate(systeme.getRocket()->get_vect_A()[1] * 180/pi, 0.0, 1.0, 0.0);
  matriceFusee.translate(0.0, 0.0, -0.9);
  dessineFusee(matriceFusee, 1.5, 0.05 ,systeme.getRocket()->fire(systeme.tempsSysteme));




  if(systeme.getRocket()->getParachute()){
  QMatrix4x4 matriceParachute;
  matriceParachute.translate(systeme.getRocket()->get_vect_P()[0], systeme.getRocket()->get_vect_P()[1], systeme.getRocket()->get_vect_P()[2]);
  matriceParachute.rotate((systeme.getRocket()->angleVitesse())*180/pi, 0.0, 1.0, 0.0 );
  matriceParachute.translate(0.0, 0.0, 3.5);


  dessineParachute(matriceParachute, 1.0);}


  if(systeme.getTrace())
  dessineTrace(systeme.getRocket());

drawBY();
dessineContour();


}

// ======================================================================
void VueOpenGL::init()
{
  initializeOpenGLFunctions();

  prog.addShaderFromSourceFile(QOpenGLShader::Vertex,   ":/vertex_shader.glsl");
  prog.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/fragment_shader.glsl");

  prog.bindAttributeLocation("sommet",  SommetId);
  prog.bindAttributeLocation("coordonnee_texture", CoordonneeTextureId);
  prog.bindAttributeLocation("couleur", CouleurId);

  prog.link();
  prog.bind();

  glEnable(GL_DEPTH_TEST);
  //glEnable(GL_CULL_FACE);

  QGLContext* context =  const_cast<QGLContext*>(QGLContext::currentContext());
  textureDeChat = context->bindTexture(QPixmap(":/nyan.png"), GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  textureBlanche = context->bindTexture(QPixmap(":/whitetexture.jpg"), GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

  texturenous = context->bindTexture(QPixmap(":/by.png"), GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  epfl = context->bindTexture(QPixmap(":/logoepfl.jpg"), GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  sphere.initialize();
  chinoise = GlChinoise();
  cone = Glcone();

  initializePosition();
}

// ======================================================================
void VueOpenGL::initializePosition()
{
  // position initiale
    rho = -3.0;
    psi= -40;
    omega = 0;
  matrice_position.setToIdentity();

  matrice_position.translate(0.0, 0.0, rho);
  matrice_position.rotate(psi, 1.0, 0.0, 0.0);
  matrice_position.rotate(omega, 0.0, 0.0, 1.0);
  matrice_position.translate(X,-Y,-Z);


  matrice_camera.setToIdentity();
  matrice_camera.rotate(-5,1.,0.,0.);
  matrice_vue = matrice_camera * matrice_position;
}

void VueOpenGL::loadWhiteTexture(){
    prog.setUniformValue("textureId", 0);
    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBlanche);
}

// ======================================================================
void VueOpenGL::translate(double x, double y, double z)
{
  /* Multiplie la matrice de vue par LA GAUCHE.
   * Cela fait en sorte que la dernière modification apportée
   * à la matrice soit appliquée en dernier (composition de fonctions).
   */
  QMatrix4x4 translation_supplementaire;
  translation_supplementaire.translate(x, y, z);
  matrice_position = translation_supplementaire * matrice_position;
  matrice_vue = matrice_camera * matrice_position;
}

void VueOpenGL::move(double pas){
    rho += pas;
    updatePosition();
}

// ======================================================================
void VueOpenGL::rotateCamera(double angle, double dir_x, double dir_y, double dir_z)
{
  // Multiplie la matrice de vue par LA GAUCHE
  QMatrix4x4 rotation_supplementaire;
  rotation_supplementaire.rotate(angle, dir_x, dir_y, dir_z);
  matrice_camera = rotation_supplementaire * matrice_camera;
  matrice_vue = matrice_camera * matrice_position;
}

void VueOpenGL::turnAround(double angle, double dir_x, double dir_y, double dir_z)
{
    psi += angle * dir_x;
    omega += angle * dir_z;
    updatePosition();
}


void VueOpenGL::updatePosition(){
    matrice_position.setToIdentity();

if (!croched){
    matrice_position.translate(0.0,0.0,rho); //rho negatif
    matrice_position.rotate(psi, 1.0, 0.0, 0.0);
    matrice_position.rotate(omega, 0.0, 0.0, 1.0);

    matrice_position.translate(-X,-Y,-Z);
    matrice_vue = matrice_camera * matrice_position;
}
else{

    matrice_position.translate(0.0,-0.07,0.2); //rho negatif
    matrice_position.rotate(-psi, 1.0, 0.0, 0.0);
    matrice_position.rotate(omega, 0.0, 0.0, 1.0);

    matrice_position.rotate(-theta*180/pi, 0.0, 1.0, 0.0);

    matrice_position.translate(-X,-Y,-Z);
    matrice_vue = matrice_camera * matrice_position;
}
}

// ======================================================================


void VueOpenGL::dessinePlan (QMatrix4x4 const& point_de_vue)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    //glDisable(GL_TEXTURE_2D);
    glBegin(GL_QUADS);
    prog.setAttributeValue(CouleurId, 0.8, 0.8, 0.8);
    prog.setAttributeValue(SommetId, -10.0, +10.0, 0.0);
    prog.setAttributeValue(SommetId, -10.0, -10.0, 0.0);
    prog.setAttributeValue(SommetId, +10.0, -10.0, 0.0);
    prog.setAttributeValue(SommetId, +10.0, +10.0, 0.0);
    glEnd();
}

void VueOpenGL::dessineRepere (QMatrix4x4 const& point_de_vue)
{
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_LINES);
    prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId, +1.0, 0.0, 0.0);

    prog.setAttributeValue(CouleurId, 0.0, 1.0, 0.0);
    prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId, 0.0, +1.0, 0.0);

    prog.setAttributeValue(CouleurId, 0.0, 0.0, 1.0);
    prog.setAttributeValue(SommetId, 0.0, 0.0, 0.0);
    prog.setAttributeValue(SommetId, 0.0, 0.0, +1.0);

    glEnd();
}

void VueOpenGL::dessineSphere (QMatrix4x4 const& point_de_vue, double rouge, double vert, double bleu)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  prog.setAttributeValue(CouleurId, rouge, vert, bleu);  // met la couleur
  sphere.draw(prog, SommetId);                           // dessine la sphère
}

void VueOpenGL::dessineCone (QMatrix4x4 const& point_de_vue, double paraColor)
{
  prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
  cone.draw(prog, gradColor(paraColor));
}

void VueOpenGL::dessineChinoise(const QMatrix4x4 &point_de_vue, double hauteurNorm,double paraColor){
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    chinoise.draw(prog, hauteurNorm ,gradColor(paraColor));
}
void VueOpenGL::dessineFusee(QMatrix4x4 const &point_de_vue, double hauteur, double rayon,bool fire){
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    fusee.draw(prog, rayon, hauteur, fire);

}
void VueOpenGL::dessineParachute(const QMatrix4x4 &point_de_vue, double rayon){
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    fusee.parachute(prog, rayon);
}




void VueOpenGL::drawJCC(double x, double y, double z){
    QMatrix4x4 point_de_vue;
    point_de_vue.translate(x,y,z-3.);
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      prog.setUniformValue("textureId", 0);

    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureDeChat);

    glBegin(GL_QUADS);
    // X+
    prog.setAttributeValue(CouleurId, 1, 1, 1);

    prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
    prog.setAttributeValue(SommetId, +20.0, -20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, +20.0, +20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
    prog.setAttributeValue(SommetId, +20.0, +20.0, +15.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
    prog.setAttributeValue(SommetId, +20.0, -20.0, +15.0);

    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, -20.0, -20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
    prog.setAttributeValue(SommetId, -20.0, +20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
    prog.setAttributeValue(SommetId, -20.0, +20.0, +15.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
    prog.setAttributeValue(SommetId, -20.0, -20.0, +15.0);

    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, -20.0, +20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
    prog.setAttributeValue(SommetId, +20.0, +20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
    prog.setAttributeValue(SommetId, +20.0, +20.0, +15.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
    prog.setAttributeValue(SommetId, -20.0, +20.0, +15.0);

    prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
    prog.setAttributeValue(SommetId, -20.0, -20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, +20.0, -20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
    prog.setAttributeValue(SommetId, +20.0, -20.0, +15.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
    prog.setAttributeValue(SommetId, -20.0, -20.0, +15.0);

    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBlanche);
    glEnd();
}

std::vector<double> VueOpenGL::gradColor(double x){
    double r,v,b;
    std::vector<double> RVB;
    x = 6 * fmod(abs(x), 1.0);
    if(x>=0. && x<1.){
        r=1.0;
        v=0.0;
        b=x;
    }
    if(x>=1. && x<2.){
        r=2.0-x;
        v=0.0;
        b=1.0;
    }
    if(x>=2. && x<3.){
        r=0.0;
        v=x - 2.0;
        b=1.0;
    }
    if(x>=3. && x<4.){
        r=0.0;
        v=1.0;
        b=4.0-x;
    }
    if(x>=4. && x<5.){
        r=x - 4.0;
        v=1.0;
        b=0.0;
    }
    if(x>=5. && x<=6.){
        r=1.0;
        v=6.0 - x;
        b=0.0;
    }
    RVB.push_back(r);
    RVB.push_back(v);
    RVB.push_back(b);
    return RVB;
}

void VueOpenGL::drawNousWTF(QMatrix4x4 const& point_de_vue){
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      prog.setUniformValue("textureId", 0);

    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturenous);

    glBegin(GL_QUADS);
    // X+
    prog.setAttributeValue(CouleurId, 1, 1, 1);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, -10.0, -10.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 10.0);
    prog.setAttributeValue(SommetId, -10.0, +10.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 10.0, 10.0);
    prog.setAttributeValue(SommetId, +10.0, +10.0, +0.0);
    prog.setAttributeValue(CoordonneeTextureId, 10.0, 0.0);
    prog.setAttributeValue(SommetId, +10.0, -10.0, +0.0);

    glFuncs->glActiveTexture(GL_TEXTURE0); // On la lie à nouveau au numéro 0 (comme ca on a pas besoin de changer "textureId" du shader)
    glBindTexture(GL_TEXTURE_2D, textureBlanche);
    glEnd();
}
void VueOpenGL::dessineContour( QMatrix4x4 point_de_vue){
    dessineBarriere(point_de_vue);
    point_de_vue.rotate(90, 0.,0.,1.0);
    dessineBarriere(point_de_vue);
    point_de_vue.rotate(90, 0.,0.,1.0);
    dessineBarriere(point_de_vue);
    point_de_vue.rotate(90, 0.,0.,1.0);
    dessineBarriere(point_de_vue);

}
void VueOpenGL::dessineBarriere(const QMatrix4x4 &point_de_vue){
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      prog.setUniformValue("textureId", 0);

    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, epfl);

    glBegin(GL_QUADS);
    prog.setAttributeValue(CouleurId, 1, 1, 1);

    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, -10.0, +10.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 10.0, 0.0);
    prog.setAttributeValue(SommetId, +10.0, +10.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 10.0, 1.0);
    prog.setAttributeValue(SommetId, +10.0, +10.0, +0.7);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
    prog.setAttributeValue(SommetId, -10.0, +10.0, +0.7);

    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBlanche);
    glEnd();
}

void VueOpenGL::drawBY(QMatrix4x4 const& point_de_vue){
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
      prog.setUniformValue("textureId", 0);

    QOpenGLFunctions *glFuncs = QOpenGLContext::currentContext()->functions();
    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texturenous);

    glBegin(GL_QUADS);
    // X+
    prog.setAttributeValue(CouleurId, 1, 1, 1);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 0.0);
    prog.setAttributeValue(SommetId, 10.0, 20.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 0.0);
    prog.setAttributeValue(SommetId, 20.0, 10.0, 0.0);
    prog.setAttributeValue(CoordonneeTextureId, 1.0, 1.0);
    prog.setAttributeValue(SommetId, 20.0, 10.0, 12.0);
    prog.setAttributeValue(CoordonneeTextureId, 0.0, 1.0);
    prog.setAttributeValue(SommetId, 10.0, 20.0, 12.0);

    glFuncs->glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureBlanche);
    glEnd();
}


void VueOpenGL::drawFloor(const QMatrix4x4 &point_de_vue){
    prog.setUniformValue("vue_modele", matrice_vue * point_de_vue);

    glBegin(GL_QUADS);
    for(int i(-50); i < 50; i++ ){
        for(int j(-50); j < 50; j++ ){

            prog.setAttributeValue(CouleurId, abs(i+j)%2, abs(i+j)%2, abs(i+j)%2);

            prog.setAttributeValue(SommetId, 10*i, 10*j, -0.9);
            prog.setAttributeValue(SommetId, 10*i, 10*(j+1), -0.9);
            prog.setAttributeValue(SommetId, 10*(i+1), 10*(j+1), -0.9);
            prog.setAttributeValue(SommetId, 10*(i+1), 10*j, -0.9);


        }
    }


    glEnd();
}



void VueOpenGL::dessineTrace(Integrable* objet){
QMatrix4x4 position;
    prog.setUniformValue("vue_modele", matrice_vue * position);

    glBegin(GL_LINE_STRIP);

     prog.setAttributeValue(CouleurId, 1.0, 0.0, 0.0);

    for(size_t i(0) ; i < objet->nbVectTrace() ; i++){
        prog.setAttributeValue(SommetId, objet->getVectNb(i)[0], objet->getVectNb(i)[1], objet->getVectNb(i)[2]);
    }
   glEnd();
}
