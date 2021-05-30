#include "menu.h"

using namespace std; 

Menu::Menu(){}
/*
void Menu::limpiar()
{
  cout << "\033[2J\033[0;0H";
}
*/

void Menu::esperar()
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

Menu::~Menu(){}

void Menu::showMenu()
{
  limpiar();
  cout << "ESCOGER DATASET" << endl;
  cout << "---------------" << endl;
  cout << endl;
  cout << "1. Usar dataset 1" << endl;
  cout << "2. Usar dataset 2" << endl;
  cout << endl;
  cout << "0. Salir" << endl;
}
/*
void Menu::showTecnicasMenu()
{
    cout << "ESCOGER TECNICA DE ORGANIZACIÓN" << endl;
    cout << "-------------------------------" << endl;
    cout << endl;
    cout << "3. Hash" << endl;
    cout << "4. Sequential" << endl;
    cout << endl;
    cout << "0. Salir" << endl;
}

void Menu::showOperationsMenu()
{
    cout << "ESCOGER OPERACION" << endl;
    cout << "-----------------" << endl;
    cout << endl;
    cout << "5. Insertar un registro" << endl;
    cout << "6. Eliminar un registro" << endl;
    cout << "7. Buscar un registro por llave" << endl;
    cout << "8. Buscar registros por rango" << endl;
    cout << endl;
    cout << "0. Salir" << endl;
}

void Menu::Insercion(int dat_, int tec_)
{
    switch(dat_)
    {
      case 1:
        switch(tec_)
        {
          case 3:
            
            break;
          case 4:
            long key;
            cout << "Llave: ";
            cin >> key;
            cout << endl;

            string temp;
            bool apple;
            cout << "Apple: ";
            cin >> temp;
            apple = temp == "true";
            cout << endl;

            bool bread;
            cout << "Bread: ";
            cin >> temp;
            bread = temp == "true";
            cout << endl;

            bool butter;
            cout << "Butter: ";
            cin >> temp;
            butter = temp == "true";
            cout << endl;

            bool cheese;
            cout << "Cheese: ";
            cin >> temp;
            cheese = temp == "true";
            cout << endl;

            bool corn;
            cout << "Corn: ";
            cin >> temp;
            corn = temp == "true";
            cout << endl;

            bool dill;
            cout << "Dill: ";
            cin >> temp;
            dill = temp == "true";
            cout << endl;

            bool eggs;
            cout << "Eggs: ";
            cin >> temp;
            eggs = temp == "true";
            cout << endl;

            bool ice_cream;
            cout << "Ice cream: ";
            cin >> temp;
            ice_cream = temp == "true";
            cout << endl;

            bool kidney_beans;
            cout << "Kidney beans: ";
            cin >> temp;
            kidney_beans = temp == "true";
            cout << endl;

            bool milk;
            cout << "Milk: ";
            cin >> temp;
            milk = temp == "true";
            cout << endl;

            bool nutmeg;
            cout << "Nutmeg: ";
            cin >> temp;
            nutmeg = temp == "true";
            cout << endl;

            bool onion;
            cout << "Onion: ";
            cin >> temp;
            onion = temp == "true";
            cout << endl;

            bool sugar;
            cout << "Sugar: ";
            cin >> temp;
            sugar = temp == "true";
            cout << endl;

            bool unicorn;
            cout << "Unicorn: ";
            cin >> temp;
            unicorn = temp == "true";
            cout << endl;

            bool yogurt;
            cout << "Yogurt: ";
            cin >> temp;
            yogurt = temp == "true";
            cout << endl;

            bool chocolate;
            cout << "Chocolate: ";
            cin >> temp;
            chocolate = temp == "true";
            cout << endl;

            cout << "Creando registro ..." << endl;
            Basket record(key, apple, bread, butter, cheese, corn, dill, eggs, ice_cream, kidney_beans, milk, nutmeg, onion, sugar, unicorn, yogurt, chocolate);
            cout << "Se creo el registro" << endl;
            sequentialFile<long, Basket> sf("basket_analysis.csv", 5);
            sf.add(record);
            cout << "Se añadio el registro" << endl;

            break;
        }
        break;
      case 2:
        swtch(tec_)
        {
          case 3:
            break;
          case 4:
            long key;
            cout << "Llave: ";
            cin >> key;
            cout << endl;

            long population;
            cout << "Population: ";
            cin >> population;
            cout << endl;

            float change_perc;
            cout << "Change Perc: ";
            cin >> change_perc;
            cout << endl;

            long net_change;
            cout << "Net change: ";
            cin >> net_change;
            cout << endl;

            int density;
            cout << "Density: ";
            cin >> density;
            cout << endl;

            long urban;
            cout << "Urban: ";
            cin >> urban;
            cout << endl;

            int urban_perc;
            cout << "Urban perc: ";
            cin >> urban_perc;
            cout << endl;

            cout << "Creando registro ..." << endl;
            WorldPopulation record(key, population, change_perc, net_change, density, urban, urban_perc);
            cout << "Se creo el registro" << endl;
            sequentialFile<long, WorldPopulation> sf("basket_analysis.csv", 5);
            sf.add(record);
            cout << "Se añadio el registro" << endl;

            break;
        }
        break;
    }
    esperar();
}

void Menu::Eliminacion(int dat_, int tec_)
{
    switch(dat_)
    {
      case 1:
        swtch(tec_)
        {
          case 3:
            
            break;
          case 4:

            
            break;
        }
        break;
      case 2:
        swtch(tec_)
        {
          case 3:
            break;
          case 4:
            break;
        }
        break;
    }
    esperar();
}

void Menu::BusquedaPuntual(int dat_, int tec_)
{
    long key;
    cout << "Ingrese la llave a buscar: ";
    cin >> key;
    cout << endl;
    switch(dat_)
    {
      case 1:
        swtch(tec_)
        {
          case 3:
            staticHash<BasketHash> sh("basket_analysis.csv");
            BasketHash record;
            sh.find(key, record);
            break;
          case 4:
            sequentialFile<long, Basket> sf("basket_analysis.csv", 5);
            Basket record = sf.search(key);      
            record.printData();      
            break;
        }
        break;
      case 2:
        swtch(tec_)
        {
          case 3:
            
            break;
          case 4:
            sequentialFile<long, WorldPopulation> sf("WorldPopulation.csv", 5);
            Basket record = sf.search(key);      
            record.printData();  
            break;
        }
        break;
    }
    esperar();
}

void Menu::BusquedaRango(int dat_)
{
  long start;
  long end;
  cout << "Ingrese el inicio del rango: ";
  cin >> start;
  cout << endl;
  cout << "Ingrese el fin del rango: ";
  cin >> end;
  cout << endl;
  vector<Basket> v;
  switch(dat_)
  {
    case 1:
      sequentialFile<long, Basket> sf("basket_analysis.csv", 5);
      break;
    case 2:
      sequentialFile<long, WorldPopulation> sf("WorldPopulation.csv", 5);
      break;
  }
  v = sf.rangeSearch(start, end);      
  for (auto x : v) 
  {
    x.printData();
  }  
  esperar();
}
*/