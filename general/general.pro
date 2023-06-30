TEMPLATE = lib

CONFIG += staticlib c++11

SOURCES += Systeme.cc \
    Erreur.cc \
    bases/Vecteur.cc \
    bases/Matrice33.cc \
    bases/constantes.cc \
    dessinable.cc \
    fusee.cc \
    Integrable.cc \
    Memoire.cc

HEADERS += \
    Erreur.h \
    Systeme.h \
    bases/Vecteur.h \
    bases/Matrice33.h \
    bases/constantes.h \
    bases/testMatrice33.h \
    bases/testVecteur.h \
    fusee.h \
    dessinable.h \
    support_a_dessin.h \
    Integrable.h\
    Memoire.h
