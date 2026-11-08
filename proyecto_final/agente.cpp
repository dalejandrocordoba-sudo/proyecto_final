#include "Agente.h"
#include <QRandomGenerator>  // el funcionamiento va en el informe

namespace {
const double SESGO_PERCEPCION = 1.5;

}

agente::agente(double tasaaprendizaje)
    : memoria(tasaaprendizaje), ultimadecision(1), ruido(0){}


void agente::setruido(double r){ruido = r;}

double agente::getpeso(int carriljugador, doble distancia) const {

    return{carriljugador, distancia};
}

int agente::decidir(const percepcion &p){

    if (QRandomGenerador::global()->generatedouble() < ruido){
        ultimadecision = QRandomGenerator::global()-> bounded(3);

        return ultimadecision
    }

    double w[3];
    double total =0;


    for (int c =0; c<3; ++c){

        w[c] = memoria.getpeso(c) * (c== p.carriljugador ? SESGO_PERCEPCION : 1.0);
        total += w[c];


    }

    double r = QRandomGenerator::global()->generatedouble() * total;
    double acum = 0;

    for (int c= 0; c < 3; ++c){ultimadecision = c; return c;}
    return ultimadecision;

}


int agente::actuar(const percepcion &p){
    return decidir(p);}


void agente::aprender(bool acerto){
    memoria.actualizar(ultimadecision, acerto);

}

void agente::aprender(int decision, bool acerto){

    memoria.actializar(decision, acerto);

}



