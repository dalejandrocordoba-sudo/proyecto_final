#include "animacion.h"
#include "recursos.h"
#include <algorithm>

animacion::animacion() : fps(10), t(0), repetir(true) {}

animacion::animacion (const QString &prefijo, int cantidad,double fps, bool repetir,double escala)
    : fps(fps), t(0), repetir(repetir) {
    for (int i = 1; i <= cantidad; ++i) {
        QString ruta = QString(":/%1_%2.png").arg(prefijo).arg(i,2,10, QChar('0'));
        QPixmap f = cargarsprite(ruta);
        if ( escala != 1.0) f = f.scaledToHeight(int(f.height()*escala), Qt::SmoothTransformation);
        frames.append(f);
    }
}

void animacion::avanzar(double dt) { t += dt; }
void animacion::reiniciar() { t = 0; }

bool animacion::terminada() const {
    return !repetir && int(t * fps) >= frames.size();
}

const QPixmap& animacion::actual() const {
    static const QPixmap vacio;
    if (frames.isEmpty()) return vacio;
    int idx = int(t * fps);
    if (repetir) idx %= frames.size();
    else idx = std::min(idx, int(frames.size())- 1);
    return frames[idx];
}
