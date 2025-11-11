#include "alien.h"

// Constructor de la clase Alien
// Inicializa todos los atributos del alien con los valores pasados como parámetros
Alien::Alien(int vida_, float x_, float y_, float ancho_, float alto_)
{
    vida = vida_;      // Establece los puntos de vida del alien
    x = x_;            // Posición horizontal inicial
    y = y_;            // Posición vertical inicial
    ancho = ancho_;    // Ancho del alien (para detección de colisiones)
    alto = alto_;      // Alto del alien (para detección de colisiones)
}

// Método que actualiza la posición del alien
// Mueve el alien sumando las velocidades Vx y Vy a sus coordenadas actuales
void Alien::movimiento()
{
    x += Vx;  // Actualiza la posición horizontal
    y += Vy;  // Actualiza la posición vertical
}

// Método que crea y devuelve un proyectil disparado por el alien
proyectil* Alien::Disparar()
{
    // El proyectil aparece en la misma posición horizontal que el alien
    float x_proyectil = x;

    // El proyectil sale desde la parte inferior del alien (y + alto)
    float y_proyectil = y + alto;

    // Dimensiones del proyectil
    float ancho_proyectil = 3;
    float alto_proyectil = 10;

    // Velocidad positiva = el proyectil se mueve hacia abajo
    float velocidad = 8;

    // Crea y devuelve un nuevo proyectil dinámicamente
    // Parámetros: (velocidad, tipo?, x, y, ancho, alto)
    return new proyectil(velocidad, 1, x_proyectil, y_proyectil, ancho_proyectil, alto_proyectil);
}
