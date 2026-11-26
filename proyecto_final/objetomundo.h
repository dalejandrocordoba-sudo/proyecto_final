#ifndef OBJETOMUNDO_H
#define OBJETOMUNDO_H


#include "entidad.h"
#include "fisica.h"


enum class tipoobjeto{ bache, llantas, lata, zarigueya, llantarebote

};

class objetomundo : public entidad{

    tipoobjeto tipo;
    fisica *fisica;
    double t;

public:

    objetomundo(tipoobjeto tipo, fisica *f, double x, double y);
    ~objetomundo() override;
    void actualizar(double dt) override;
    tipoobjeto gettipo() const;

};


#endif // OBJETOMUNDO_H
