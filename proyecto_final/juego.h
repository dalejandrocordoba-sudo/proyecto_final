#ifndef JUEGO_H
#define JUEGO_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QGraphicsRectItem>
#include <QElapsedTimer>
#include <Qhash>
#include <QString>
#include <QTimer>
#include <Qvector>

#include "animacion.h"
#include "fondoparallax.h"
#include "pepsiman.h"
#include "enemigo.h"
#include "proyectil.h"
#include "objetomundo.h"
#include "balaagente.h"
#include "jefebandolero.h"
#include "dificultad.h"


class juego : public QGraphicsView {
    Q_OBJECT
public:
    explicit juego(QWidget *parent = nullptr);
        ~juego() override;

protected:
    void keypressevent(QKeyEvent *e) override;
    void resizeevent(QResizeEvent *e) override;

private slots:
    void tick();
    void avalancha();

private:
    enum class estado { titulo, jugando, nivelcompletado, ganado, perdido };
    struct evento { double x; int tipo; bool alta; };
    struct capacfg { QString ruta; double factor;};

    struct confignivel {
        QString nombre, meta, monumento;
        QVector<capacfg> capas;
        double velmundo = 260;
        int nenemigos = 0, nbaches = 0, nllantas = 0, nlatas = 0, nzartigueyas = 0;
        int espaciomin = 420, espacioextra = 120;
        double factorcadencia = 1.0;
        bool avalancha = false;
        bool jefe = false;
    };
    static confignivel confignivel ( int n);

    QGraphicsScene *escena = nullptr;
    QTimer *timer = nullptr;
    QTimer *timeravalcha = nullptr;
    QElapsedTimer reloj;
    fondoparallax *fondo = nullptr;
    estado estado = estado::titulo;
    dificultad dificultad;
    int dificultadelegida = 2;
    int nivelactual = 1;
    confignivel cfg;
    int puntosinicionivel = 0,vidasinicionivel = 3 ;

    animacion animpedaleo, animlanzar, animenemigo;
    QPixmap pixsalto,pixlata,pixlavolamdo,pixhue,pixllanta,pixbala,pixcongelado,pixvida;
    QPixmap pixzarigueya, pixrueda;
    QPixmap pixjefequieto,pixcongeladojefe,pixbalajefe;
    animacion animjefe;

    pepsiman *pepsiman = nullptr;
    QGraphicsPixmapItem *itempepsi = nullptr;
    QGraphicsPixmapItem *monumento = nullptr;
    QVector<enemigo*> enemigos;
    QVector<proyectil*> latas;
    QVector<proyectil*> balas;
    QVector<balaagente*> balasjefe;
    jefebandolero *jefe = nullptr;
    double flashjefe = 0;
    QVector<objetomundo*> objetos;
    QHash<entidad*, QGaphicsPixmapItem*> items;
    QHash<enemigo*,animacion>animenemigos;

    QVector<evento> guion;
    int siguienteevento= 0;
    double mondox = 0;
    double largonivel = 1;
    double tlanzar = 0;

    QGraphicsSimpleTextItem *textopuntos = nullptr;
    QGraphicsSimpleTextItem *textonivel = nullptr;
    QGraphicsSimpleTextItem *textometa = nullptr;
    QGraphicsSimpleTextItem *mensaje = nullptr;
    QGraphicsRectItem *velo= nullptr;
    QGraphicsRectItem *barrafondo = nullptr;
    QGraphicsRectItem *barrarelleno = nullptr;
    QVector<QGraphicsPixmapItem*> vidashud;
    QGraphicsRectItem *jefebarrafondo= nullptr;
    QGraphicsRectItem *jefebarravida = nullptr;
    QGraphicsSimpleTextItem *jefeaviso = nullptr;
    QGraphicsSimpleTextItem *textoaprendizaje = nullptr;
    QVector<QGraphicsSimpleTextItem*> etiquetaspeso;
    QVector<QGraphicsRectItem*> barraspeso;

    void iratitulo();
    void cargarnivel (int n);
    void iniciarnivel (int n, int puntos, int vidad);


}

};

#endif // JUEGO_H
