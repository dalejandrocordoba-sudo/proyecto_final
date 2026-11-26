#ifndef ENEMIGO_H
#define ENEMIGO_H
#include "entidad.h"
#include "fisica.h"


class enemigo: public entidad {



protected:
    fisica *Fisica;
    double t;
    bool congelado;
    double tdisparo;

public:


    enemigo(fisica *f, double x, double y);
    ~enemigo() override;

    void actualizar(double dt) override;

    virtual bool recibirimpacto(double vmundo);

    void congelar(double vmundo);
    bool estacongelado() const;
    bool debedisparar(double dt, double cadencia);

};
#endif // ENEMIGO_H
