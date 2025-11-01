#include "pulpo.h"
#include <QPainter>

Pulpo::Pulpo(int vida_, float x_, float y_, float ancho_, float alto_, float separacion_alien)
    : Alien(separacion_alien, vida_, x_, y_, ancho_, alto_)

{
    vida=vida_;
    x=x_;
    y=y_;
    alto=alto_;
    separacion_alien=separacion_alien;

}

void Pulpo::Dibujar(QPainter &P)
{
    QPolygon pul;

    // Dibujar usando las coordenadas propias de la barrera
    pul << QPoint(x - ancho/2, y - alto)
      << QPoint(x + ancho/2, y - alto)
      << QPoint(x + ancho/2, y - 2*alto)
      << QPoint(x - ancho/2, y - 2*alto);

    P.setPen(Qt::white);
    P.setBrush(Qt::blue);     // color de la barrera
    P.drawPolygon(pul);
}
