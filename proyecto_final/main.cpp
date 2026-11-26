#include <QApplication>
#include <QMessageBox>
#include <stdexcept>
#include "juego.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try{
        juego juego;
        juego.show();
        return a.exec();
    }

    catch (const std::exception &e){

        QMessageBox::critical(nullptr, "no se puede iniciar el juego", e.what());
        return 1;
    }
}
