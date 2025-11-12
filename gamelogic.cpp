#include "gamelogic.h"
#include <QPainter>
#include "cangrejo.h"
#include "pulpo.h"
#include "calamar.h"
#include <QRandomGenerator64>

//Variables
bool mover_izq=false; bool mover_dcha=false; bool disparar=false;
float vel_alienx, vel_alieny;
Gamelogic::Gamelogic()
{
    // Inicializar estado del juego
    juego_iniciado = false;
    puntaje = 0;
    puntaje_maximo = 0;

    nave_principal = nullptr;
    nave_bonus = nullptr;
}

void Gamelogic::inicializar_juego()
{
    // Limpiar todo lo anterior si existe
    if (nave_principal != nullptr) delete nave_principal;
    if (nave_bonus != nullptr) delete nave_bonus;

    lista_dibujables.clear();
    //✅pa'limpiar
    lista_moviles.clear();

    qDeleteAll(lista_barrera);
    lista_barrera.clear();

    qDeleteAll(lista_alien);
    lista_alien.clear();

    qDeleteAll(lista_proyectil_jugador);
    lista_proyectil_jugador.clear();

    qDeleteAll(lista_proyectil_enemigos);
    lista_proyectil_enemigos.clear();

    // Reiniciar puntaje
    puntaje = 0;
    // Inicializar variables de movimiento
    velocidad_alien = 0.2f;          // Velocidad horizontal
    direccion_derecha = true;        // Empiezan moviéndose a la derecha
    descenso_alien = 20.0f;          // Cuánto bajan cuando tocan el borde
    margen_izquierdo = 10;           // Margen izquierdo de la pantalla
    margen_derecho = 790;            // Margen derecho (800 - 10)


    nave_principal = new Nave(385, 580);
    lista_dibujables.append(nave_principal);
    lista_moviles.append(nave_principal);

    // Inicializar variables de disparo alien
    contador_disparo_alien = 0;
    intervalo_disparo_min = 60;   // Mínimo 60 frames (~1 segundo a 60fps)
    intervalo_disparo_max = 180;  // Máximo 180 frames (~3 segundos)
    // Inicializar variables de nave bonus
    nave_bonus = nullptr;
    contador_nave_bonus = 0;
    intervalo_nave_bonus = 600;


//creo barreras
    Barrera* barrita;
    for (int i = 0; i < 4; i++) {
        int x = 40 + i * 230;
        int y = 500;
        barrita= new Barrera(40, 10, x, y, 40, 25);
        lista_barrera.append(barrita);
        lista_dibujables.append(barrita);
    }


    // === Parámetros comunes de filas ===
    int columnas = 11;
    int espaciadoX = 50;
    int inicioX = 50;

    // === Calamar (fila 1) ===
    int inicioY_calamar = 90;
    calamar* calamarcito;
    for (int c = 0; c < columnas; c++) {
        int x = inicioX + c * espaciadoX;
        int y = inicioY_calamar;
        calamarcito= new calamar(1, x, y, 35, 10, 4);
        lista_alien.append(calamarcito);
        lista_dibujables.append(calamarcito);
    }

    // === Cangrejo (filas 2 y 3) ===
    int inicioY_cangrejo = 120;
    int espaciadoY_cangrejo = 40;
    cangrejo* cangrejito;
    for (int f = 0; f < 2; f++) {
        for (int c = 0; c < columnas; c++) {
            int x = inicioX + c * espaciadoX;
            int y = inicioY_cangrejo + f * espaciadoY_cangrejo;
            cangrejito=new cangrejo(1, x, y, 35, 10, 4);
            lista_alien.append(cangrejito);
            lista_dibujables.append(cangrejito);
        }
    }

    // === Pulpo (filas 4 y 5) ===
    int inicioY_pulpo = 200;
    int espaciadoY_pulpo = 40;
    Pulpo* pito;
    for (int f = 0; f < 2; f++) {
        for (int c = 0; c < columnas; c++) {
            int x = inicioX + c * espaciadoX;
            int y = inicioY_pulpo + f * espaciadoY_pulpo;
            pito=new Pulpo(1, x, y, 35, 10, 4);
            lista_alien.append(pito);
            lista_dibujables.append(pito);
        }
    }
    //✅Fijo la velocidad de los aliens y de paso los agrego a la lista
    for(Alien* alf:lista_alien){
        alf->set_Vx(0.3f);//porque así estaba
        alf->set_Vy(0.0f);//pa'que no se mueva verticalmente
        lista_moviles.append(alf);
    }
juego_iniciado = true;
    //✅Acá también hacer pruebas, por ahora anda bien
// pausa=false;
}

