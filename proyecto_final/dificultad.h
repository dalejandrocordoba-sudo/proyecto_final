#ifndef DIFICULTAD_H
#define DIFICULTAD_H


struct dificultad
{
    double tasaaprendizaje;
    double precision;
    double cadenciadisparo;
    double aviso;

};

dificultad creardificultad(int nivel);
#endif // DIFICULTAD_H
