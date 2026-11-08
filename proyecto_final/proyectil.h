#ifndef PROYECTIL_H
#define PROYECTIL_H
#include "entidad.h"
#include "fisica.h"

class proyectil : public entidad{

    Fisica *fisica;
    double t;

public:
    proyectil(fisica *f, double x, double y);
    ~proyectil() override;
    void actualizar(double dt) override;

};

#endif // PROYECTIL_H
