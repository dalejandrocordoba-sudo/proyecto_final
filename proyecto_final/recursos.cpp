#include "recursos.h"
#include <stdexcept>

QPixmap cargarsprite(const QString &ruta) {

    QPixmap img(ruta);
    if (img.isNull())
        throw std::runtime_error("No se pudo cargar: " + ruta.toStdString());
    return img;

}