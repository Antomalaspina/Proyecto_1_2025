#ifndef BARRERA_H
#define BARRERA_H


#include "colisionable.h"
#include "dibujable_abstracto.h"

class Barrera : public colisionable, public Dibujable_abstracto
{
private:
    float Separacion_barrera;

public:
    Barrera(float Separacion_barrera,int vida_,float x_, float y_,float ancho_, float alto_);
    void Dibujar(QPainter &P) override ;
    QRectF get_area() const override;
    // Método para reducir vida cuando recibe impacto
    void recibir_danio(int danio = 1);
};

#endif // BARRERA_H
