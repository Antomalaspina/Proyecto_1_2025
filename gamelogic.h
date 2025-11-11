#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QPainter>
#include "alien.h"
#include "nave.h"
#include "barrera.h"
#include "nave_enemiga.h"
#include "proyectil.h"
#include <qevent.h>
#include <QRandomGenerator>


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
    QList<Alien*> lista_alien;
    QList<proyectil*> lista_proyectil_jugador;
    QList<proyectil*> lista_proyectil_enemigos;
    QList<Dibujable_abstracto*> lista_dibujables;
    //agrego la lista de moviles
    QList<movil*> lista_moviles;
     Nave_enemiga* nave_bonus;

//variables de movimiento de aliens
    float velocidad_alien;
    bool direccion_derecha;  // true = derecha, false = izquierda
    float descenso_alien;
    int margen_izquierdo;
    int margen_derecho;

    // Variables para disparo de aliens
    int contador_disparo_alien;
    int intervalo_disparo_min;
    int intervalo_disparo_max;




    // Variables para nave bonus
    int contador_nave_bonus;
    int intervalo_nave_bonus;

    // Estado del juego
    bool juego_iniciado;
    int puntaje;
    int puntaje_maximo;
    //✅Nuevo estado de juego:
    bool pausa=false;




public:
    Gamelogic();
    void Dibujar(QPainter &P);
    void Generar_proyectiles();
    void Mover_enemigos();
    void Colision_proyectil();
    void Verificar_colisiones();
    void Pressbutton(QKeyEvent *ev);
    void Releasebutton(QKeyEvent *ev);
    void actualizar();
    // Métodos para obtener estado del juego
    int get_vidas_nave() const { return nave_principal->get_vidas_restantes(); }
    bool juego_terminado() const { return nave_principal->esta_destruida() || lista_alien.isEmpty(); }
    bool esta_en_menu() const { return !juego_iniciado; }
    int get_puntaje() const { return puntaje; }
    void inicializar_juego();
    void Dibujar_menu(QPainter &P);
    void iniciar_juego();
    void Disparar_aliens();
    void Generar_nave_bonus();
    bool Aliens_tocaron_borde();
    bool Aliens_alcanzaron_barreras();

};

#endif // GAMELOGIC_H
