#ifndef BARRERA_H
#define BARRERA_H
#include "dibujable_abstracto.h"


class Barrera : public Dibujable_abstracto
{
private:
    float Separacion_barrera;

public:
    Barrera(float Separacion_barrera,int vida_,float x_, float y_,float ancho_, float alto_);
    void Dibujar(QPainter &Qpainter) override ;
};

#endif // BARRERA_H