void Gamelogic::iniciar_juego()
{
    juego_iniciado = true;
    //✅Hacer pruebas después para ver si bueguea
    //pausa=false;
    inicializar_juego();
}
void Gamelogic::Dibujar_menu(QPainter &P)
{


    // Título principal
    P.setFont(QFont("Courier New", 48, QFont::Bold));
    P.setPen(Qt::white);
    P.drawText(QRect(0, 50, 800, 80), Qt::AlignCenter, "SPACE INVADERS");

    // Instrucción para jugar
    P.setFont(QFont("Courier New", 24, QFont::Bold));
    P.setPen(Qt::green);
    P.drawText(QRect(0, 150, 800, 40), Qt::AlignCenter, "APRETAR BARRA ESPACIADORA PARA INICIAR");

    // Tabla de puntajes
    P.setFont(QFont("Courier New", 20, QFont::Bold));
    P.setPen(Qt::white);
    P.drawText(QRect(0, 250, 800, 40), Qt::AlignCenter, "*SCORE ADVANCE TABLE*");

    // Nave misteriosa (roja)
    P.setBrush(Qt::red);
    P.setPen(Qt::red);
    QRectF nave_mystery(250, 320, 40, 15);
    P.drawEllipse(nave_mystery);
    P.setFont(QFont("Courier New", 18));
    P.setPen(Qt::white);
    P.drawText(310, 335, "= ? MYSTERY");

    // Calamar (30 puntos)
    calamar* calamar_menu = new calamar(1, 270, 375, 25, 8, 0);
    calamar_menu->Dibujar(P);
    delete calamar_menu;
    P.setFont(QFont("Courier New", 18));
    P.setPen(Qt::white);
    P.drawText(310, 385, "= 30 POINTS");


    // Cangrejo (20 puntos)
    cangrejo* cangrejo_menu = new cangrejo(1, 270, 425, 25, 8, 0);
    cangrejo_menu->Dibujar(P);
    delete cangrejo_menu;
    P.drawText(310, 430, "= 20 POINTS");

    // Pulpo (10 puntos)
    Pulpo* pulpo_menu = new Pulpo(1, 270, 470, 25, 8, 0);
    pulpo_menu->Dibujar(P);
    delete pulpo_menu;
    P.drawText(310, 475, "= 10 POINTS");


    // Mostrar puntaje máximo si existe
    if (puntaje_maximo > 0) {
        P.setFont(QFont("Courier New", 16));
        P.setPen(Qt::yellow);
        P.drawText(QRect(0, 520, 800, 30), Qt::AlignCenter,
                   QString("HIGH SCORE: %1").arg(puntaje_maximo));
    }
}
void Gamelogic::Generar_nave_bonus()
{
    if (nave_bonus != nullptr) return;

    contador_nave_bonus++;

    if (contador_nave_bonus >= intervalo_nave_bonus) {
        contador_nave_bonus = 0;

        bool desde_izquierda = QRandomGenerator::global()->bounded(2) == 0;
        float x_inicial = desde_izquierda ? -50 : 850;
        float y_inicial = 40;



        nave_bonus = new Nave_enemiga(x_inicial, y_inicial, desde_izquierda);
        lista_dibujables.append(nave_bonus);
        //✅agregar a moviles y setear su velocidad
        lista_moviles.append(nave_bonus);
        nave_bonus->set_Vx(3.0f);//✅Así estaba antes desde su constructor
    }
}

