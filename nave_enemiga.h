#ifndef NAVE_ENEMIGA_H
#define NAVE_ENEMIGA_H

#include "colisionable.h"          // Permite detección de colisiones
#include "dibujable_abstracto.h"   // Proporciona posición, tamaño y vida
#include "movil.h"                 // Agrega velocidad y movimiento
#include <QPainter>                // Necesario para dibujar en pantalla

// Herencia múltiple:
//  - colisionable → puede chocar
//  - Dibujable_abstracto → se dibuja y tiene posición/tamaño
//  - movil → puede moverse horizontalmente
class Nave_enemiga: public colisionable, public Dibujable_abstracto, public movil
{
public:
    // Constructor: inicializa posición y dirección de movimiento
    Nave_enemiga(float x_, float y_, bool direccion_derecha = true);

    // Dibuja la nave enemiga en pantalla
    void Dibujar(QPainter &P) override;

    // Devuelve el área usada para detectar colisiones
    QRectF get_area() const override;

    // Define su movimiento horizontal
    void movimiento() override;

    // Indica si salió completamente de la pantalla
    bool fuera_de_pantalla() const;

    // Puntos otorgados al destruirla
    int get_puntos() const { return 100; }

private:
    bool mover_derecha;
    // true → se mueve de izquierda a derecha
    // false → se mueve de derecha a izquierda
};

#endif // NAVE_ENEMIGA_H
