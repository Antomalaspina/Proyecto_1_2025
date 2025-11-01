#ifndef CALAMAR_H
#define CALAMAR_H
#include "alien.h"


class calamar : public Alien
{
public:
    calamar(int vida_,float x_, float y_,float ancho_, float alto_, float separacion_alien);
     void Dibujar(QPainter &Qpainter) override ;

};

#endif // CALAMAR_H