void Gamelogic::Dibujar(QPainter &P)
{
    {
        // Si estamos en el menú, dibujar el menú
        if (!juego_iniciado) {
            Dibujar_menu(P);
            return;
        }


        for (Dibujable_abstracto* dibu : lista_dibujables) {
            if (dibu != nullptr) {
                dibu->Dibujar(P);
            }
        }

        // Mostrar puntaje
        P.setPen(Qt::white);
        P.setFont(QFont("Courier New", 16, QFont::Bold));
        P.drawText(10, 20, QString("SCORE: %1").arg(puntaje));

        // Mostrar puntaje máximo
        P.drawText(600, 20, QString("HIGH: %1").arg(puntaje_maximo));

        // Mostrar vidas restantes
        if (nave_principal != nullptr) {
            P.drawText(10, 45, QString("LIVES: %1").arg(nave_principal->get_vidas_restantes()));
        }

        // Mostrar mensaje de Game Over si la nave fue destruida
        if (nave_principal != nullptr && nave_principal->esta_destruida()) {
            P.setFont(QFont("Courier New", 48, QFont::Bold));
            P.setBrush(Qt::white);
            P.setPen(Qt::red);
            P.drawText(200, 300, "GAME OVER");

            P.setFont(QFont("Courier New", 20));
            P.setPen(Qt::white);
            P.drawText(QRect(0, 350, 800, 30), Qt::AlignCenter, "Press SPACE to return to menu");
        }

        // Mostrar mensaje de victoria si eliminó todos los aliens
        if (lista_alien.isEmpty()) {
            P.setFont(QFont("Courier New", 48, QFont::Bold));
            P.setBrush(Qt::white);
            P.setPen(Qt::green);
            P.drawText(250, 300, "YOU WIN!");

            P.setFont(QFont("Courier New", 20));
            P.setPen(Qt::white);
            P.drawText(QRect(0, 350, 800, 30), Qt::AlignCenter, "Press SPACE to return to menu");
        }
    }

}

void Gamelogic::Disparar_aliens()
{
    if (lista_alien.isEmpty()) return;

    contador_disparo_alien++;

    // Generar intervalo aleatorio para el próximo disparo
    int intervalo_aleatorio = QRandomGenerator::global()->bounded(intervalo_disparo_min, intervalo_disparo_max);

    if (contador_disparo_alien >= intervalo_aleatorio) {
        contador_disparo_alien = 0;

        // Seleccionar un alien aleatorio que dispare
        int indice_aleatorio = QRandomGenerator::global()->bounded(lista_alien.size());
        Alien* alien_disparador = lista_alien[indice_aleatorio];


        proyectil* nuevo_proyectil = alien_disparador->Disparar();
        if (nuevo_proyectil != nullptr) {
            lista_proyectil_enemigos.append(nuevo_proyectil);
            lista_dibujables.append(nuevo_proyectil);
            //✅Asigno los proyectiles a moviles
            lista_moviles.append(nuevo_proyectil);
        }
    }
}


bool Gamelogic::Aliens_tocaron_borde()
{
    // Verificar si algún alien tocó el borde según la dirección
    for (Alien* alien : lista_alien) {
        QRectF area = alien->get_area();
        alien->set_Vy(descenso_alien);
        if (direccion_derecha) {
            // Si se mueven a la derecha, verificar el borde derecho
            if (area.right() >= margen_derecho) {
                descenso_alien=20.0f;
                return true;
            }
        } else {
            // Si se mueven a la izquierda, verificar el borde izquierdo
            if (area.left() <= margen_izquierdo) {
                descenso_alien=20.0f;
                return true;
            }
        }
    }
    descenso_alien=0.0f;
    return false;
}

void Gamelogic::Mover_enemigos()
{
    if (lista_alien.isEmpty()) return;
    // Verificar si tocaron el borde
    if (Aliens_tocaron_borde()) {
        // Cambiar dirección
        direccion_derecha = !direccion_derecha;

        // Opcional: Aumentar velocidad a medida que quedan menos aliens
         velocidad_alien = 0.3f + (55 - lista_alien.size()) * 0.03f;
    }

    // Mover horizontalmente según la dirección
    float desplazamiento = direccion_derecha ? velocidad_alien : -velocidad_alien;

    for (Alien* alien : lista_alien) {
        alien->set_Vx(desplazamiento);
    }
}

