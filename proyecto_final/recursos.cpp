#include "recursos.h"
#include <stdexcept>

Qpixmap cargarstrite(const QString &ruta) {

    Qpixmap img(ruta);
    if (img.isNull())
        throw std::runtime_error("No se pudo cargar: " + ruta.tostdstring());
    return img;

}