#ifndef MEMORIA_H
#define MEMORIA_H
#include <QMap>

class meroria{
    QMap <int, double> pesos;
    double tasa;

public:
    explicit memoria(double tasa = 0.2);
    double getpeso(int carril) const;
    void actualizar(int carril, bool acierto);

};
#endif // MEMORIA_H
