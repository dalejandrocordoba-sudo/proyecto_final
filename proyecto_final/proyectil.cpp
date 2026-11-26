#include "proyectil.h"

proyectil::proyectil(class fisica *f, double x, double y)
    : entidad(x, y, 1), Fisica(f), t(0){}

proyectil::~proyectil(){delete Fisica;}

void proyectil::actualizar(double dt){


    t += dt;
    QPointF p = Fisica->posicion(t);

    x= p.x();
    y= p.y();

}