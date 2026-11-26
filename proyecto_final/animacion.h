#ifndef ANIMACION_H
#define ANIMACION_H

#include <QPixmap>
#include <QString>
#include <QVector>

class animacion {
    QVector<QPixmap> frames;
    double fps;
    double t;
    bool repetir;

public:
    animacion();
    animacion(const QString &prefijo, int cantidad, double fps, bool repetir = true, double escala = 1.0);


    void avanzar(double dt);
    void reiniciar();
    bool terminada() const;
    const QPixmap& actual() const;
};



#endif // ANIMACION_H
