#ifndef PEPSIMAN_H
#define PEPSIMAN_H

#include "entidad.h"
#include "fisica.h"
#include "proyectil.h"


class pepsiman : public entidad{

    double ysuelo;
    fisica *salto;
    double tsalto;
    double enfriamiento;
    double invulnerable;
    int puntos;
    int latasrecogidas;
    int bonosvida;

public:

    pepsiman(double x, double ysuelo);
    ~pepsiman()override;



    void actualizar(double dt) override;
    void saltar();
    bool enaire() const;

    proyectil* lanzarlata();
    void sumarpuntos(int p);
    void recogerlata();
    bool recibirgolpe();
    void restaurarestado(int puntos, int vidas);
    bool esinvulnerable() const;
    int getvidas() const;
    int getpuntos() const;
    int getlatasrecogidas() const;



};

#endif // PEPSIMAN_H
