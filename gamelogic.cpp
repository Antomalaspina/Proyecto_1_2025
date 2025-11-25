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
    nave_principal = new Nave(385, 580);// crea dinámicamente un objeto del tipo nave con su posicion en pantalla
    lista_dibujables.append(nave_principal);// agrega la nave a la lista de dibujables
    lista_moviles.append(nave_principal);// agrega a la nave a la lista de objetos que se mueven

    // Configura temporizador de disparo alien
    contador_disparo_alien = 0;
    intervalo_disparo_min = 60;// valor minimo en frames para que ocurra un disparo
    intervalo_disparo_max = 180;// valor maximo entonces se elige un valor aleatorio entre ellos para que disparen los aliens

    // Configura nave bonus
    nave_bonus = nullptr;
    contador_nave_bonus = 0;
    intervalo_nave_bonus = 600;// cada 600 frames aparece la nave bonus, maso 10s

    //-----------------------------------------------------
    // Generación de las 4 barreras
    //-----------------------------------------------------
    Barrera* barrita;// puntero que apunta a cada barrera generada en el for
    for (int i = 0; i < 4; i++) {
        int x = 40 + i * 230;// aca establezco la separación de barreras se separan cada 230 pix
        int y = 500;//posición vertical para todas iguales
        barrita = new Barrera(10, x, y, 40, 25);// 10 vidas, x,y 40 ancho 25 alto en barrita se almacena el puntero
        lista_barrera.append(barrita);// guarda cada barrera en una lista de barrreras
        lista_dibujables.append(barrita);// las agregaa  la lista de dibujables
    }

    //-----------------------------------------------------
    // Generación de los aliens por filas
    //-----------------------------------------------------
    int columnas = 11;// cantidad de aliens por filla
    int espaciadoX = 50;// distancia entre aliens
    int inicioX = 50;// posicion inicial donde empieza cada alien

    // Fila superior: CALAMAR (30 pts)
    int inicioY_calamar = 90;// posicion en y para la fila de mas arriba
    for (int c = 0; c < columnas; c++) { // bucle para generar 11 calamares
        calamar* calamarcito = new calamar(1, inicioX + c * espaciadoX, inicioY_calamar, 35, 10);// crea dinamicamente los calamares con esos parámetros
        //inicioX+C* espaciadoX calcula el espaciado del calamar c ,ancho ,alto

        lista_alien.append(calamarcito);// agrega cada calamar a la lista de aliens
        lista_dibujables.append(calamarcito);//lo agrega a la lista de dibujables
    }

    // Filas 2-3: CANGREJOS (20 pts)
    int inicioY_cangrejo = 120;//posicion vertical de la primer fila de cangrejos
    for (int f = 0; f < 2; f++) {//genera dos filas
        for (int c = 0; c < columnas; c++) {// con 11 cangrejos por fila
            cangrejo* cangrejito = new cangrejo(1, inicioX + c * espaciadoX, inicioY_cangrejo + f * 40, 35, 10);
            lista_alien.append(cangrejito);
            lista_dibujables.append(cangrejito);
        }
    }

    // Filas 4-5: PULPOS (10 pts)
    int inicioY_pulpo = 200;// posicion vertical de la primera fila de pulpos
    for (int f = 0; f < 2; f++) {
        for (int c = 0; c < columnas; c++) {
            Pulpo* pulpito = new Pulpo(1, inicioX + c * espaciadoX, inicioY_pulpo + f * 40, 35, 10);// en y base + desplazamiento por fila
            lista_alien.append(pulpito);
            lista_dibujables.append(pulpito);
        }
    }

    // Configura movilidad de todos los aliens
    for (Alien* alf : lista_alien) {//recorre la lista de aliens generados
        alf->set_Vx(0.3f);//velocidad horizontal a la derecha
        alf->set_Vy(0.0f);// 0 en y porque no bajan hasta tocar un borde
        lista_moviles.append(alf);//agrega cada alien a la lista de objetos moviles que se actualizan en el update del juego
    }

    juego_iniciado = true;   // Marca que estamos en partida indica al gamelogic que la partida comenzo
}

