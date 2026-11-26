#include "objetomundo.h"

objetomundo::objetomundo(tipoobjeto tipo, fisica *f, double x, double y)
    : entidad(x, y, 1), tipo(tipo), fisica(f), t(0) {}


objetomundo::objetomundo(){delete fisica;}

void objetomundo::actualizar(double dt){

    t +=dt;
    QPointF p = fisisca ->posicion(t);
    x = p.x();
    y = p.y();



}


tipoobjeto objetomundo::gettipo() const {return tipo;}