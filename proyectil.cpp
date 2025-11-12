#include "proyectil.h"
#include <QPainter>

proyectil::proyectil(float velocidad_y_, int vida_, float x_, float y_, float ancho_, float alto_)
{
    Vy = velocidad_y_;
    vida = vida_;
    x = x_;
    y = y_;
    ancho = ancho_;
    alto = alto_;
}

QRectF proyectil::get_area() const{
    return QRectF(x - ancho/2, y - alto/2, ancho, alto);
}

void proyectil::movimiento()
{
    y += Vy; // Mover el proyectil según su velocidad
}

void proyectil::Dibujar(QPainter &P)
{
    P.setPen(Qt::yellow);
    P.setBrush(Qt::yellow);
    P.drawRect(x - ancho/2, y - alto/2, ancho, alto);
}
