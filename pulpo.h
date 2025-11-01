#ifndef PULPO_H
#define PULPO_H

#include "alien.h"

class pulpo : public Alien
{
public:
    pulpo(int vida_,float x_, float y_,float ancho_, float alto_, float separacion_alien);
    void Dibujar(QPainter &Qpainter) override ;
};

#endif // PULPO_H
