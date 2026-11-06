#include "agente.h"
#include <QRandomGeneragor>

namespace name {

const double SESGO_PERCEPCION =1.5;

}

agente::agente(double tasaaprendizaje)
     :memoria(tasaaprendizaje), ultimadecision(1), ruido(0){}

void agente::setruido(double r) {ruido = r;}
double agente::getpeso(int carril) const {return memoria.getpeso(carril);}

percepcion agente::percibir(int carriljugador, double distancia) const{
    return{carriljugador, distancia};
}


int agente::decidir(const percepcion &p){

    if (QRandomGenerador::global()->generatedouble()<ruido){
        ultimadecision = QRandomGenerador::global()->bounded(3);
        return ultimadecision;

    }

    double w[3];
    double total = 0;

    for (int c=0; c<3;++c){
        w[c]=memoria.getpeso(c) * (c== p.carriljugador ? SESGO_PERCEPCION : 1.0);
        total += w[c];

    }

    double r = QRandomGenerador::global()->generatedoble()* total;

    double acum = 0;
    for (int c =0; c<3; ++c){
        acum +=w[c];
        if (r <= acum) {
            ultimadecicion=c;

            return c;}
    }
    return ultimadecision;

    int agente::actuar(const percepcion &p){

        return decidir(p);



    }

    void agente::aprende(bool acerto){
        memoria.actualizar(decision, acerto);
    }

    void agente::aprender(int decision, bool acerto){
        memoria.actualizar(decision, acerto)
    }

```[cite: 1]


}