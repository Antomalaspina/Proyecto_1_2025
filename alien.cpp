#include "alien.h"

Alien::Alien(float separacion_alien, int vida_, float x_, float y_, float ancho_, float alto_)

{
    vida = vida_;
    x = x_;
    y = y_;
    ancho = ancho_;
    alto = alto_;
    this->separacion_alien = separacion_alien;
}

// void Alien::set_x(float x_alien_movimiento)
// {
// x = x_alien_movimiento;

// }

// void Alien::set_y(float y_alien_movimiento)
// {
//  y = y_alien_movimiento;
// }

//✅ Ya no hacen falta los set_y o set_x, separacion_aliens ta'al pedo, nunca lo usas
//podrias usarlo, pero tendría que ser un atributo o variable de gamelogic no de alien
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
