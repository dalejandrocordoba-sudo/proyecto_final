#include "objetomundo.h"

objetomundo::objetomundo(tipoobjeto tipo, fisica *f, double x, double y)
    : entidad(x, y, 1), tipo(tipo), Fisica(f), t(0) {}


objetomundo::~objetomundo(){delete Fisica;}

void objetomundo::actualizar(double dt){

    t +=dt;
    QPointF p = Fisica->posicion(t);
    x = p.x();
    y = p.y();



}


tipoobjeto objetomundo::gettipo() const {return tipo;}