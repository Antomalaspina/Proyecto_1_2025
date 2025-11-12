#include "nave.h"


Nave::Nave( float pos_x, float pos_y ) {
    x=pos_x;
    y= pos_y;
    ancho=30.0f;
    alto=20.0f;
    vida=3;
}

void Nave::movimiento(){
    x+=Vx;
}


 void Nave::Dibujar(QPainter &P){
     // Solo dibujar si tiene vida
     if (vida <= 0) return;
     P.setPen(Qt::green);
     P.setBrush(Qt::green);

     // Base (parte inferior ancha)
     QRect base(QPoint(x - 15, y - 8), QPoint(x + 15, y));
     P.drawRect(base);

     // Torreta (parte superior angosta)
     QRect torreta(QPoint(x - 8, y - 14), QPoint(x + 8, y - 8));
     P.drawRect(torreta);

     // Cañón (rectángulo central alargado)
     QRect canon(QPoint(x - 2, y - 22), QPoint(x + 2, y - 14));
     P.drawRect(canon);

 }
 QRectF Nave::get_area() const
 {
     return QRectF(x - 15, y - 22, 30, 22);
 }

 proyectil* Nave::Disparar() {
     float x_proyectil = x;
     float y_proyectil = y - alto/2;
     float ancho_proyectil = 3;
     float alto_proyectil = 10;
     float velocidad = -12; // Negativa para que suba
     return new proyectil(velocidad, 1, x_proyectil, y_proyectil, ancho_proyectil, alto_proyectil);
 }
 void Nave::recibir_danio(int danio)
 {
     vida -= danio;
     if (vida < 0) {
         vida = 0;
     }
 }
