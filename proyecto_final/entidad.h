#ifndef ENTIDAD_H
#define ENTIDAD_H

class entidad{
protected:

    double x, y; //esta es la pocicion  de las entidades o personajes
    double vx, vy; //velocidad de una particula

    int vida;


public:

    entidad(double x, double y, int vida);
    virtual ~entidad();

    virtual void actualizar (double dt)=0;



    double getx() const;
    double gety() const;
    int getvida() const;
    bool estaviva () const;

    void resibirdano(int d);
    void setvelocidad(double vx, double vy);

};

#endif // ENTIDAD_H
