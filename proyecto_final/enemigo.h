#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "entidad.h"
#include "fisica.h"


class enemigo: public entidad{



protected:
    Fisica *fisica;
    double t;
    bool congelado;
    double tdisparo;

public:


    enemigo(Fisica *f, double x, double y);
    ~enemigo() overrride;

    void actualizar(double dt) override;

    virtual bool recibirimpacto(double vmundo);

    void congelar(doble vmundo);
    bool estacongelado() const;
    bool debedisparar(double dt, double cadencia);

};
#endif // ENEMIGO_H
