#ifndef NAVE_H
#define NAVE_H
#include <QPainter>
#include <QPolygon>
#include <QPoint>
#include <QLine>
#include "colisionable.h"
#include "dibujable_abstracto.h"
#include "movil.h"
#include "proyectil.h"

class Nave: public colisionable, public Dibujable_abstracto, public movil
{
public:
    Nave(float pos_x, float pos_y);

   // void set_x(float x_nave_nueva);
   void Dibujar(QPainter &P) override ;
   QRectF get_area() const override;
   //nuevo
   proyectil* Disparar();

   // Métodos para gestionar vidas
   void recibir_danio(int danio = 1);
   int get_vidas_restantes() const { return vida; }
   bool esta_destruida() const { return vida <= 0; }

   //✅métodos de movil:
   virtual void movimiento() override;
};

#endif // NAVE_H
