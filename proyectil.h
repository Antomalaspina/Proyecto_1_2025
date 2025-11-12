#ifndef PROYECTIL_H
#define PROYECTIL_H
#include "colisionable.h"
#include "dibujable_abstracto.h"
#include "movil.h"

//✅Hereda de movil y ya no necesita get_vel o set_y
class proyectil: public colisionable, public Dibujable_abstracto, public Movil
{
public:
    proyectil(float velocidad_y, int vida_, float x_,float _y,float ancho_,float alto_);
    void mover();
    QRectF get_area() const override;
    void Dibujar(QPainter &P) override ;
    //✅métodos de movil:
    virtual void movimiento() override;
};

#endif // PROYECTIL_H
