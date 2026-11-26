#include "enemigo.h"


enemigo::enemigo(fisica *f, double x, double y)
    :entidad(x, y, 3), Fisica(f), t(0), congelado(false), tdisparo(0){}


enemigo::~enemigo() {delete Fisica; }

void enemigo::actualizar(double dt){

    t += dt;
    QPointF p = Fisica ->posicion(t);

    x= p.x();
    y= p.y();

}

bool enemigo::recibirimpacto(double vmundo){

    congelar(vmundo);
    return true;
}

void enemigo::congelar(double vmundo){

    delete Fisica;

    Fisica = new movrectilineo(x, y, -vmundo, 0);
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