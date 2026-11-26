#ifndef FONDOPARALLAX_H
#define FONDOPARALLAX_H


#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QString>
#include <QVector>



class fondoparallax {
    struct capa {
        QGraphicsPixmapItem *a = nullptr;
        QGraphicsPixmapItem *b = nullptr;
        double factor = 0;
        double desplazamiento = 0;
        int ancho = 1;

    };
    QGraphicsScene *escena;
    QVector<capa> capas;
public:
    explicit fondoparallax(QGraphicsScene *escena);
    void agregarcapa(const QString &ruta, double factor, int z);
    void avanzar(double pixelesmundo);
    void limpiar();
};

#endif // FONDOPARALLAX_H
