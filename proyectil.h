#ifndef PROYECTIL_H
#define PROYECTIL_H
#include <QPainter>
#include "dibujable_abstracto.h"

#include "dibujable_abstracto.h"
class proyectil: public Dibujable_abstracto
{
private:
    float velocidad_y;
public:
    proyectil(float velocidad_y, int vida_, float x_,float _y,float ancho_,float alto_);
    float set_y(float y_proyectil);
    void Dibujar(QPainter &Qpainter) override ;

};

#endif // PROYECTIL_H
