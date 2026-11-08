#include "entidad.h"

entidad::entidad(double x, double y, int vida)
    : x(x), y(y), vx(0), vy(0), vida(vida) {}

entidad::entidad(){}

double entidad::getx() const {return x; }
double entidad::gety() const {return y; }
int entidad::getvida() const {return vida;}
bool entidad::estaviva() const{return vida > 0;}

void entidad::resibirdano(int d){vida -= d;}
void entidad::setvelocidad(double vx, double vy) {vx = nvx; vy = nvy;}

