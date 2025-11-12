#ifndef PULPO_H
#define PULPO_H

#include "alien.h"

class Pulpo : public Alien
{
public:
    Pulpo(int vida_,float x_, float y_,float ancho_, float alto_, float separacion_alien);
    void Dibujar(QPainter &P) override ;
    QRectF get_area() const override;
};

#endif // PULPO_H
