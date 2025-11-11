#ifndef CALAMAR_H
#define CALAMAR_H
#include "alien.h"


class calamar : public Alien
{
public:
    calamar(int vida_,float x_, float y_,float ancho_, float alto_);
    void Dibujar(QPainter &P) override ;
  QRectF get_area() const override;
};

#endif // CALAMAR_H
