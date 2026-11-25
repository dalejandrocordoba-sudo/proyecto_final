#ifndef FISICA_H
#define FISICA_H
#include <QPointF>

class fisica{

public:

    virtual ~fisica();
    virtual QPointF posicion(double t) const=0;


};

class movrectilineo: public fisica
{

    double x0, y0, vx, yv;

public:
    movrectilineo(double x0, double y0, double vx, double vy);
    QPointF posicion(double t) const override;

};


class movparabolico : public fisica{

    double x0, y0, v0, angulo, g; //angulo en radianes

public:
    movparabolico(double x0, double y0, double v0, double angulo, double g = 9.8);
    QPointF posicion(double t) const override;

};


class movoscilatorio : public fisica{

    double xc, yc, amplitud, omega, face, vy;


//movimiento oscilatorio
public:
    movoscilatorio(double xc, double yc, double amplitud, double omega, double fase, doble vy);
    QPointF posicion(double t) const override;

};


// friccion

class movfriccion : public fisica {


    double s0, v0, a;

public:

    movfriccion(double s0, double v0, double theta, doble mu, double g= 9.8);
    QPointF posicion(double t) const override;

};


//movimiento oscilatorio vertical

class movoscilatoriovertical : public fisica{

    double x0, y0, vx, amplitud, omega, fase;

public:
    movoscilatoriovertical(double x0, double y0, double vx, double amplitud, double omega, double fase);
    QPointF posicion(double t) const override;

};


class movcaidarebote : public fisica {
    double x0, y0, vx, ysuelo, g, e;
public:
    movcaidarebote(double x0, double y0, double vx, double ysuelo, double g, double e);
    QPointF posicion(double t) const override;
};





#endif // FISICA_H