void Gamelogic::Pressbutton(QKeyEvent *ev){

    // Si estamos en el menú, presionar espacio inicia el juego
    if (!juego_iniciado) {
        if (ev->key() == Qt::Key_Space) {
            inicializar_juego();
        }
        return;
    }

    // Si el juego terminó, espacio vuelve al menú
    if (juego_terminado()) {
        if (ev->key() == Qt::Key_Space) {
            juego_iniciado = false;
            // Actualizar puntaje máximo
            if (puntaje > puntaje_maximo) {
                puntaje_maximo = puntaje;
            }
        }
        return;
    }

    // Controles normales del juego
    if (ev->key() == Qt::Key_Left)
        mover_izq = true;
    if (ev->key() == Qt::Key_Right)
        mover_dcha = true;
    if (ev->key() == Qt::Key_Space)
        disparar = true;
    //✅Agrego la lectura de escapa
    if(ev->key()==Qt::Key_Escape)
        pausa=!pausa;//cambio el estado de pausa
}

void Gamelogic::Releasebutton(QKeyEvent *ev){
    if (ev->key() == Qt::Key_Left)
        mover_izq=false;
    if (ev->key() == Qt::Key_Right)
        mover_dcha=false;

    if (ev->key() == Qt::Key_Space)
        disparar=false;
}

void Gamelogic::actualizar()
{
    // No actualizar si no ha iniciado el juego o si terminó
    //✅Agrego la condición de que no se actualice nada si es que está en pausa
    if (!juego_iniciado || juego_terminado() || nave_principal == nullptr || pausa) {
        return;
    }
    if (Aliens_alcanzaron_barreras()) {
        nave_principal->recibir_danio(nave_principal->get_vidas_restantes()); // Matar la nave
        return;
    }

    if (mover_izq && (nave_principal->get_x() - 15 > 0) )
        nave_principal->set_Vx(-10);
    else if (mover_dcha && (nave_principal->get_x() + 15 < 800))
        nave_principal->set_Vx(10);
    else
        nave_principal->set_Vx(0);

    Mover_enemigos();
    for(Movil* movi:lista_moviles)
        movi->movimiento();


    if (disparar && lista_proyectil_jugador.empty()) {
    proyectil* nuevo_proyectil = nave_principal->Disparar();
    if (nuevo_proyectil != nullptr) {
        lista_proyectil_jugador.append(nuevo_proyectil);
        lista_dibujables.append(nuevo_proyectil);
        //✅Asigno el proyectil a moviles
        lista_moviles.append(nuevo_proyectil);
    }
    }


    for (int i = 0; i < lista_proyectil_jugador.size(); i++) {
        proyectil* p = lista_proyectil_jugador[i];
        // p->mover();
        if (p->get_y() < 0 || p->get_colision()) {
            lista_proyectil_jugador.removeAt(i);
            lista_dibujables.removeOne(p);
            lista_moviles.removeOne(p);
            delete p;
            i--;
        }
    }


    for (int i = 0; i < lista_proyectil_enemigos.size(); i++) {
        proyectil* p = lista_proyectil_enemigos[i];
        // p->mover();
        if (p->get_y() > 600 || p->get_colision()) {
            lista_proyectil_enemigos.removeAt(i);
            lista_dibujables.removeOne(p);
            //✅ Remover de lista moviles
            lista_moviles.removeOne(p);
            delete p;
            i--;
        }
    }
    //mover nave bonus si existe
    if (nave_bonus != nullptr) {

        // Eliminar si sale de pantalla o es destruida
        if (nave_bonus->fuera_de_pantalla() || nave_bonus->get_colision()) {
            lista_dibujables.removeOne(nave_bonus);
            //✅La borró de moviles y asigno los puntos correspondientes
            lista_moviles.removeOne(nave_bonus);
            puntaje+=50;
            delete nave_bonus;
            nave_bonus = nullptr;
        }
    }
    Generar_nave_bonus();



    // Disparar aliens
    Disparar_aliens();
    //elimina aliens destruidos y suma puntos
    // Eliminar aliens destruidos y sumar puntos
    for (Alien* alf: lista_alien) {
        if (alf->get_colision()) {
            // Determinar puntos según el tipo de alien
            // Calamar (fila 1): 30 puntos
            // Cangrejo (filas 2-3): 20 puntos
            // Pulpo (filas 4-5): 10 puntos
            calamar* cal = dynamic_cast<calamar*>(alf);
            cangrejo* can = dynamic_cast<cangrejo*>(alf);
            Pulpo* pul = dynamic_cast<Pulpo*>(alf);

            if (cal != nullptr) {
                puntaje += 30;
            } else if (can != nullptr) {
                puntaje += 20;
            } else if (pul != nullptr) {
                puntaje += 10;
            }

            lista_alien.removeOne(alf);
            lista_dibujables.removeOne(alf);
            //✅Los elimino de la lista de moviles
            lista_moviles.removeOne(alf);

            delete alf;
        }
    }
    // Eliminar barreras destruidas
    for (Barrera* barrita:lista_barrera) {
        if (barrita->get_colision()) {
            lista_barrera.removeOne(barrita);
            lista_dibujables.removeOne(barrita);
            delete barrita;
        }
    }
}



