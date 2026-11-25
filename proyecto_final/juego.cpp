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
const int ancho = 1280;
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
    return c;
}

juego::juego(QWidget *parent) : QGraphicsView(parent) {
    escena = new QGraphicsScene(0,0,ancho,alto,this);
    setScene(escena);
    resize(ancho,alto);
    setWindowTitle("pepsiman da la vuelta a colombia");
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setFrameShape(QFrame::NoFrame)
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setFocusPolicy(Qt::StrongFocus);

    dificultad = creardificultad(dificultadelegida);
    fondo = new fondoparallax(escena);

    animpedaleo = animacion("pepsiman_pedalear_A",9,14);
    animlanzar = animacion("pepsiman_lanzar",4,14,false);
    animenemigo = animacion("bandolero_correr",7,10);
    pixsalto = cargarsprite(":/pepsiman_pedalear_B_01.png");
    pixlata = cargarsprite(":/sixpack.png").scaledToHeight(48,Qt::SmoothTransformation);
    pixlatavolando = cargarsprite(":/lata_volando.png").scaledToWidth(44, Qt::SmoothTransformation);
    pixhueco = cargarsprite(":/hueco.png").scaledToWidth(170,Qt::SmoothTransformation);
    pixllantas = cargarsprite(":/llantas.png").scaledToWidth(74,Qt::SmoothTransformation);
    pixcongelado = cargarsprite(":/congelado_3_iced.png").scaledToWidth(110,Qt::SmoothTransformation);
    pixvida = cargarsprite(":/lata_hud.png").scaledToWidth(42,Qt::SmoothTransformation);
    pixzarigueya = cargarsprite(":/zarigueya.png").scaledToWidth(76,Qt::SmoothTransformation);
    animjefe = animacion("bandolero_correr", 7, 9, true, 1.45);
    pixjefequieto = cargarsprite(":/bandolero_caminar_06.png").scaledToWidth(172,Qt::SmoothTransformation);
    pixcongeladojefe = cargarsprite(":/congelado_1_herido.png").scaledToWidth(170,Qt::SmoothTransformation);

    pixbala = QPixmap(14,14);
    pixbala.fill(Qt::transparent);
    {
        QPainter p(&pixbala);
        p.setrenderHint(QPainter::Antialiasing);
        p.setpen(QPen(QColor("#ffd34d"),2));
        p.setBrush(QColor("#222222"));
        p.drawEllipse(1,1,12,12);

    }
    pixbalajefe = QPixmap (26,26);
    pixbalajefe.fill(Qt::transparent);
    {
        QPainter p (&pixbalajefe);
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(QPen(QColor("#ffffff"), 2));
        p.setBrush(QColor("#c1121f"));
        p.drawEllipse(2,2,22,22);

    }
    pixrueda = QPixmap(58,58);
    pixrueda.fill(Qt::transparent);
    {
        QPainter p(&pixrueda);
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(QPen(QColor("#111111"), 3));
        p.setBrush(QColor("#2b2b2b"));
        p.drawEllipse(2,2,54,54);
        p.setBrush(QColor("#6b6b6b"));
        p.drawEllipse(24,24,10,10);
    }
    QFont fuente("Arial", 20,QFont::Bold);
    textopuntos = escena->addSimpleText("puntos: 0", fuente);
    textopuntos->setBrush(Qt::white);
    textopuntos->setPen()


}





