#include "alien.h"

Alien::Alien( int vida_, float x_, float y_, float ancho_, float alto_)

{
    vida = vida_;
    x = x_;
    y = y_;
    ancho = ancho_;
    alto = alto_;

}


void Alien::movimiento(){
    x+=Vx;
    y+=Vy;
}
proyectil* Alien::Disparar()
{
    float x_proyectil = x;
    float y_proyectil = y + alto;  // Dispara desde la parte inferior del alien
    float ancho_proyectil = 3;
    float alto_proyectil = 10;
    float velocidad = 8;  // Positiva para que baje
    return new proyectil(velocidad, 1, x_proyectil, y_proyectil, ancho_proyectil, alto_proyectil);
}
