#ifndef PROYECTIL_H
#define PROYECTIL_H

#include "colisionable.h"        // Permite detectar colisiones
#include "dibujable_abstracto.h" // Define posición, tamaño y dibujado
#include "movil.h"               // Define velocidades y movimiento

// Clase proyectil: representa balas tanto del jugador como de los aliens.
// Hereda comportamiento de colisión, dibujo y movimiento.
class proyectil: public colisionable, public Dibujable_abstracto, public movil
{

public:
    // Constructor: inicializa velocidad vertical, vida y dimensiones del proyectil
    proyectil(float velocidad_y, int vida_, float x_, float _y, float ancho_, float alto_);

    // Área rectangular usada para colisiones
    QRectF get_area() const override;

    // Dibujo gráfico del proyectil
    void Dibujar(QPainter &P) override;

    // Movimiento vertical según la velocidad Vy
    virtual void movimiento() override;
};

#endif // PROYECTIL_H
