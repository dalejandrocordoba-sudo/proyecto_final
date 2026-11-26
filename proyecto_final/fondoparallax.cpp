#include "fondoparallax.h"
#include "recursos.h"
#include <cmath>

fondoparallax::fondoparallax(QGraphicsScene *escena) : escena(escena) {}

void fondoparallax::agregarcapa(const QString &ruta, double factor, int z) {
QPixmap pix = cargarsprite(ruta);
    capa c;
c.a = escena->addPixmap(pix);
    c.b = escena->addPixmap(pix);
c.a->setZValue(z);
c.b->setZValue(z);
c.b->setX(pix.width());
c.factor = factor;
c.ancho = pix.width();
capas.append(c);
}

void fondoparallax::avanzar(double pixelesmundo) {
    for (capa &c : capas) {
        c.desplazamiento = std::fmod(c.desplazamiento + pixelesmundo * c.factor, double(c.ancho));
        c.a->setX(-c.desplazamiento);
        c.b->setX(c.ancho - c.desplazamiento);

    }
}

void fondoparallax::limpiar() {
    for (capa &c : capas) {
        escena->removeItem(c.a);
        escena->removeItem(c.b);
        delete c.a;
        delete c.b;

    }
    capas.clear();
}