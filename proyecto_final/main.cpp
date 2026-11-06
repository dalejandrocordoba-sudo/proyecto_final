#include <iostream>
#include <QMessageBox>
#include <stdexcept>
#include "juego.h"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    try{
        Juego juego;
        juego.show();
        return a.exc();
    }

    catch (const std::exception &e){

        QMessangeBox::critical(nullptr, "no se puede iniciar el juego", e.what());
        return 1;
    }
    cout << "Hello World!" << endl;
    return 0;
}
