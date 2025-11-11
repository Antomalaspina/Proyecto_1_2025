#ifndef NAVE_ENEMIGA_H
#define NAVE_ENEMIGA_H

#include "colisionable.h"
#include "dibujable_abstracto.h"
#include "movil.h"
#include <QPainter>


class Nave_enemiga: public colisionable, public Dibujable_abstracto, public movil
{
public:
    Nave_enemiga(float x_, float y_, bool direccion_derecha = true);
    void Dibujar(QPainter &P) override;
    QRectF get_area() const override;
    void movimiento() override;
    bool fuera_de_pantalla() const;
    int get_puntos() const { return 100; }  // Puntos que da al destruirla
private:

    bool mover_derecha;  // true = izquierda a derecha, false = derecha a izquierda
};

#endif // NAVE_ENEMIGA_H
