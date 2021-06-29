#include <QApplication>
#include "Window.h"
#include <QtCore/QJsonObject>
/**
 * @brief Main : Funcion main que llama a la ventana principal para iniciar la aplicaciÃ³n
 */
int main(int argc, char **argv) {
    QApplication app (argc, argv);
    QWidget *window = new Window;
    window->show();
    return app.exec();
}