#ifndef JEFEBANDOLERO_H
#define JEFEBANDOLERO_H

#include "enemigo.h"
#include "agente.h"

class jefebandolero : public enemigo{

    agente *agente;
    int vidamaxima;
    bool anclado;
    bool preparado;

public:


    jefebandolero(fisica *f, double x, double y, double tasaaprendizaje);
    ~jefebandolero() override;


    class agente* getagente();
    int getvidamaxima() const;
    void anclar(double xpantalla);
    bool estaanclado() const;
    bool estapreparado() const;

    bool actualizarataque(double dt, double cadencia, double aviso);
    bool recibirimpacto(double vmundo) override;



};


#endif // JEFEBANDOLERO_H
