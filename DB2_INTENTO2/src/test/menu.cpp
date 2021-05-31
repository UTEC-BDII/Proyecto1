#include "menu.h"

using namespace std; 

Menu::Menu(){}

void Menu::limpiar()
{
  for (int i=0; i<30; i++)
  {
    cout << "\n";
  }
}

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
  cout << "1. Usar dataset 1 (basket_analysis)" << endl;
  cout << "2. Usar dataset 2 (WorldPopulation)" << endl;
  cout << endl;
  cout << "0. Salir" << endl;
}

void Menu::showTecnicasMenu()
{
    limpiar();
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
    limpiar();
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
    limpiar();
    switch(dat_)
    {
      case 1:
      {
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
        BasketSeq nuevo1(key, apple, bread, butter, cheese, corn, dill, eggs, ice_cream, kidney_beans, milk, nutmeg, onion, sugar, unicorn, yogurt, chocolate);
        BasketHash nuevo3(key, apple, bread, butter, cheese, corn, dill, eggs, ice_cream, kidney_beans, milk, nutmeg, onion, sugar, unicorn, yogurt, chocolate);
        cout << "Se creo el registro" << endl;
        switch(tec_)
        {
          case 3:
          {
            staticHash<BasketHash> HashFile("basket_analysis.csv");
            HashFile.addToHash(nuevo3);
          }
          break;
          case 4:
          {
            sequentialFile<long, BasketSeq> basketFile("basket_analysis.csv", 3);
            basketFile.add(nuevo1);
          }
          break;
        }
      }
      break;
      case 2:
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
        WorldPopulationSeq nuevo2(key, population, change_perc, net_change, density, urban, urban_perc);
        WorldPopulationHash nuevo4(key, population, change_perc, net_change, density, urban, urban_perc);
        cout << "Se creo el registro" << endl;
        switch(tec_)
        {
          
          case 3: {
            staticHash<WorldPopulationHash> HashFile("WorldPopulation.csv");
            HashFile.addToHash(nuevo4);
            break;
          }
          case 4:
          {
            sequentialFile<long, WorldPopulationSeq> worldFile("WorldPopulation.csv", 3);
            worldFile.add(nuevo2);
            break;
          }
        }
        break;
    }
    cout << "Se añadio el registro" << endl;
    esperar();
}

void Menu::Eliminacion(int dat_, int tec_)
{
    limpiar();
    long key;
    cout << "Ingrese la llave del registro a eliminar: ";
    cin >> key;
    cout << endl;
    switch(dat_)
    {
      case 1:
        switch(tec_)
        {
          case 3: {
            staticHash<BasketHash> HashFile("basket_analysis.csv");
            BasketHash eliminado1;
            HashFile.remove(key, eliminado1);
            break;
          }
          case 4:
            sequentialFile<long, BasketSeq> basketFile("basket_analysis.csv", 3);
            basketFile.remove(key);
            break;
        }
        break;
      case 2:
        switch(tec_)
        {
          case 3: {
            staticHash<WorldPopulationHash> HashFile("WorldPopulation.csv");
            WorldPopulationHash eliminado2;
            HashFile.remove(key, eliminado2);
            break;
          }
          case 4:
            sequentialFile<long, WorldPopulationSeq> WorldFile("WorldPopulation.csv", 3);
            WorldFile.remove(key);
            break;
        }
        break;
    }
    cout << "Se elimino el registro" << endl;
    esperar();
}

void Menu::BusquedaPuntual(int dat_, int tec_)
{
    limpiar();
    long key;
    cout << "Ingrese la llave a buscar: ";
    cin >> key;
    cout << endl;
    switch(dat_)
    {
      case 1:
        switch(tec_)
        {
          case 3: {
            staticHash<BasketHash> HashFile("basket_analysis.csv");
            BasketHash record1;
            auto flag = HashFile.find(key, record1);
            if (flag)
            {
              record1.printData();
            }
            else
            {
              cout << "No se encontro el registro" << endl;
            }
            break;
          }
          case 4:
          {
            sequentialFile<long, BasketSeq> basketFile("basket_analysis.csv", 3);
            BasketSeq record2 = basketFile.search(key);       
            record2.printData();
          }
          break;
        }
        break;
      case 2:
        switch(tec_)
        {
          case 3: {
            staticHash<WorldPopulationHash> HashFile("WorldPopulation.csv");
            WorldPopulationHash record3;
            auto flag = HashFile.find(key, record3);
            if (flag)
            {
              record3.printData();
            }
            else
            {
              cout << "No se encontro el registro" << endl;
            }
            break;
          }
          case 4:
          {
            sequentialFile<long, WorldPopulationSeq> worldFile("WorldPopulation.csv", 3);
            WorldPopulationSeq record4 = worldFile.search(key);   
            record4.printData();   
          }
          break;
        }
        break;
    }
    esperar();
}

void Menu::BusquedaRango(int dat_, int tec_)
{
  limpiar();
  long start;
  long end;
  cout << "Ingrese el inicio del rango: ";
  cin >> start;
  cout << endl;
  cout << "Ingrese el fin del rango: ";
  cin >> end;
  cout << endl;
  vector<BasketSeq> vBasket;
  vector<WorldPopulationSeq> vWorld;
  vector<BasketHash> vHashBasket;
  vector<WorldPopulationHash> vHashWorld;
  switch(dat_)
  {
    case 1:
      switch(tec_)
      {
        case 3:
        {
          staticHash<BasketHash> HashFile("basket_analysis.csv");
          vHashBasket = HashFile.rangeSearch(start, end);
        }
        break;
        case 4:
        {
          sequentialFile<long, BasketSeq> prueba1("basket_analysis.csv", 3);
          vBasket = prueba1.rangeSearch(start, end);
        }
        break;
      }
      for (auto x : vBasket) 
      {
        x.printData();
      }
      break;
    case 2:
      switch(tec_)
      {
        case 3:
        {
          staticHash<WorldPopulationHash> HashFile2("WorldPopulation.csv");
          vHashWorld = HashFile2.rangeSearch(start, end);
        }    
        break;
        case 4:
        {
          sequentialFile<long, WorldPopulationSeq> prueba2("WorldPopulation.csv", 3);
          vWorld = prueba2.rangeSearch(start, end);     
        }
        break;
      }
      for (auto x : vWorld) 
      {
        x.printData();
      } 
      break;
  }
  esperar();
}
