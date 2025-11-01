#ifndef NAVE_H
#define NAVE_H
#include "dibujable_abstracto.h"
#include <QPainter>

class Nave: public Dibujable_abstracto
{
public:
    Nave();
    float set_x(float x_nave_nueva);
    void Dibujar(QPainter &Qpainter) override ;

};

#endif // NAVE_H
