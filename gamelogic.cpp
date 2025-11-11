#include "gamelogic.h"          // Incluye la clase principal de lógica
#include <QPainter>             // Permite dibujar en pantalla
#include "cangrejo.h"           // Tipos de enemigos
#include "pulpo.h"
#include "calamar.h"
#include <QRandomGenerator64>   // Generador aleatorio

// Flags globales para leer teclas mantenidas
bool mover_izq=false;
bool mover_dcha=false;
bool disparar=false;

// Variables auxiliares (no muy usadas)
float vel_alienx, vel_alieny;

//---------------------------------------------------------
// CONSTRUCTOR: configura la lógica inicial del juego
//---------------------------------------------------------
Gamelogic::Gamelogic()
{
    juego_iniciado = false;     // Inicia en menú
    puntaje = 0;                // Puntaje inicial
    puntaje_maximo = 0;         // Mejor puntaje

    nave_principal = nullptr;   // No hay nave todavía
    nave_bonus = nullptr;       // Sin nave bonus
}

//---------------------------------------------------------
// Inicializa una partida desde cero
//---------------------------------------------------------
void Gamelogic::inicializar_juego()
{
    // Limpia instancias previas si existían
    if (nave_principal != nullptr) delete nave_principal;
    if (nave_bonus != nullptr) delete nave_bonus;

    lista_dibujables.clear();
    lista_moviles.clear();

    qDeleteAll(lista_barrera); lista_barrera.clear();
    qDeleteAll(lista_alien); lista_alien.clear();
    qDeleteAll(lista_proyectil_jugador); lista_proyectil_jugador.clear();
    qDeleteAll(lista_proyectil_enemigos); lista_proyectil_enemigos.clear();

    puntaje = 0;   // Reinicia el puntaje

    // Parámetros de movimiento alien
    velocidad_alien = 0.2f;
    direccion_derecha = true;
    descenso_alien = 20.0f;
    margen_izquierdo = 10;
    margen_derecho = 790;

    // Crea la nave del jugador
    nave_principal = new Nave(385, 580);
    lista_dibujables.append(nave_principal);
    lista_moviles.append(nave_principal);

    // Configura temporizador de disparo alien
    contador_disparo_alien = 0;
    intervalo_disparo_min = 60;
    intervalo_disparo_max = 180;

    // Configura nave bonus
    nave_bonus = nullptr;
    contador_nave_bonus = 0;
    intervalo_nave_bonus = 600;

    //-----------------------------------------------------
    // Generación de las 4 barreras
    //-----------------------------------------------------
    Barrera* barrita;
    for (int i = 0; i < 4; i++) {
        int x = 40 + i * 230;
        int y = 500;
        barrita = new Barrera(40, 10, x, y, 40, 25);
        lista_barrera.append(barrita);
        lista_dibujables.append(barrita);
    }

    //-----------------------------------------------------
    // Generación de los aliens por filas
    //-----------------------------------------------------
    int columnas = 11;
    int espaciadoX = 50;
    int inicioX = 50;

    // Fila superior: CALAMAR (30 pts)
    int inicioY_calamar = 90;
    for (int c = 0; c < columnas; c++) {
        calamar* calamarcito = new calamar(1, inicioX + c * espaciadoX, inicioY_calamar, 35, 10);
        lista_alien.append(calamarcito);
        lista_dibujables.append(calamarcito);
    }

    // Filas 2-3: CANGREJOS (20 pts)
    int inicioY_cangrejo = 120;
    for (int f = 0; f < 2; f++) {
        for (int c = 0; c < columnas; c++) {
            cangrejo* cangrejito = new cangrejo(1, inicioX + c * espaciadoX, inicioY_cangrejo + f * 40, 35, 10);
            lista_alien.append(cangrejito);
            lista_dibujables.append(cangrejito);
        }
    }

    // Filas 4-5: PULPOS (10 pts)
    int inicioY_pulpo = 200;
    for (int f = 0; f < 2; f++) {
        for (int c = 0; c < columnas; c++) {
            Pulpo* pulpito = new Pulpo(1, inicioX + c * espaciadoX, inicioY_pulpo + f * 40, 35, 10);
            lista_alien.append(pulpito);
            lista_dibujables.append(pulpito);
        }
    }

    // Configura movilidad de todos los aliens
    for (Alien* alf : lista_alien) {
        alf->set_Vx(0.3f);
        alf->set_Vy(0.0f);
        lista_moviles.append(alf);
    }

    juego_iniciado = true;   // Marca que estamos en partida
}

