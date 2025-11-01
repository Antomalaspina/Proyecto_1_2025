#include "gamelogic.h"
#include <QPainter>


Gamelogic::Gamelogic()
{
    nave_principal=new Nave(385,580);
    for (int i = 0; i < 4; i++) {
        int x = 40 + i * 230;
        int y = 450;
       Barrera* barrita= new Barrera(40, 3, x, y, 40, 25);
        lista_barrera.append(barrita);
    }

    // --- Crear los 22 pulpos (2 filas de 11) ---
    int filas = 2;
    int columnas = 11;
    int inicioX = 50;     // posición inicial horizontal
    int inicioY = 200;    // posición de la primera fila
    int espaciadoX = 50;  // separación entre pulpos
    int espaciadoY = 40;  // separación vertical entre filas

    for (int f = 0; f < filas; f++) {
        for (int c = 0; c < columnas; c++) {
            int x = inicioX + c * espaciadoX;
            int y = inicioY + f * espaciadoY;
            Pulpo* pulpito = new Pulpo(1, x, y, 100, 10,4);  // ancho 20, alto 10
            lista_Pulpo.append(pulpito);
        }
    }
}



void Gamelogic::Dibujar(QPainter &painter)
{
    nave_principal->Dibujar(painter);
    for (Barrera* b : lista_barrera)
        b->Dibujar(painter);
    // --- Dibujar los pulpos ---
    for (Pulpo* pul : lista_Pulpo)
        pul->Dibujar(painter);
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
