#include <bits/stdc++.h>
#include "../staticHash/staticHash.h"
#include "../sequentialFile/sequentialFile.h"
using namespace std; 
template <typename Rec>
class Menu
{
  private:
  /*
    sequentialFile<long, Basket> seq1("basket_analysis.csv", 5);
    sequentialFile<long, WorldPopulation> seq2("WorldPopulation.csv", 5);
  */
    staticHash<Rec> hash;
  public:
    Menu();
    void limpiar();
    void esperar();
    virtual ~Menu();
    void showMenu();
    void agregA();
    void removA();
    void showA();
    void showAllA();
    void createA();
};
