#include "menu.h"

using namespace std; 

template <typename Rec>
Menu<Rec>::Menu(){}
/*
void Menu::limpiar()
{
  cout << "\033[2J\033[0;0H";
}
*/
template <typename Rec>
void Menu<Rec>::esperar()
{
  int pas;
  do
  {
    cout << "Presione 1 para continuar..." << endl;
    cin >> pas;
  }
  while (pas != 1);
  showMenu();
}

template <typename Rec>
Menu<Rec>::~Menu(){}

template <typename Rec>
void Menu<Rec>::showMenu()
{
  limpiar();
  cout << "MENU" << endl;
  cout << "----" << endl;
  cout << endl;
  cout << "1. Probar hash" << endl;
  cout << "2. Probar sequential" << endl;
  cout << endl;
  cout << "0. Salir" << endl;
}
/*
template <typename Rec>
void Menu<Rec>::showSpecificMenu(int val)
{
    if (val == 2)
    {
        cout << "SEQUENTIAL" << endl;
    }
    else
    {
        cout << "HASH" << endl;
    }
    cout << "----" << endl;
    cout << endl;
    cout << "3. Insercion" << endl;
    cout << "4. Eliminación" << endl;
    cout << "5. Busqueda puntual" << endl;
    cout << "6. Busqueda por rango" << endl;
    cout << endl;
    cout << "0. Salir" << endl;
}

template <typename Rec>
void Menu<Rec>::Insercion(int val)
{
    if (val == 2)
    {
        int key;
        Rec record
        cout << "";
    }
    else
    {

    }
    esperar();
}

template <typename Rec>
void Menu<Rec>::Eliminacion(int val)
{
    if (val == 2)
    {

    }
    else
    {
        
    }
    esperar();
}

template <typename Rec>
void Menu<Rec>::BusquedaPuntual(int val)
{
    if (val == 2)
    {

    }
    else
    {
        
    }
    esperar();
}

template <typename Rec>
void Menu<Rec>::BusquedaRango(int val)
{
    if (val == 2)
    {

    }
    else
    {
        
    }
    esperar();
}
*/