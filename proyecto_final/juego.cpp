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
        p.setRenderHint(QPainter::Antialiasing);
        p.setPen(QPen(QColor("#ffd34d"),2));
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
    textopuntos->setPen(QPen(Qt::black,1));
    textopuntos->setPos(24,12);
    textopuntos->setZValue(100);

    for(int i = 0; i< 8; ++i)
    { QGraphicsPixmapItem *v = escena->addPixmap(pixvida);
        v->setPos(24+i*32,58);
        v->setZValue(100);
        vidashud.append(v);
}

    textonivel = escena->addSimpleText("Nivel 1", fuente);
    textonivel->setBrush(Qt::white);
    textonivel->setPen(QPen(Qt::black,1));
    textonivel->setPos(560,12);
    textonivel->setZValue(100);

    jefebarrafondo =escena->addRect(0,0,120,10,QPen(Qt::white,2),QBrush(QColor(40,40,40,200)));
    jefebarravida = escena->addRect(0,0,120,10, QPen(Qt::NoPen), QBrush(QColor("#d62828")));
    jefebarrafondo->setZValue(60);
    jefebarravida->setZValue(61);
    jefeaviso = escena->addSimpleText("!",QFont("Arial",40,QFont::Bold));
    jefeaviso->setBrush(QColor("#ffd34d"));
    jefeaviso->setPen(QPen(Qt::black,2));
    jefeaviso->setZValue(62);
    textoaprendizaje = escena->addSimpleText("El jefe aprende a disparar:",QFont("Arial",11,QFont::Bold));
    textoaprendizaje->setBrush(Qt::white);
    textoaprendizaje->setPen(QPen(Qt::black,1));
    textoaprendizaje->setPos(900,76);
    textoaprendizaje->setZValue(100);
    const char *alturas[3] = {"Alto", "Medio","Bajo"};
    for(int c =0; c < 3; ++c) {
        QGraphicsSimpleTextItem *et = escena->addSimpleText(alturas[c], QFont("Arial",11,QFont::Bold));
        et->setBrush(Qt::white);
        et->setPen(QPen(Qt::black,1));
        et->setPos(900,98+c*24);
        et->setZValue(100);
        etiquetaspeso.append(et);
        QGraphicsRectItem *b = escena->addRect(965,100 +c * 24,10,14, QPen(Qt::white,1),QBrush(QColor("#d62828")));
        b->setZValue(100);
        barraspeso.append(b);
    }
    mostrarpaneljefe(false);

    velo = escena->addRect(0,0,ancho,alto,QPen(Qt::NoPen),QBrush(QColor(0,0,0,120)));
    velo->setZValue(150);
    velo->setVisible(false);
    mensaje = escena->addSimpleText("",QFont("Arial",28,QFont::Bold));
    mensaje->setBrush(Qt::white);
    mensaje->setPen(151);
    mensaje->setVisible(false);

    timeravalancha = new QTimer(this);
    connect(timeravalancha,&QTimer::timeout(),this,&juego::avalancha);

    reloj.start();
    iratitulo();

    timer= new QTimer(this);
    connect(timer, &QTimer(this);
    connect(timer,&QTimer::timeout,this, &juego::tick);
    timer->start(16);

    }

juego::~juego() {
    limpiar();
    delete fondo;
}

void juego::iratitulo() {
    cargarnivel(1);
    estado = estado::titulo;
    mostrarmensaje(textotitulo());

}
QString juego::textotitulo() const {
    const QString nombres[] = { "facil","normal","dificil"};
    return QString ("PEPSIMAN DA LA VUELTA A COLOMBIA\n\n"
                    "Dificultad: %1 (teclas 1/ 2/3)\n\n"
                    "ENTER =jugar\n"
                    "shift = ir directo al nivel 2 (para pruebas)\n\n"
                    "↑/ W saltar ESPACIO lanzar lata")
            .arg(nombres[dificultadelegida-1]);
}

