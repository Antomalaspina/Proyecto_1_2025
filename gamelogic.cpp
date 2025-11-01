#include "gamelogic.h"
#include <QPainter>

Gamelogic::Gamelogic()
{
    nave_principal=new Nave(385,580);
}

void Gamelogic::Dibujar(QPainter &painter)
{
    nave_principal->Dibujar(painter);
}

void Gamelogic::Generar_proyectiles()
{

}

void Gamelogic::Mover_enemigos()
{

}

void Gamelogic::Colision_proyectil()
{

}

void Gamelogic::vida()
{

}
