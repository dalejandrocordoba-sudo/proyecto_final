#include "enemigo.h"


enemigo::enemigo(Fisica *f, double x, double y)
    :entidad(x, y, 3), fisica(f), t(0), congelado(false), tdisparo(0){}


enemigo::~enemigo() {delete fisica; }

void enemigo::actualizar(double dt){

    t += dt;
    QPointF p = fisica ->posicion(t);

    x= p.x();
    y= p.y();

}

bool enemigo::recibirimpacto(double vmundo){

    congelar(vmundo);
    return true;
}

void enemigo::congelar(doble vmundo){

    delete fisica;

    fisica 0 new movrectilineo(x, y, -vmundo, 0);
    t=0;

    congelado= true;

}

bool enemigo::estacongelado() const{return congelado;}

bool enemigo::debedisparar(double dt, double cadencia){

    if(congelado) return false;
    tdisparo += dt;

    if (tdisparo >= cadencia) {tdisparo = 0; return true;}

    return false;
}