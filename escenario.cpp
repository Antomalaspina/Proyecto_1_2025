#include "escenario.h"

//CONSTRUCTOR DE LA CLASE ESCENARIO, QUE INICIA LOS VALORES DE LOS P1 Y P2
Escenario::Escenario(QVector2D _p1, QVector2D _p2) :
    p1(_p1), p2(_p2)
{}

//METODO PARA DIBUJAR EL ESCENARIO
void Escenario::dibujar(QPainter &Qpainter){
    // p->setRenderHint(QPainter::Antialiasing, true);
    //ESTABLECE EL COLOR DE FONDO DEL ESCENARIO
    Qpainter.setBrush(Qt::black);
    //EL COLOR DEL BORDE DEL ESCENARIO
    Qpainter.setPen(Qt::black);
    //DIBUJA UN RECTANGULO USANDO EL P1 COMO ESQUINA SUPERIOR IZQUIERDA
    //Y EL ALTO Y ANCHO COMO LAS DIFERENCIA ENTRE P1 Y P2 QUE SON COORDENADAS
    Qpainter.drawRect(p1.x(), p1.y(), p2.x()-p1.x(), p2.y()-p1.y());
}

