#include "Fisica.h"
#include <cmath>
#include <algorithm>



fisica::~fisica() {}



// movimiento rectilineo

movrectilineo::movrectilineo(double x0, double y0, double vx, double vy)
    : x0(x0), y0(y0), vx(vx), vy(vy) {}

QPointF movrectilineo::posicion(double t) const {
    return QPointF(x0 + vx * t, y0 + vy * t);
}





//movimiento parabolico

movparabolico::movparabolico(double x0, double y0, double v0, double angulo, double g)
    : x0(x0), y0(y0), v0(v0), angulo(angulo), g(g) {}

QPointF movparabolico::posicion(double t) const {
    double px = x0 + v0 * std::cos(angulo) * t;
    double py = y0 - (v0 * std::sin(angulo) * t - 0.5 * g * t * t);
    return QPointF(px, py);
}





// movimiento oscilatorio

movoscilatorio::movoscilatorio(double xc, double yc, double amplitud, double omega, double fase, double vy)
    : xc(xc), yc(yc), amplitud(amplitud), omega(omega), fase(fase), vy(vy) {}

QPointF movoscilatorio::posicion(double t) const {
    return QPointF(xc + amplitud * std::sin(omega * t + fase), yc + vy * t);
}





// friccion

movfriccion::movfriccion(double s0, double v0, double theta, double mu, double g)
    : s0(s0), v0(v0), a(g * (std::sin(theta) - mu * std::cos(theta))) {}

QPointF movfriccion::posicion(double t) const {
    double tstop = (a < 0 && v0 > 0) ? -v0 / a : t;
    double tt = std::min(t, tstop);
    return QPointF(s0 + v0 * tt + 0.5 * a * tt * tt, 0);
}





// movimiento osilatorio pero vertical
movoscilatoriovertical::movoscilatoriovertical(double x0, double y0, double vx, double amplitud, double omega, double fase)
    : x0(x0), y0(y0), vx(vx), amplitud(amplitud), omega(omega), fase(fase) {}

QPointF movoscilatoriovertical::posicion(double t) const {
    return QPointF(x0 + vx * t, y0 + amplitud * std::sin(omega * t + fase));
}







//caida y rebote

movcaidarebote::movcaidarebote(double x0, double y0, double vx, double ysuelo, double g, double e)
    : x0(x0), y0(y0), vx(vx), ysuelo(ysuelo), g(g), e(e) {}

QPointF movcaidarebote::posicion(double t) const {
    double x = x0 + vx * t;
    double h0 = ysuelo - y0;
    if (h0 <= 0) return QPointF(x, ysuelo);
    double t0 = std::sqrt(2 * h0 / g);
    if (t <= t0) return QPointF(x, y0 + 0.5 * g * t * t);

    double s = t - t0;
    double v = e * g * t0;
    for (int i = 0; i < 40 && v > 25; ++i) {
        double duracion = 2 * v / g;
        if (s <= duracion) return QPointF(x, ysuelo - (v * s - 0.5 * g * s * s));
        s -= duracion;
        v *= e;
    }
    return QPointF(x, ysuelo);
}