#include "memoria.h"
#include <algorithm>
using namespace std;


Memoria::Memoria(double tasa) : tasa(tasa) {

    for (int c =0; c<3; ++c) pesos[c] = 1.0;

}


double Memoria::getpeso(int carril) const {
    return pesos.value(carril, 1.0);

}


void Memoria::actualizar (int carril, bool acierto) {

    double p = pesos[carril];
    p += acierto ? tasa : -tasa;
    pesos[carril] = min(5.0, max(0.1, p));

}