//---------------------------------------------------------
// Arrancar una nueva partida
//---------------------------------------------------------
void Gamelogic::iniciar_juego()
{
    juego_iniciado = true;// indica al gamelogic que la partida comenzo
    inicializar_juego();
}

//---------------------------------------------------------
// Dibuja el menú de inicio con la tabla de puntajes
//---------------------------------------------------------
void Gamelogic::Dibujar_menu(QPainter &P)
{
    // Título grande
    P.setFont(QFont("Courier New", 48, QFont::Bold));//configuración de la fuente
    P.setPen(Qt::white);//configuramos el color
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
    calamar* calamar_menu = new calamar(1, 270, 375, 25, 8);// reserva memoria dinámica para crear un objeto calamar se guarda el puntero en calamar_menu
    calamar_menu->Dibujar(P);// se llama al metodo dibujar
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
    if (nave_bonus != nullptr) return;  // Si ya existe en la pantalla la nave no la vuelve a dibujar

    contador_nave_bonus++;// contador para saber cuanto tiempo paso desde que aparecio por ultima vez

    if (contador_nave_bonus >= intervalo_nave_bonus) {//cuando el contador supera el intervalo configurado
        contador_nave_bonus = 0;// se resetea el contador

        // Decide si viene desde izq o der
        bool desde_izquierda = QRandomGenerator::global()->bounded(2) == 0;//genera un boolean aleatorio para que determine de donde aparece la nave
        float x_inicial = desde_izquierda ? -50 : 850;// en funcion del lado elegido determina posicion inicial x
        float y_inicial = 40;// altura fija

        // Crea nave enemiga
        nave_bonus = new Nave_enemiga(x_inicial, y_inicial, desde_izquierda);
        lista_dibujables.append(nave_bonus);
        lista_moviles.append(nave_bonus);
        nave_bonus->set_Vx(3.0f);   // Velocidad fija de la nave bonus
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
    if (lista_alien.isEmpty()) return;// si no hay aliens en la lista evita el acceso invalido

    contador_disparo_alien++;//incrementa el contador que define cada cuanto pueden disparar

    // Intervalo aleatorio entre min y max
    int intervalo_aleatorio =
        QRandomGenerator::global()->bounded(intervalo_disparo_min, intervalo_disparo_max);

    if (contador_disparo_alien >= intervalo_aleatorio) {// si el contador supero el intervalo aleatorio
        contador_disparo_alien = 0;//reinicia el contador

        // Escoge un alien al azar
        int indice_aleatorio = QRandomGenerator::global()->bounded(lista_alien.size());//bounded(lista_alien.size()) devuelve un índice válido dentro del rango
        Alien* alien_disparador = lista_alien[indice_aleatorio];// se obtiene el puntero al alien seleccionado para que realice el disparo

        proyectil* nuevo_proy = alien_disparador->Disparar();// el alien genera su proyectil
        if (nuevo_proy != nullptr) {// si lo genera
            lista_proyectil_enemigos.append(nuevo_proy); //se agrega a la lista de proyectiles de enemigos
            lista_dibujables.append(nuevo_proy);// se agrega a la lista de dibujables
            lista_moviles.append(nuevo_proy);// y a la lista de moviles
        }
    }
}

//---------------------------------------------------------
// Detecta si algún alien tocó el borde pantalla
//---------------------------------------------------------
bool Gamelogic::Aliens_tocaron_borde()
{
    for (Alien* alien : lista_alien) {//recorre la listo de los aliens que estan vivos
        QRectF area = alien->get_area();//obtiene el rectangulo que encierra cada alien

        alien->set_Vy(descenso_alien);   // Fuerza a los aliens a tener una velocidad vertical configurada

        if (direccion_derecha) {
            if (area.right() >= margen_derecho) {// si el borde del alien supera el limite de la pantalla
                descenso_alien = 20.0f;// se ajusta la bajada vertical para todos
                return true;// se informa que tocaron borde
            }
        } else {
            if (area.left() <= margen_izquierdo) {// si el alien llega al margen izquierdo
                descenso_alien = 20.0f;// activa la bajada vertical
                return true;// indica que tocaron borde
            }
        }
    }
    descenso_alien = 0.0f;// si ningun alien toco borde no hay bajada vertical
    return false;// no se detectó colision
}

//---------------------------------------------------------
// Movimiento horizontal y vertical de los aliens
//---------------------------------------------------------
void Gamelogic::Mover_enemigos()

//Controla el movimiento horizontal de todos los aliens.
    // Si tocan borde → cambian de dirección y bajan, además aceleran.
    // Distribuye la velocidad horizontal a cada alien.
{
    if (lista_alien.isEmpty()) return;// si no hay aliens no hay que mover nada

    // Si toca borde → cambiar dirección y aumentar velocidad
    if (Aliens_tocaron_borde()) {
        direccion_derecha = !direccion_derecha;
        velocidad_alien = 0.3f + (55 - lista_alien.size()) * 0.03f;// aca configuro la velocidad a medida que se destruyen
    }

    // calcula el desplazamiento horizontal segun la direccion
    float desplazamiento = direccion_derecha ? velocidad_alien : -velocidad_alien;

    for (Alien* alien : lista_alien) {//aplica la velocidad a cada alien
        alien->set_Vx(desplazamiento);
    }
}

//---------------------------------------------------------
// Manejo de teclas presionadas
//---------------------------------------------------------
void Gamelogic::Pressbutton(QKeyEvent *ev)//procesa las teclas presionadas por el jugador
{
    // Menú → inicia con espacio si el juego no inicio
    if (!juego_iniciado) {
        if (ev->key() == Qt::Key_Space) inicializar_juego();
        return;
    }

    // Fin de partida → espacio vuelve al menú
    if (juego_terminado()) {
        if (ev->key() == Qt::Key_Space) {
            juego_iniciado = false;
            if (puntaje > puntaje_maximo) puntaje_maximo = puntaje;//actualiza el puntaje maximo si corresponde
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
// Tecla liberada: desactiva banderas de movimeinto y disparo cuando se sueltan las teclas
//---------------------------------------------------------
void Gamelogic::Releasebutton(QKeyEvent *ev)
{
    if (ev->key() == Qt::Key_Left) mover_izq=false;// cuando se suelta la tecla <- deja de moverse hacia la izquierda
    if (ev->key() == Qt::Key_Right) mover_dcha=false; //cuando se suelta la tecla -> deja de moverse hacia la derecha
    if (ev->key() == Qt::Key_Space) disparar=false;// cuando se suelta la tecla SPACE se corta la interaccion con el disparo
}

//---------------------------------------------------------
// Actualiza todo el estado del juego una vez por frame
//---------------------------------------------------------
void Gamelogic::actualizar()
{
    // Si está en pausa, no inicializo el juego o terminado → no actualizar
    if (!juego_iniciado || juego_terminado() || nave_principal == nullptr || pausa) return;

    // Si los aliens llegaron a las barreras → pierde
    if (Aliens_alcanzaron_barreras()) {
        nave_principal->recibir_danio(nave_principal->get_vidas_restantes());//le quita todas las vidas restantes
        return;
    }

    //-----------------------------------------------------
    // Movimiento de la nave del jugador para que no se salga de pantalla
    //-----------------------------------------------------
    if (mover_izq && (nave_principal->get_x() - 15 > 0))
        nave_principal->set_Vx(-10);// se mueve a la izq a 10px por frame
    else if (mover_dcha && (nave_principal->get_x() + 15 < 800))
        nave_principal->set_Vx(10);// se mueve hacia la derecha
    else
        nave_principal->set_Vx(0);// si no toca teclas se queda quieto

    //-----------------------------------------------------
    // Movimiento general: aliens, proyectiles, nave bonus
    //-----------------------------------------------------
    Mover_enemigos();// actualiza velocidad y direccion de los aliens

    // recorre la lista de todos los moviles y llama a su metodo de movimiento
    for (movil* movi : lista_moviles) movi->movimiento();

    //-----------------------------------------------------
    // Disparo del jugador solo permite un proyectil en pantalla
    //-----------------------------------------------------
    if (disparar && lista_proyectil_jugador.empty()) {// si el jujador dispara y no hay proyectil en pantalla
        proyectil* nuevo = nave_principal->Disparar();// se crea un nuevo proyectil
        if (nuevo != nullptr) {// si la nave devolvio un proyectil válido
            lista_proyectil_jugador.append(nuevo);// se agrega a la lista de proyectiles jugador a la de dibujables y moviles
            lista_dibujables.append(nuevo);
            lista_moviles.append(nuevo);
        }
    }

    //-----------------------------------------------------
    // Eliminar proyectiles del jugador fuera o colisionados
    //-----------------------------------------------------
    for (int i = 0; i < lista_proyectil_jugador.size(); i++) {// recorre todos los proyectiles del jugador
        proyectil* p = lista_proyectil_jugador[i];// apunta al proyectial actual

        if (p->get_y() < 0 || p->get_colision()) {// si el proyectil salio de pantalla o colisiono con algo
            lista_proyectil_jugador.removeAt(i);//se elimina de la lista de proyectiles, el renderizado el movimiento  y se libera memoria
            lista_dibujables.removeOne(p);//
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
    if (nave_bonus != nullptr) {// si existe la nave bonus
        nave_bonus->movimiento();// actualiza su posicion

        if (nave_bonus->fuera_de_pantalla() || nave_bonus->get_colision()) {// si sale de pantalla o fue destruida
            lista_dibujables.removeOne(nave_bonus);// se elimina de todos los lugares
            lista_moviles.removeOne(nave_bonus);
            delete nave_bonus;
            nave_bonus = nullptr;
        }
    }

    // Generar nave bonus si corresponde segun el contador aleatorio
    Generar_nave_bonus();

    //-----------------------------------------------------
    // Nuevamente movimiento alien y disparo
    //-----------------------------------------------------
    Mover_enemigos();
    Disparar_aliens();

    //-----------------------------------------------------
    // Eliminar aliens destruidos y asignar puntos
    //-----------------------------------------------------
    for (Alien* alf : lista_alien) {// recorre lista de aliens
        if (alf->get_colision()) {// si el alien fue colisionado

            // Determinar tipo de alien mediante dynamic_cast
            if (dynamic_cast<calamar*>(alf)) puntaje += 30;
            else if (dynamic_cast<cangrejo*>(alf)) puntaje += 20;
            else if (dynamic_cast<Pulpo*>(alf)) puntaje += 10;

            lista_alien.removeOne(alf);//se elimina de todas las listas
            lista_dibujables.removeOne(alf);
            lista_moviles.removeOne(alf);
            delete alf;//libera memoria
        }
    }

    //-----------------------------------------------------
    // Eliminar barreras destruidas
    //-----------------------------------------------------
    for (Barrera* barrita : lista_barrera) {//recorre todas las barreras
        if (barrita->get_colision()) {// si una fue destruida la elimina de sus listas
            lista_barrera.removeOne(barrita);
            lista_dibujables.removeOne(barrita);
            delete barrita;//libera memoria
        }
    }
}

//---------------------------------------------------------
// Verificación de TODAS las colisiones del juego
//---------------------------------------------------------
void Gamelogic::Verificar_colisiones()
{
    if (!juego_iniciado || nave_principal == nullptr) return;// si el juego no empezo o la nave jugadora no existe no hay que verificar

    // Jugador → aliens
    for (proyectil* proy : lista_proyectil_jugador)// recorre todos los proyectiles del jugador
        for (Alien* alf : lista_alien)// recorre todos los aliens
            if (proy->CheckCollision(alf)) {//si hay colision
                alf->set_colision(true);//marca al alien como destruido
                proy->set_colision(true);
            }//destruye el proyectil

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
//hola
//---------------------------------------------------------
// Detecta si algún alien llegó a la altura de las barreras, si pasa el jugador pierde
//---------------------------------------------------------
bool Gamelogic::Aliens_alcanzaron_barreras()
{
    if (lista_alien.isEmpty()) return false;// si no hay aliens no hace nada

    float limite_barrera = 500.0f; // altura donde están las barreras

    if (!lista_barrera.isEmpty())// si existen toma la altura rela de la primera
        limite_barrera = lista_barrera[0]->get_y();

    // Si algún alien bajó demasiado → jugador pierde
    for (Alien* alien : lista_alien)//recorre todos los aliens
        if (alien->get_y() >= limite_barrera)// si alguno bajo pasando el limite
            return true;// devuelve que tocaron la barrera

    return false;
}