//---------------------------------------------------------
// Arrancar una nueva partida
//---------------------------------------------------------
void Gamelogic::iniciar_juego()
{
    juego_iniciado = true;
    inicializar_juego();
}

//---------------------------------------------------------
// Dibuja el menú de inicio con la tabla de puntajes
//---------------------------------------------------------
void Gamelogic::Dibujar_menu(QPainter &P)
{
    // Título grande
    P.setFont(QFont("Courier New", 48, QFont::Bold));
    P.setPen(Qt::white);
    P.drawText(QRect(0, 50, 800, 80), Qt::AlignCenter, "SPACE INVADERS");

    // Instrucción para comenzar
    P.setFont(QFont("Courier New", 24, QFont::Bold));
    P.setPen(Qt::green);
    P.drawText(QRect(0, 150, 800, 40), Qt::AlignCenter, "APRETAR BARRA ESPACIADORA PARA INICIAR");

    // Tabla de puntuaciones
    P.setFont(QFont("Courier New", 20, QFont::Bold));
    P.setPen(Qt::white);
    P.drawText(QRect(0, 250, 800, 40), Qt::AlignCenter, "*TABLA DE PUNTUACIÓN*");

    // Nave misteriosa
    P.setBrush(Qt::red);
    P.setPen(Qt::red);
    QRectF nave_mystery(250, 320, 40, 15);
    P.drawEllipse(nave_mystery);
    P.setFont(QFont("Courier New", 18));
    P.setPen(Qt::white);
    P.drawText(310, 335, "= ? MYSTERIO");

    // Calamar = 30 pts
    calamar* calamar_menu = new calamar(1, 270, 375, 25, 8);
    calamar_menu->Dibujar(P);
    delete calamar_menu;
    P.drawText(310, 385, "= 30 PUNTOS");

    // Cangrejo = 20 pts
    cangrejo* cangrejo_menu = new cangrejo(1, 270, 425, 25, 8);
    cangrejo_menu->Dibujar(P);
    delete cangrejo_menu;
    P.drawText(310, 430, "= 20 PUNTOS");

    // Pulpo = 10 pts
    Pulpo* pulpo_menu = new Pulpo(1, 270, 470, 25, 8);
    pulpo_menu->Dibujar(P);
    delete pulpo_menu;
    P.drawText(310, 475, "= 10 PUNTOS");

    // Puntaje máximo
    if (puntaje_maximo > 0) {
        P.setFont(QFont("Courier New", 16));
        P.setPen(Qt::yellow);
        P.drawText(QRect(0, 520, 800, 30), Qt::AlignCenter,
                   QString("PUNTAJE MÁXIMO: %1").arg(puntaje_maximo));
    }
}

//---------------------------------------------------------
// Genera la nave bonus cada cierto tiempo
//---------------------------------------------------------
void Gamelogic::Generar_nave_bonus()
{
    if (nave_bonus != nullptr) return;  // Solo una activa

    contador_nave_bonus++;

    if (contador_nave_bonus >= intervalo_nave_bonus) {
        contador_nave_bonus = 0;

        // Decide si viene desde izq o der
        bool desde_izquierda = QRandomGenerator::global()->bounded(2) == 0;
        float x_inicial = desde_izquierda ? -50 : 850;
        float y_inicial = 40;

        // Crea nave enemiga
        nave_bonus = new Nave_enemiga(x_inicial, y_inicial, desde_izquierda);
        lista_dibujables.append(nave_bonus);
        lista_moviles.append(nave_bonus);
        nave_bonus->set_Vx(3.0f);   // Velocidad fija
    }
}

