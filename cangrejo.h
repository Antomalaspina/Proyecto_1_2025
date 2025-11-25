#ifndef CANGREJO_H
#define CANGREJO_H

#include "alien.h"     // Incluye la clase base Alien

// Clase Cangrejo: un tipo de enemigo derivado de Alien
class cangrejo : public Alien
{
public:
    // Constructor: inicializa un cangrejo con vida, posición y tamaño
    cangrejo(int vida_, float x_, float y_, float ancho_, float alto_);

    // Dibuja el cangrejo en pantalla usando QPainter
    void Dibujar(QPainter &P) override;

    // Retorna el área rectangular del cangrejo (para detectar colisiones)
    QRectF get_area() const override;
};

#endif // CANGREJO_H
