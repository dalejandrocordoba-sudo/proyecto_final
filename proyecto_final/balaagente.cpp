#include "balaagente.h"

balaagente::balaagente(class fisica *f, double x, double y, int carril)
    : proyectil(f, x, y), carril(carril){}

int balaagente::getcarril() const {return carril;}