void juego::cargarnivel(int n) {
    timeravalancha->stop();
    limpiar();
    fondo->limpiar();
    if (monumento) { escena->removeItem(monumento); delete monumento;monumento = nullptr; }

    nivelactual = n;
    cfg = confignivel(n);
    int z = 0;
    for (const capacfg &c : cfg.capas) fondo->agregarcapa(c.ruta,c.factor,z++);


    mundox = 0;
    siguienteevento = 0;
    tlanzar = 0;
    animpedaleo.reiniciar();
    generarguion();

    if(!cfg.monumento.idEmpty()) {
        monumento = escena->addPixmap(cargarsprite(cfg.monumento).scaledtoheight(450,Qt::SmoothTransformation));
        monumento->setZValue(4.5);
        actualizarmonumento();
    }
    pepsiman = new pepsiman(x_pepsi, suelo);
    itempepsi = crearitem(pepsiman, animpedaleo.actual(), 11);

    textonivel->setText(cfg.nombre);
    textometa->setText(cfg.meta);
    velo->setVisible(false);
    mensaje->setVisible(false);
}

void juego::terminarnivel(estado nuevo,const QString &texto) {
    estado = nuevo;
    timeravalancha->stop();
    mostrarmensaje(texto);
}

void juego::limpiar() {
    while (!enemigos.isEmpty()) quitarenemigo(0);
    while (!latas.isEmpty()) quitar(latas,0);
    while (!balas.isEmpty()) quitar(balas,0);
    while (!objetos.isEmpty()) quitar(objetos,0);
    while(!balasjefe.isEmpty()) quitar(balasjefe,0);
    jefe = nullptr;
    mostrarpaneljefe(false);
    if (pepsiman) {
        if (QGraphicsPixmapItem *g = items.take(pepsiman)) { escena->removeItem(g); delete g; }
        delete pepsiman;
        pepsiman = nullptr;
        itempepsi = nullptr;
    }
}

void juego::generarguion() {
    guion.clear();
    QVector<int> tipos;
    tipos += QVector<int> (cfg.nlartas, 3);
    tipos += QVector<int> (cfg.nenemigos, 0);
    tipos += QVector<int>(cfg.nbaches,1);
    tipos += QVector<int>(cfg.nllantas,2);
    tipos += QVector<int>(cfg.nzarigueyas, 4);
    std::shuffle(tipos.begin(), tipos.end(), *QRandomGenerator::global());
    if (cfg.jefe) tipos.insert(tipos.begin()+ tipos.zise() * 2 / 3, 5);

    double x = 1500;
    for (int t : tipos) {
        evento ev;
        ev.x = x;
        ev.tipo = t;
        ev.alta = (t == 3) && QRandomGenerator::global()->bounded(3) == 0;
        guion.append(ev);
        x += cfg.espaciomin + QRandomGenerator::global()->bounded(cfg.espacioExtra);
        if( == 5) x += 700;
    }
    largonivel = x +900;
}

void juego::generarevento(const evento &ev) {
    double sx = ev.x - mundox;
    double v = cfg.velmundo;
    bool peleando = jefe && jefe->estaanclado() & !jefe->estacongelado();
    if (peleando && (ev.tipo == 0 || ev.tipo == 4)) return;

    if(ev.tipo == 5) {
        jefebandolero *j = new jefebandolero(new movrectilineo(sx, 650, -(v + 170), 0), sx, 650, dificultad.tasaaprendizaje);
        j->getagente()->setruido(dificultad.precision);
        jefe = j;
        flashjefe= 0;
        animenemigos. insert(j, animjefe);
        enemigos.append(j);
        crearitem(j, animjefe.actual(), 10);
        mostrarpaneljefe(true);
    }else if (ev.tipo == 0) {
        enemigo *e = new enemigo(new movrectilineo(sx,650, -(v + 90),0), sx,650);
        animacion a = animenemigo;
        a.avanzar(QRandomGenerator::global()->bounded(1.0));
        animenemigos.insert(e,a);
        enemigos.append(e);
        crearitem(e, a.actual(),10);
    }else if (ev.tipo == 1) {
        objetomundo *o = new objetomundo(tipoobjeto::bache, new movrectilineo(sx,690, -v, 0), sx, 690);
        objetos.append(o);
        crearitem(o, pixhueco, 8);
    }else if (ev.tipo == 2) {
        objetomundo *o = new objetomundo(tipoobjeto::llantas,new movrectilineo(sx,662, -v , 0),sx,662);
        objetos.append(o);
        crearitem(o,pixllantas, 9);
    }else if (ev.tipo == 3) {
        double y = 630 - (ev.alta ? 130 : 0);
        objeromundo *o = new objeromundo(tipoobjeto::lata,new movrectilineo(sx, y, -v, 0),sx, y );
        objetos.append(o);
        crearitem(o, pixlata, 9);
    } else {
        double fase = QRandomGenerator::global()->bounded(6.28);
        double y0 = suelo - 30;
        objetomundo *o new objetomundo(tipoobjeto::zarigueya,
                                       new movoscilatoriovertical(sx, y0, -(v + 70), 30, 7.0, fase), sx, y0);
        objetos.append(0);
        crearitem(o, pixzarigueya, 10);
    }
}


