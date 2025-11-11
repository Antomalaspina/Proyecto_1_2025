#ifndef PROYECTIL_H
#define PROYECTIL_H
#include "colisionable.h"
#include "dibujable_abstracto.h"
#include "movil.h"


class proyectil: public colisionable, public Dibujable_abstracto, public movil
{

public:
    proyectil(float velocidad_y, int vida_, float x_,float _y,float ancho_,float alto_);
    QRectF get_area() const override;
    void Dibujar(QPainter &P) override ;
    //✅métodos de movil:
    virtual void movimiento() override;
};

#endif // PROYECTIL_H
