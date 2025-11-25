#ifndef ESCENARIO_H
#define ESCENARIO_H
#include <QVector2D>
#include <qwindowdefs.h>
#include "dibujable_abstracto.h"

class Escenario: public Dibujable_abstracto
{
public:
    Escenario(QVector2D _p1, QVector2D _p2);
    void dibujar(QPainter &Qpainter) ;
    QVector2D getP1() {return p1;}
    QVector2D getP2() {return p2;}

protected:
    QVector2D p1, p2;
};

#endif // ESCENARIO_H
