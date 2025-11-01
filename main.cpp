#include <QApplication>
#include "gamewidget.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Crear y mostrar la ventana principal del juego
    GameWidget window;
    window.show();

    // Ejecutar el bucle principal de la aplicación
    return app.exec();
}
