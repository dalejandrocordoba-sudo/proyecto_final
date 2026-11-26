#include "pepsiman.h"

namespace {
const double V_SALTO = 700.0;
const double G_SALTO = 1500.0;
const double ANGULO_VERTICAL = 1.5707963267948966;
const double V_LATA = 640.0;
const double ANGULO_LATA = 0.5236;
const double G_LATA = 900.0;
const double ENFRIAMIENTO = 0.30;
const double TIEMPO_INVULNERABLE = 1.6;

}




pepsiman::pepsiman(double x, double ysuelo)
    : entidad(x, ysuelo, 3), ysuelo(ysuelo), salto(nullptr), tsalto(0),
    enfriamiento(0), invulnerable(0), puntos(0), latasrecogidas(0), bonosvida(0) {}

pepsiman::~pepsiman() { delete salto; }

void pepsiman::actualizar(double dt){

    if (enfriamiento > 0) enfriamiento -= dt;
    if(invulnerable > 0) invulnerable -= dt;

    if (salto){

        tsalto += dt;
        QPointF p = salto->posicion(tsalto);
        if (p.y() >= 0 && tsalto > 0){

            y = ysuelo;
            delete salto;
            salto = nullptr;
        } else {
            y = ysuelo + p.y();
        }

    }
}

void pepsiman::saltar(){
    if (salto) return;
    salto = new movparabolico(0, 0, V_SALTO, ANGULO_VERTICAL, G_SALTO );
    tsalto = 0;

}


bool pepsiman::enaire() const {return salto != nullptr;}
proyectil* pepsiman::lanzarlata(){
    if (enfriamiento > 0) return nullptr;
    enfriamiento = ENFRIAMIENTO;
    double x0 = x + 50, y0 = y -55;
    return new proyectil(new movparabolico(x0, y0, V_LATA, ANGULO_LATA, G_LATA), x0, y0);

}


void pepsiman::sumarpuntos(int p){

    puntos += p;
    while (puntos / 1000 >bonosvida){

        ++bonosvida;
        ++vida;

    }

}


void pepsiman::recogerlata(){

    ++latasrecogidas;
    sumarpuntos(100);

}


bool pepsiman::recibirgolpe(){

    if (invulnerable > 0) return false;
    recibirdano(1);
    invulnerable = TIEMPO_INVULNERABLE;
    return true;


}

void pepsiman::restaurarestado(int p, int v) {
    puntos = p;
    vida = v;
    bonosvida = p / 1000;
    latasrecogidas = 0;
    invulnerable = 0;
}

bool pepsiman::esinvulnerable() const { return invulnerable > 0; }
double pepsiman::tiempoinvulnerable() const { return invulnerable; }
int pepsiman::getvidas() const { return vida; }
int pepsiman::getpuntos() const { return puntos; }
int pepsiman::getlatasrecogidas() const { return latasrecogidas; }