//---------------------------------------------------------
// Dibuja el juego (modo normal, pausa, menú, etc.)
//---------------------------------------------------------
void Gamelogic::Dibujar(QPainter &P)
{
    if (!juego_iniciado) {
        Dibujar_menu(P);
        return;
    }

    // Dibuja todos los objetos
    for (Dibujable_abstracto* dibu : lista_dibujables) {
        if (dibu != nullptr) dibu->Dibujar(P);
    }

    // Puntaje
    P.setPen(Qt::white);
    P.setFont(QFont("Courier New", 16, QFont::Bold));
    P.drawText(10, 20, QString("PUNTAJE: %1").arg(puntaje));
    P.drawText(600, 20, QString("MÁXIMO: %1").arg(puntaje_maximo));

    // Vidas de la nave
    if (nave_principal != nullptr) {
        P.drawText(10, 45, QString("VIDAS: %1").arg(nave_principal->get_vidas_restantes()));
    }

    // GAME OVER
    if (nave_principal != nullptr && nave_principal->esta_destruida()) {
        P.setFont(QFont("Courier New", 48, QFont::Bold));
        P.setPen(Qt::red);
        P.drawText(200, 300, "JUEGO TERMINADO");

        P.setFont(QFont("Courier New", 20));
        P.setPen(Qt::white);
        P.drawText(QRect(0, 350, 800, 30), Qt::AlignCenter, "Presionar SPACE para retornar al menú");
    }

    // YOU WIN
    if (lista_alien.isEmpty()) {
        P.setFont(QFont("Courier New", 48, QFont::Bold));
        P.setPen(Qt::green);
        P.drawText(250, 300, "GANASTE!");

        P.setFont(QFont("Courier New", 20));
        P.setPen(Qt::white);
        P.drawText(QRect(0, 350, 800, 30), Qt::AlignCenter, "Presionar SPACE para retornar al menú");
    }

    //-----------------------------------------------------
    // Mensaje de PAUSA
    //-----------------------------------------------------
    if (pausa) {
        P.setFont(QFont("Courier New", 48, QFont::Bold));
        P.setPen(Qt::yellow);
        P.drawText(QRect(0, 250, 800, 80), Qt::AlignCenter, "PAUSADO");

        P.setFont(QFont("Courier New", 20));
        P.setPen(Qt::white);
        P.drawText(QRect(0, 340, 800, 30), Qt::AlignCenter, "Presionar ESC para reanudar");
    }
}

//---------------------------------------------------------
// Disparo aleatorio de aliens
//---------------------------------------------------------
void Gamelogic::Disparar_aliens()
{
    if (lista_alien.isEmpty()) return;

    contador_disparo_alien++;

    // Intervalo aleatorio entre min y max
    int intervalo_aleatorio =
        QRandomGenerator::global()->bounded(intervalo_disparo_min, intervalo_disparo_max);

    if (contador_disparo_alien >= intervalo_aleatorio) {
        contador_disparo_alien = 0;

        // Escoge un alien al azar
        int indice_aleatorio = QRandomGenerator::global()->bounded(lista_alien.size());
        Alien* alien_disparador = lista_alien[indice_aleatorio];

        proyectil* nuevo_proy = alien_disparador->Disparar();
        if (nuevo_proy != nullptr) {
            lista_proyectil_enemigos.append(nuevo_proy);
            lista_dibujables.append(nuevo_proy);
            lista_moviles.append(nuevo_proy);
        }
    }
}

//---------------------------------------------------------
// Detecta si algún alien tocó el borde pantalla
//---------------------------------------------------------
bool Gamelogic::Aliens_tocaron_borde()
{
    for (Alien* alien : lista_alien) {
        QRectF area = alien->get_area();

        alien->set_Vy(descenso_alien);   // Fuerza la bajada

        if (direccion_derecha) {
            if (area.right() >= margen_derecho) {
                descenso_alien = 20.0f;
                return true;
            }
        } else {
            if (area.left() <= margen_izquierdo) {
                descenso_alien = 20.0f;
                return true;
            }
        }
    }
    descenso_alien = 0.0f;
    return false;
}

