#include "balaagente.h"

balaagente::balaagente(fisica *f, double x, double y, int carril)
    : proyectil(f, x, y), carril(carril){}

int balaagente::getcarril() const {return carril;}