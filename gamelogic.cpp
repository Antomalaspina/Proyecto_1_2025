#include "gamelogic.h"

Gamelogic::Gamelogic(Nave* nave,
                     QList<Barrera*> barrera,
                     QList<Calamar*> calamar,
                     QList<Cangrejo*> cangrejo,
                     QList<Pulpo*> pulpo,
                     QList<Proyectil*> proyectil) {
    nave_principal = nave;
    lista_barrera = barrera;
    lista_calamar = calamar;
    lista_cangrejo = cangrejo;
    lista_pulpo = pulpo;
    lista_proyectil = proyectil;
}