//---------------------------------------------------------
// Movimiento horizontal y vertical de los aliens
//---------------------------------------------------------
void Gamelogic::Mover_enemigos()
{
    if (lista_alien.isEmpty()) return;

    // Si toca borde → cambiar dirección y aumentar velocidad
    if (Aliens_tocaron_borde()) {
        direccion_derecha = !direccion_derecha;
        velocidad_alien = 0.3f + (55 - lista_alien.size()) * 0.03f;
    }

    // Movimiento horizontal
    float desplazamiento = direccion_derecha ? velocidad_alien : -velocidad_alien;

    for (Alien* alien : lista_alien) {
        alien->set_Vx(desplazamiento);
    }
}

//---------------------------------------------------------
// Manejo de teclas presionadas
//---------------------------------------------------------
void Gamelogic::Pressbutton(QKeyEvent *ev)
{
    // Menú → inicia con espacio
    if (!juego_iniciado) {
        if (ev->key() == Qt::Key_Space) inicializar_juego();
        return;
    }

    // Fin de partida → espacio vuelve al menú
    if (juego_terminado()) {
        if (ev->key() == Qt::Key_Space) {
            juego_iniciado = false;
            if (puntaje > puntaje_maximo) puntaje_maximo = puntaje;
        }
        return;
    }

    // Movimiento
    if (ev->key() == Qt::Key_Left) mover_izq = true;
    if (ev->key() == Qt::Key_Right) mover_dcha = true;

    // Disparo
    if (ev->key() == Qt::Key_Space) disparar = true;

    // Pausa con ESC
    if (ev->key() == Qt::Key_Escape) pausa = !pausa;
}

//---------------------------------------------------------
// Tecla liberada
//---------------------------------------------------------
void Gamelogic::Releasebutton(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Left) mover_izq=false;
    if (ev->key() == Qt::Key_Right) mover_dcha=false;
    if (ev->key() == Qt::Key_Space) disparar=false;
}

//---------------------------------------------------------
// Actualiza todo el estado del juego una vez por frame
//---------------------------------------------------------
void Gamelogic::actualizar()
{
    // Si está en pausa o terminado → no actualizar
    if (!juego_iniciado || juego_terminado() || nave_principal == nullptr || pausa) return;

    // Si los aliens llegaron a las barreras → pierde
    if (Aliens_alcanzaron_barreras()) {
        nave_principal->recibir_danio(nave_principal->get_vidas_restantes());
        return;
    }

    //-----------------------------------------------------
    // Movimiento de la nave del jugador
    //-----------------------------------------------------
    if (mover_izq && (nave_principal->get_x() - 15 > 0))
        nave_principal->set_Vx(-10);
    else if (mover_dcha && (nave_principal->get_x() + 15 < 800))
        nave_principal->set_Vx(10);
    else
        nave_principal->set_Vx(0);

    //-----------------------------------------------------
    // Movimiento general: aliens, proyectiles, nave bonus
    //-----------------------------------------------------
    Mover_enemigos();

    // Mueve todos los elementos móviles
    for (movil* movi : lista_moviles) movi->movimiento();

    //-----------------------------------------------------
    // Disparo del jugador
    //-----------------------------------------------------
    if (disparar && lista_proyectil_jugador.empty()) {
        proyectil* nuevo = nave_principal->Disparar();
        if (nuevo != nullptr) {
            lista_proyectil_jugador.append(nuevo);
            lista_dibujables.append(nuevo);
            lista_moviles.append(nuevo);
        }
    }

    //-----------------------------------------------------
    // Eliminar proyectiles del jugador fuera o colisionados
    //-----------------------------------------------------
    for (int i = 0; i < lista_proyectil_jugador.size(); i++) {
        proyectil* p = lista_proyectil_jugador[i];

        if (p->get_y() < 0 || p->get_colision()) {
            lista_proyectil_jugador.removeAt(i);
            lista_dibujables.removeOne(p);
            lista_moviles.removeOne(p);
            delete p;
            i--;
        }
    }

    //-----------------------------------------------------
    // Eliminar proyectiles enemigos fuera o colisionados
    //-----------------------------------------------------
    for (int i = 0; i < lista_proyectil_enemigos.size(); i++) {
        proyectil* p = lista_proyectil_enemigos[i];

        if (p->get_y() > 600 || p->get_colision()) {
            lista_proyectil_enemigos.removeAt(i);
            lista_dibujables.removeOne(p);
            lista_moviles.removeOne(p);
            delete p;
            i--;
        }
    }

    //-----------------------------------------------------
    // Movimiento y eliminación de nave bonus
    //-----------------------------------------------------
    if (nave_bonus != nullptr) {
        nave_bonus->movimiento();

        if (nave_bonus->fuera_de_pantalla() || nave_bonus->get_colision()) {
            lista_dibujables.removeOne(nave_bonus);
            lista_moviles.removeOne(nave_bonus);
            delete nave_bonus;
            nave_bonus = nullptr;
        }
    }

    // Generar nave bonus si corresponde
    Generar_nave_bonus();

    //-----------------------------------------------------
    // Nuevamente movimiento alien y disparo
    //-----------------------------------------------------
    Mover_enemigos();
    Disparar_aliens();

    //-----------------------------------------------------
    // Eliminar aliens destruidos y asignar puntos
    //-----------------------------------------------------
    for (Alien* alf : lista_alien) {
        if (alf->get_colision()) {

            // Determinar tipo de alien mediante dynamic_cast
            if (dynamic_cast<calamar*>(alf)) puntaje += 30;
            else if (dynamic_cast<cangrejo*>(alf)) puntaje += 20;
            else if (dynamic_cast<Pulpo*>(alf)) puntaje += 10;

            lista_alien.removeOne(alf);
            lista_dibujables.removeOne(alf);
            lista_moviles.removeOne(alf);
            delete alf;
        }
    }

    //-----------------------------------------------------
    // Eliminar barreras destruidas
    //-----------------------------------------------------
    for (Barrera* barrita : lista_barrera) {
        if (barrita->get_colision()) {
            lista_barrera.removeOne(barrita);
            lista_dibujables.removeOne(barrita);
            delete barrita;
        }
    }
}

