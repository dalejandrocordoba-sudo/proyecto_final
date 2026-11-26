#include "jefebandolero.h"

jefebandolero::jefebandolero(fisica *f, double x, double y, double tasaaprendizaje)
    :enemigo(f, x, y), agente(new agente(tasaaprendizaje)),
    vidamaxima(10), anclado(false), preparado(false){

    vida=vidamaxima;
}


jefebandolero::jefebandolero(){delete agente; }

agente* jefebandolero::getagente(){return agente; }
int jefebandolero::getvidamaxima() const{return vidamaxima; }
bool jefebandolero::estaanclado() const{return anclado; }
bool jefebandolero::estapreparado() const {return preparado;}

void jefebandolero::anclar(double xpantalla){
    delete fisica;
    fisica = new movrectilineo(xpantalla, y, 0, 0);
    t = 0;
    anclado= true;
    tdisparo = 0;

}


bool jefebandolero::actualizarataque(double dt, double cadencia, double aviso){


    if (congelado || !anclado) { preparando = false; return false; }
    tdisparo += dt;
    preparando = tdisparo >= cadencia - aviso;
    if (tdisparo >= cadencia) {
        tdisparo = 0;
        preparando = false;
        return true;

}
    return false;

}

bool jefebandolero::recibirimpacto(double vmundo){

    recibirdano(1);
    if (vida > 0) return false;     // todavía aguanta
    congelar(vmundo);
    preparando = false;
    return true;


}


