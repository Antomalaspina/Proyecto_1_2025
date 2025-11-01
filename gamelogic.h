#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QPainter>
#include "nave.h"
#include "barrera.h"
#include "calamar.h"
#include "cangrejo.h"
#include "pulpo.h"
#include "proyectil.h"
class Calamar;
class Cangrejo;
class Pulpo;
class Proyectil;
class Barrera;

class Gamelogic
{
private:
    Nave* nave_principal;
    QList<Barrera*> lista_barrera;
    QList<calamar*> lista_calamar;
    QList<cangrejo*> lista_cangrejo;
    QList<pulpo*> lista_pulpo;
    QList<proyectil*> lista_proyectil;
public:
    Gamelogic();
    void Dibujar(QPainter &painter);
    void Generar_proyectiles();
    void Mover_enemigos();
    void Colision_proyectil();
    void vida();
};

#endif // GAMELOGIC_H