//---------------------------------------------------------
// Verificación de TODAS las colisiones del juego
//---------------------------------------------------------
void Gamelogic::Verificar_colisiones()
{
    if (!juego_iniciado || nave_principal == nullptr) return;

    // Jugador → aliens
    for (proyectil* proy : lista_proyectil_jugador)
        for (Alien* alf : lista_alien)
            if (proy->CheckCollision(alf)) {
                alf->set_colision(true);
                proy->set_colision(true);
            }

    // Jugador → barreras
    for (proyectil* proy : lista_proyectil_jugador)
        for (Barrera* barr : lista_barrera)
            if (proy->CheckCollision(barr)) {
                barr->recibir_danio(1);
                proy->set_colision(true);
            }

    // Enemigos → nave
    for (proyectil* proy : lista_proyectil_enemigos)
        if (proy->CheckCollision(nave_principal)) {
            nave_principal->recibir_danio(1);
            proy->set_colision(true);
        }

    // Proyectil jugador ↔ proyectil enemigo
    for (proyectil* proy_j : lista_proyectil_jugador)
        for (proyectil* proy_a : lista_proyectil_enemigos)
            if (proy_j->CheckCollision(proy_a)) {
                proy_a->set_colision(true);
                proy_j->set_colision(true);
            }

    // Proyectil enemigo → barreras
    for (proyectil* proy : lista_proyectil_enemigos)
        for (Barrera* barr : lista_barrera)
            if (proy->CheckCollision(barr)) {
                barr->recibir_danio(1);
                proy->set_colision(true);
            }

    // Jugador → nave bonus
    if (nave_bonus != nullptr) {
        for (proyectil* proy : lista_proyectil_jugador)
            if (proy->CheckCollision(nave_bonus)) {
                nave_bonus->set_colision(true);
                proy->set_colision(true);
                puntaje += 50;   // Bonus
            }
    }
}

//---------------------------------------------------------
// Detecta si algún alien llegó a la altura de las barreras
//---------------------------------------------------------
bool Gamelogic::Aliens_alcanzaron_barreras()
{
    if (lista_alien.isEmpty()) return false;

    float limite_barrera = 500.0f; // Y donde están las barreras

    if (!lista_barrera.isEmpty())
        limite_barrera = lista_barrera[0]->get_y();

    // Si algún alien bajó demasiado → jugador pierde
    for (Alien* alien : lista_alien)
        if (alien->get_y() >= limite_barrera)
            return true;

    return false;
}
