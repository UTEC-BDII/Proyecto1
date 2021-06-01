#include "test/menu.cpp"

int main() {
    string filename = choosefile();
    string technique = choosetechnique();
    
    if (technique == "sequential") {
        if (filename == "basket_analysis.csv") {
            testSequential<BasketSeq>(filename);
        } else if (filename == "WorldPopulation.csv") {
            testSequential<WorldPopulationSeq>(filename);
        }
    } else if (technique == "hash") {
        if (filename == "basket_analysis.csv") {
            testHash<BasketHash>(filename);
        } else if (filename == "WorldPopulation.csv") {
            testHash<WorldPopulationHash>(filename);
        }
    } else if (technique == "test") {
        if (filename == "basket_analysis.csv") {
            testTimeBasket(filename, 5, -100, 1500);
        } else if (filename == "WorldPopulation.csv") {
            testTimeWorld(filename, 5, 1920, 2040);
        }
    }

    return 0;
}