void juego::avalancha() {
    if (estado != estado::jugando) return;
    for (int i = 0;i < 1; ++i) {
        double sx = ancho + 60 + i * 150;
        double y0 = -80 - i * 40;
        objetomundo *o = new objetomundo(tipoobjeto::llantarebote,
                                         new movcaidarebote(sx, y0, -(cfg.velmundo + 80), 662, 1400,0.6), sx, y0);
        objetos.append(o);
        crearitem(o, pixrueda, 9);
    }
}

void juego::tick() {
    double dt = reloj.restart() / 1000.0;
    if (dt > 0.05) dt = 0.05;

    if (estado == estado::jugando) actualizarjuego(dt);
    actualizarhud();
}

void juego::actualizarjuego(double dt) {
    mundox += cfg.velmundo * dt;
    fondo->avanzar( cfg.velmundo * dt);
    actualizarmonumento();

    while (siguienteevento < guion.size() && guion[siguienteevento].x - mundox < ancho + 80) {
        generarevento(guion[siguienteevento]);
        ++siguienteevento;
    }

    pepsiman->actualizar(dt);
    animpedaleo.avanzar(dt);
    if (tlanzar > 0 ) { tlanzar -= dt; animlanzar.avanzar(dt); }
    if (tlanzar > 0) itempepsi->setPixmap(animlanzar.actual());
    else if (pepsiman->enaire()) itempepsi->setPixmap(pixsalto);
    else itempepsi->setPixmap(animpedaleo.actual());
    bool parpadeo = pepsiman->esinculnerable() && (int(pepsiman->tiempoinvulnerable() * 12) % 2 == 0 );
    itempepsi-setOpacity(parpadeo ? 0.35 : 1.0);

    double cadencia = dificultad.cadenciadisparo * cfg.factorcadencia;
    for(int i = enemigo.size() - 1; i>= 0 ; --i) {
        enemigo *e = enemigos[i];
        e->actualizarjefe(dt);
        if (e == jefe) {
            actualizarjefe(dt);
        }else if (!e->estacongelado()) {
            animenemigos[e].avanzar(dt);
            items[e]->setpixmap(animenemigos[e].actual());
            if (e->getx()< 1150 && e->debedisparar(dt, cadencia)) disparar(e);
        }
        if (e->getx() < -160) quitarenemigo(i);
    }

    for(int i = latas.size() - 1; i >= 0; --i) {
        latas[i]->actualizar(dt);
        if (latas[i]->getx() > ancho + 60 || latas[i]->gety() > suelo + 10) quitar(latas, i);
    }
    for(int i = latas.size() - 1; i >= 0; --i) {
        latas[i]->actualizar(dt);
        if(balasjefe[i]->getx() < -40) quitar(balas, i);

    }
    for (int i = balasjefe.size() - 1; i >= 0; --i) {
        balasjefe[i]->actualizar(dt);
        if(balasjefe[i]->getx() < -40) {
            if(jefe) jefe->getagente()->aprender(balasjefe[i]->getcarril(), false);
            quitar(balasjefe, i);
        }
    }
    for (int i = objetos.size() - 1; i >= 0; --i) {
        objetos[i]->actualizar(dt);
        if(objetos[i]->getx() < -250) quitar(objetos, i);
    }

    sincronizar();
    colisiones();

    if (estado == estado::jugando && mundox >= largonivel) {
        if (nivelactual < total_niveles) {
            terminarnivel(estado::nivelcompletado,
                          QString(" llegaste a rionegro ¡¡¡¡ \n puntos : %1  vidas: %2\n\n"
                                  "enter = nivel 2\n(rionegro -> marinilla -> el peñol)")
                              .arg(pepsiman->getpuntos()));
        }
    }
}

