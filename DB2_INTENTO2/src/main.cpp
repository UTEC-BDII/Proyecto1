#include "test/test.cpp"
#include "test/menu.h"

int main() {

    Menu M;
    M.showMenu();
    int op;
    int dat;
    int tec;
    do
    {
        cin >> op;
        switch (op)
        {
        case 0:
            cout << "se acabo..." << endl;
            break;
        case 1:
        case 2:
            dat = op;
            M.showTecnicasMenu();
            break;
        case 3:
        case 4:
            tec = op;
            M.showOperationsMenu();
            break;
        case 5:
            M.Insercion(dat, tec);
            break;
        case 6:
            M.Eliminacion(dat, tec);
            break;
        case 7:
            M.BusquedaPuntual(dat, tec);
            break;
        case 8:
            M.BusquedaRango(dat, tec);
            break;
        }
    }
    while (op != 0);
    
    // testHash();
    //testSequential();

    return 0;
}
