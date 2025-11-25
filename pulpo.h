#ifndef PULPO_H
#define PULPO_H

#include "alien.h"
// Pulpo hereda directamente de Alien. Alien ya incluye movimiento,
// colisiones, dibujo abstracto y velocidad horizontal.

class Pulpo : public Alien
{
public:
    // Constructor: inicializa vida, posición y tamaño, enviando
    // esos valores al constructor de Alien.
    Pulpo(int vida_, float x_, float y_, float ancho_, float alto_);

    // Dibuja el pulpo en pantalla (sobrescribe el método del padre).
    void Dibujar(QPainter &P) override;

    // Devuelve el área completa del pulpo para detección de colisiones.
    QRectF get_area() const override;
};

#endif // PULPO_H

