#ifndef GAMELOGIC_H
#define GAMELOGIC_H

#include <QPainter>              // Para dibujar
#include "alien.h"               // Clase base de aliens
#include "nave.h"                // Nave del jugador
#include "barrera.h"             // Barreras defensivas
#include "nave_enemiga.h"        // Nave bonus
#include "proyectil.h"           // Proyectiles
#include <qevent.h>              // Manejo de teclado
#include <QRandomGenerator>      // Aleatorios

// Forward declarations para evitar includes pesados
class Calamar;
class Cangrejo;
class Pulpo;
class Proyectil;
class Barrera;

// Clase principal que maneja toda la lógica del juego
class Gamelogic
{
private:
    Nave* nave_principal;                    // Nave del jugador
    QList<Barrera*> lista_barrera;           // Todas las barreras
    QList<Alien*> lista_alien;               // Todos los aliens
    QList<proyectil*> lista_proyectil_jugador;   // Proyectiles del jugador
    QList<proyectil*> lista_proyectil_enemigos;  // Proyectiles enemigos
    QList<Dibujable_abstracto*> lista_dibujables; // Objetos que se dibujan
    QList<movil*> lista_moviles;             // Objetos que se mueven
    Nave_enemiga* nave_bonus;                // Nave misteriosa

    // Variables de movimiento de los aliens
    float velocidad_alien;                   // Velocidad horizontal
    bool direccion_derecha;                  // Dirección actual
    float descenso_alien;                    // Qué tanto bajan
    int margen_izquierdo;                    // Límite izquierdo
    int margen_derecho;                      // Límite derecho

    // Disparos de aliens
    int contador_disparo_alien;
    int intervalo_disparo_min;
    int intervalo_disparo_max;

    // Nave bonus
    int contador_nave_bonus;
    int intervalo_nave_bonus;

    // Estado del juego
    bool juego_iniciado;                     // Si hay partida
    int puntaje;                             // Puntaje actual
    int puntaje_maximo;                      // Puntaje máximo
    bool pausa = false;                      // Estado de pausa

public:
    Gamelogic();                             // Constructor
    void Dibujar(QPainter &P);               // Dibuja todo en pantalla
    void Generar_proyectiles();              // Genera proyectiles
    void Mover_enemigos();                   // Movimiento de aliens
    void Colision_proyectil();               // Manejo de colisiones
    void Verificar_colisiones();             // Detecta todas las colisiones
    void Pressbutton(QKeyEvent *ev);         // Tecla presionada
    void Releasebutton(QKeyEvent *ev);       // Tecla liberada
    void actualizar();                       // Actualiza lógica general

    // Getters de estado del juego
    int get_vidas_nave() const { return nave_principal->get_vidas_restantes(); }
    bool juego_terminado() const { return nave_principal->esta_destruida() || lista_alien.isEmpty(); }
    bool esta_en_menu() const { return !juego_iniciado; }
    int get_puntaje() const { return puntaje; }

    void inicializar_juego();                // Configura nueva partida
    void Dibujar_menu(QPainter &P);          // Dibuja menú inicial
    void iniciar_juego();                    // Inicia partida
    void Disparar_aliens();                  // Aliens disparan
    void Generar_nave_bonus();               // Crea nave bonus
    bool Aliens_tocaron_borde();             // Detecta bordes
    bool Aliens_alcanzaron_barreras();       // Detecta final del juego
};

#endif // GAMELOGIC_H
