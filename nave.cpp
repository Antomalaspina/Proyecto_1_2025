#include "nave.h"


Nave::Nave( float pos_x, float pos_y ) {
    x=pos_x;
    y= pos_y;
    ancho=30;
    alto=20;
}
 void Nave::set_x(float x_nave_nueva){
     x=x_nave_nueva;
}
 void Nave::Dibujar(QPainter &P){
     QPolygon N;
     N<< QPoint(400- ancho/2,600-alto)<<QPoint(400+ ancho/2,600-alto)
       <<QPoint(400+ancho/2,600-2*alto)<<QPoint(400-ancho/2,600-2*alto)
       <<QPoint(400-ancho/2,600-alto);
     P.setPen(Qt::white);
     P.setBrush(Qt::green);
     P.drawPolygon(N);
 }
