#ifndef BARRERA_H
#define BARRERA_H

#include "colisionable.h"
#include "dibujable_abstracto.h"

// Clase que representa una barrera protectora (como las de Space Invaders)
// Hereda de:
// - colisionable: para detectar impactos de proyectiles
// - Dibujable_abstracto: para poder dibujarse en pantalla
class Barrera : public colisionable, public Dibujable_abstracto
{

public:
    // Constructor que inicializa la barrera con:

    // - vida_: puntos de vida de la barrera
    // - x_, y_: posición en pantalla
    // - ancho_, alto_: dimensiones de la barrera
    Barrera(int vida_, float x_, float y_, float ancho_, float alto_);

    // Método override que dibuja la barrera en pantalla usando QPainter
    void Dibujar(QPainter &P) override;

    // Método override que devuelve el área rectangular de la barrera
    // (usado para detección de colisiones)
    QRectF get_area() const override;

    // Método para reducir la vida de la barrera cuando recibe un impacto
    // Por defecto reduce 1 punto de vida
    void recibir_danio(int danio = 1);
};

#endif // BARRERA_H
