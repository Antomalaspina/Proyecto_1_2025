#ifndef NAVE_H
#define NAVE_H

#include <QPainter>          // Para dibujar la nave
#include <QPolygon>
#include <QPoint>
#include <QLine>
#include "colisionable.h"     // Para detección de colisiones
#include "dibujable_abstracto.h" // Base con posición, tamaño, vida
#include "movil.h"            // Permite movimiento con Vx y Vy
#include "proyectil.h"        // Para generar disparos

// La nave usa herencia múltiple: se dibuja, se mueve y colisiona
class Nave: public colisionable, public Dibujable_abstracto, public movil
{
public:
    // Constructor: inicializa posición y tamaño básico
    Nave(float pos_x, float pos_y);

    // Dibuja la nave
    void Dibujar(QPainter &P) override;

    // Devuelve el área rectangular para colisiones
    QRectF get_area() const override;

    // Genera un proyectil nuevo que sale desde la nave
    proyectil* Disparar();

    // Gestión de vida
    void recibir_danio(int danio = 1);
    int get_vidas_restantes() const { return vida; }
    bool esta_destruida() const { return vida <= 0; }

    // Implementación del movimiento horizontal
    virtual void movimiento() override;
};

#endif // NAVE_H

