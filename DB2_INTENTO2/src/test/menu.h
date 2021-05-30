#include "../staticHash/staticHash.h"
#include "../sequentialFile/sequentialFile.h"
using namespace std; 

/*template <typename T>*/
class Menu
{
  private:
  /*
    sequentialFile<long, Basket> seq1("basket_analysis.csv", 5);
    sequentialFile<long, WorldPopulation> seq2("WorldPopulation.csv", 5);
  */
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
    void crearRegistros();
    void printRegistros();
};
