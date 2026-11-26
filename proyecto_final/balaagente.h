#ifndef BALAAGENTE_H
#define BALAAGENTE_H
#include "proyectil.h"

class balaagente : public proyectil{

    int carril;

public:
    balaagente(class fisica *f, double x, double y, int carril);
    int getcarril()const;

};

#endif // BALAAGENTE_H
