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
     P.setPen(Qt::green);
     P.setBrush(Qt::blue);

     // RECONSTRUIR el polígono con la posición ACTUAL cada vez que se dibuja
     float mitad_ancho = ancho / 2.0f;
     float mitad_alto = alto / 2.0f;

     QPolygon polygon;
     polygon << QPoint(x - mitad_ancho, y - mitad_alto)  // Superior izquierda
             << QPoint(x + mitad_ancho, y - mitad_alto)  // Superior derecha
             << QPoint(x + mitad_ancho, y + mitad_alto)  // Inferior derecha
             << QPoint(x - mitad_ancho, y + mitad_alto); // Inferior izquierda

     P.drawPolygon(polygon);
 }
