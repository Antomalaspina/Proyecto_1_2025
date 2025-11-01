#ifndef DIBUJABLE_ABSTRACTO_H
#define DIBUJABLE_ABSTRACTO_H
#include <QPainter>

class Dibujable_abstracto
{
protected:
    int vida;
    float x;
    float y;
    float ancho;
    float alto;

public:
    float get_x();
    float get_y();
    float get_ancho();
    float get_alto();
    virtual void Dibujar(QPainter &P)=0;
};

#endif // DIBUJABLE_ABSTRACTO_H
