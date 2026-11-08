#include "proyectil.h"

proyectil::~proyectil(Fisica *f, double x, double y)
    : Entidad(x, y, 1), fisica(f), t(0){}

proyectil::~proyectil(){delete fisica;}

void proyctil::actualizar(double dt){


    t += dt;
    QPointF p = fisica->posicion(t);

    x= p.x();
    y= p.y();

}