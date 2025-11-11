#include "proyectil.h"
#include <QPainter>

// Constructor: asigna velocidad, posición, tamaño y vida del proyectil
proyectil::proyectil(float velocidad_y_, int vida_, float x_, float y_, float ancho_, float alto_)
{
    Vy = velocidad_y_;  // Velocidad vertical (negativa = sube, positiva = baja)
    vida = vida_;       // Vida del proyectil (normalmente 1)
    x = x_;             // Posición inicial X
    y = y_;             // Posición inicial Y
    ancho = ancho_;     // Ancho gráfico del proyectil
    alto = alto_;       // Alto gráfico del proyectil
}

// Devuelve el rectángulo que ocupa el proyectil (para colisiones)
QRectF proyectil::get_area() const {
    return QRectF(x - ancho/2, y - alto/2, ancho, alto);
}

// Actualiza su posición moviéndolo verticalmente
void proyectil::movimiento()
{
    y += Vy; // Desplaza según su velocidad vertical
}

// Dibuja el proyectil como un rectángulo amarillo
void proyectil::Dibujar(QPainter &P)
{
    P.setPen(Qt::yellow);
    P.setBrush(Qt::yellow);
    P.drawRect(x - ancho/2, y - alto/2, ancho, alto);
}
