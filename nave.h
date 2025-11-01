#ifndef NAVE_H
#define NAVE_H
#include "dibujable_abstracto.h"
#include <QPainter>
#include <QPolygon>
#include <QPoint>
#include <QLine>

class Nave: public Dibujable_abstracto
{
public:
    Nave(float pos_x, float pos_y);
   void set_x(float x_nave_nueva);
   void Dibujar(QPainter &Qpainter) override ;

};

#endif // NAVE_H
