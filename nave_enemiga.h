#ifndef NAVE_ENEMIGA_H
#define NAVE_ENEMIGA_H

#include "colisionable.h"
#include "dibujable_abstracto.h"
#include <QPainter>
#include "movil.h"
//✅Agrego herencia de movil y ya no hacen falta velocidad o mover() o algun set posicion
//✅Recordar borrar el atributo del constructor en el cpp
class Nave_enemiga: public colisionable, public Dibujable_abstracto, public Movil
{
public:
    Nave_enemiga(float x_, float y_, bool direccion_derecha = true);
    void Dibujar(QPainter &P) override;
    QRectF get_area() const override;
    void mover();
    bool fuera_de_pantalla() const;
    int get_puntos() const { return 100; }  // Puntos que da al destruirla
    //✅métodos de movil:
    virtual void movimiento() override;
private:
    // float velocidad;
    bool mover_derecha;  // true = izquierda a derecha, false = derecha a izquierda
};

#endif // NAVE_ENEMIGA_H