void juego::actualizarmonumento() {
    if(!monumento) return;
    const QPixmap &p = monumento->pixmap();
    monumento->setPos(largonivel + 260 - mundox -p.width() / 2.0,585 - p.height());

}

void juego::sincronizar() {
    for (auto it = items.begin(); it != item.end(); ++it) {
        const QPixmap &p = it.value()->pixmap();
        it.value()->setPos(it.key()->getX()-p.width() / 2.0, it.key()->gety() - p.height());

    }
}

void juego::colisiones() {
    QRectF rf = cajade(pepsiman,30,14);
    QRectF pies(pepsiman->getx() - 30, pepsiman->gety() -6,60, 6);


    for ( int i = latas.size() - 1; i >= 0; --i) {
        QRectF rl = cajade(latas[i],2,2);
        bool usada = false;
        for (enemigo *e : enemigos) {
            if(e->estacongelado()) continue;
            if(rl.intersects(cajade(e, 20, 8))) {
                if(e->recibirimpacto(cfg.velmundo)) {
                    items[e]->setpixmap(e == jefe ? pixcongeladojefe : pixcongelado);
                    if(e == jefe) {
                        pepsiman->sumarpuntos(500);
                        mostrarpaneljefe(false);
                    }
                } else if ( e == jefe) {
                    flashjefe = 0.25;
                }
                usada = true;
                break;
            }
        }
            if (!usada) {
                for (int j = objetos.size() - 1 ; j >= 0; --j) {
                    if(objetos[j]->gettipo() != tipoobjeto::zarigueya) continue;
                    if (rl.intersects(cajade(objeros[j],8,8))) { quitar(objetos, j); usada= true; break; }
                }

            }
            if (usada) quitar(latas, i);
        }

        /*cuando tocan a pepsiman los enemigos*/
        for (enemigo *e : enemigos)
            if (!e->estacongelado() && rp.intersects(cajade(e, 22, 10))) golpe();
        /*balas de los enemigos*/
        for (int i = balas.size() - 1; i >= 0; --i) {
            if (estado != estado::jugando) break;
            if (rp.intersects(cajade(balas[i],0,0))) {golpe(); quitar(balas, i);}

        }
        /*balas del jefe el jefe verifica a que altura le pega y aprende  */
        for (int i = balasjefe.size() - 1; i >= 0; --i) {
            if (estado != estado::jugando) break;
            if (rp.intersects(cajade(balasjefe[i],0,0))) {
                if (jefe) jefe->getagente()-aprender(balasjefe[i]->getcarril(),true);
                golpe();
                quitar(balasjefe, i);
            }

        }

        for (int i = objetos.size() -1; i >= 0; --i) {
            if(estado != estado::jugando) break;
            objetomundo *o = objetos[i];
            switch (o->getTipo()) {
            case tipoobjeto::lata:
                if(rp.intersects(cajade(o, 4, 4))) {pepsiman->recogerlata();quitar(objetos, i); }
                break;
            case tipoobjeto::llantas:
                if (rp.intersects(cajade(o, 10, 12))) golpe();
                break;
            case tipoobjeto::zarigueya:
                if(rp.intersects(cajade(o,12,12))) golpe();
                break;
            case tipoobjeto::llantarebote:
                if(rp.intersects(cajade(o,8,8))) { golpe(); quitar(objetos, i); }
                break
            case tipoobjeto::bache: {
                QRectF r = cajade(o, 30,0);
                r.setTop(646);
                if (pies.intersects(r)) golpe();
                break;
            }
            }
        }


}








