#include "barrera.h"
#include <QPainter>

Barrera::Barrera(float Separacion_barrera, int vida_, float x_, float y_, float ancho_, float alto_){
    x=x_;
    y=y_;
    ancho=ancho_;
    alto=alto_;
    Separacion_barrera=Separacion_barrera;
}


void Barrera::Dibujar(QPainter &P)

{
    QPolygon B;

    // Dibujar usando las coordenadas propias de la barrera
    B << QPoint(x - ancho/2, y - alto)
      << QPoint(x + ancho/2, y - alto)
      << QPoint(x + ancho/2, y - 2*alto)
      << QPoint(x - ancho/2, y - 2*alto);

    P.setPen(Qt::white);
    P.setBrush(Qt::red);     // color de la barrera
    P.drawPolygon(B);
}
