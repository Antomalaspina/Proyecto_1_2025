#ifndef CANGREJO_H
#define CANGREJO_H

#include "alien.h"

class cangrejo :public Alien
{
public:
    cangrejo(int vida_,float x_, float y_,float ancho_, float alto_, float separacion_alien);
    void Dibujar(QPainter &Qpainter) override ;
};

#endif // CANGREJO_H