void Gamelogic::Verificar_colisiones(){
    // No verificar colisiones si no ha iniciado el juego
    if (!juego_iniciado || nave_principal == nullptr)
        return;
    //colision proyectiles jugador con aliens
    for (proyectil* proy: lista_proyectil_jugador)
        for(Alien* alf: lista_alien){
            if(proy->CheckCollision(alf)){
                alf->set_colision(true);
                proy->set_colision(true);
            }
    }
    // Colisión proyectiles con barreras
    for (proyectil* proy : lista_proyectil_jugador)
        for (Barrera* barr : lista_barrera) {
            if (proy->CheckCollision(barr)) {
                barr->recibir_danio(1);  // Reducir vida de la barrera
                proy->set_colision(true);  // Destruir el proyectil
            }
        }
    // Colisión proyectiles enemigos con nave (ACTUALIZADO)
    for (proyectil* proy : lista_proyectil_enemigos) {
        if (proy->CheckCollision(nave_principal)) {
            nave_principal->recibir_danio(1);  // La nave pierde 1 vida
            proy->set_colision(true);           // Destruir el proyectil
        }
    }
    //✅Acá había código repetido
        // // Colisión proyectiles enemigos con barreras (ESTA ES LA NUEVA)
        // for (proyectil* proy : lista_proyectil_enemigos)
        //     for (Barrera* barr : lista_barrera) {
        //         if (proy->CheckCollision(barr)) {
        //             barr->recibir_danio(1);  // La barrera pierde 1 vida
        //             proy->set_colision(true);  // El proyectil se destruye
        //         }
        //     }
        // Colisión proyectiles enemigos con barreras
    //✅Agrego la colisión entre proyectiles, lo hago para mantener mi organización
    for(proyectil*proy_j :lista_proyectil_jugador)
        for(proyectil*proy_a: lista_proyectil_enemigos)
            if(proy_j->CheckCollision(proy_a)){
                proy_a->set_colision(true);
                proy_j->set_colision(true);
            }

    for (proyectil* proy : lista_proyectil_enemigos)
        for (Barrera* barr : lista_barrera) {
            if (proy->CheckCollision(barr)) {
                barr->recibir_danio(1);
                proy->set_colision(true);
            }
        }
    // Colisión proyectiles jugador con nave bonus
    if (nave_bonus != nullptr) {
        for (proyectil* proy : lista_proyectil_jugador) {
            if (proy->CheckCollision(nave_bonus)) {
                nave_bonus->set_colision(true);
                proy->set_colision(true);
                // Aquí puedes añadir puntos bonus
            }
        }

    }


}
bool Gamelogic::Aliens_alcanzaron_barreras()
{
    if (lista_alien.isEmpty()) return false;

    // Obtener la posición Y más baja de las barreras
    float limite_barrera = 500.0f;  // Usa el mismo valor Y que pusiste en inicializar_juego

    // Si hay barreras, usar su posición real
    if (!lista_barrera.isEmpty()) {
        limite_barrera = lista_barrera[0]->get_y();
    }

    // Verificar si algún alien sobrepasó ese límite
    for (Alien* alien : lista_alien) {
        if (alien->get_y() >= limite_barrera) {
            return true;
        }
    }

    return false;
}
