#include "juego.h"
#include "recursos.h"

#include <QBrush>
#include <QColor>
#include <QFont>
#include <QKeyEvent>
#include <QKeyEvent>
#include <QPainter>
#include <QPen>
#include <QRandomGenerator>
#include <algorithm>

namespace {
const int ancho= 1280;
const int alto = 720;
const double suelo = 655.0;
const double x_pepsi = 190.0;
const int total_niveles = 2;
const double x_jefe = 640.0;

}



template <typename t>
void juego::quitar(QVector<t*> &v, int i) {
    entidad *e= v[i];
    if(QGraphicsPixmapItem *g = items.take(e)) { escena->removeItem(g); delete g;}
    delete e;
    v.removeAt(i);
}

juego::confignivel juego::confignivel(int n) {
    confignivel c;
    auto capa = [&c](const char *ruta, double factor) {
        capacfg k; k.ruta = ruta; k.factor = factor; c.capas.append (k);

    };

    if (n==1) {
        c.nombre = "nivel 1";
        c.meta = "las palmas -> rionegro";
        capa(":/nivel1_01_cielo.png", 0.0);
        capa(":/nivel1_02_nubes.png",0.10);
        capa(":/nivel1_03_montanas_lejanas.png",0.20);
        capa(":/nivel1_04_montanas_medias.png",0.35);
        capa(":/nivel1_05_cerros_cercanos.png",0.60);
        capa(":/nivel1_06_carretera.png",1.00);
        c.velmundo = 260;
        c.nlatas= 10;
        c.nenemigos= 6;
        c.nbaches= 4;
        c.nllantas=3;
        c.nzarigueyas = 0;
        c.espaciomin = 420;
        c.espacioextra= 120;
        c.factorcadencia = 1.0;
        c.avalancha = false;
    }else{
        c.nombre = "nivel 2";
        c.meta = "rionegro -> marinilla -> el peñol";
        capa(":/nivel2_01_cielo.png", 0.0);
        capa(":/nivel2_02_nubes.png",0.10);
        capa(":/nivel2_03_montanas_lejanas.png",0.20);
        capa(":/nivel2_04_montanas_medias.png",0.35);
        capa(":/nivel2_05_cerros_cercanos.png", 0.60);
        capa(":/nivel2_06_carretera.png",1.00);
        c.monumento = ":/penol_meta.png";
        c.velmundo = 300;
        c.nlatas = 10;
        c.nenemigos = 10;
        c.nbaches = 4;
        c.nllantas = 3;
        c.nzarigueyas= 6;
        c.espaciomin = 380; c.espacioextra= 100;
        c.factorcadencia = 0.8;
        c.avalancha = true;
        c.jefe = true;






    }

}




