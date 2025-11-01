#ifndef DIBUJABLE_ABSTRACTO_H
#define DIBUJABLE_ABSTRACTO_H
#include <QPainter>

class Dibujable_abstracto
{
private:
    int vida;
    float x;
    float y;
    float ancho;
    float alto;

public:
    Dibujable_abstracto(int vida_,float x_, float y_,float ancho_, float alto_);
    float get_x();
    float get_y();
    float get_ancho();
    float get_alto();
    virtual void Dibujar(QPainter &Qpainter)=0;
};

#endif // DIBUJABLE_ABSTRACTO_H
