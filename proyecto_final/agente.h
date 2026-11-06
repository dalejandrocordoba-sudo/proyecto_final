#ifndef AGENTE_H
#define AGENTE_H
#include "memoria.h"

struct percepcion
{

    int carriljugador;
    double distancia;


};





class agente {

    memoria1 memoria;
    int ultimadecision;
    double ruido;

public:
    explicit agente(double tasaaprendizaje);

    void setruido(double r);
    double getpeso(int carril) const;

    percepcion percibir(int carriljugador, double distancia) const;

    int decidir(const percepcion &p);
    int actuar(const percepcion &p);
    void aprender(bool acerto);
    void aprender(int decision, bool acerto);

};
#endif // AGENTE_H

```[cite: 1]