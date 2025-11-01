#include "pulpo.h"
#include <QPainter>

pulpo::pulpo(int vida_, float x_, float y_, float ancho_, float alto_, float separacion_alien)
    : Alien(separacion_alien, vida_, x_, y_, ancho_, alto_)
{

}

void pulpo::Dibujar(QPainter &Qpainter)
{

}
