//
// Created by Jorge on 25/05/2021.
//

#include "test.h"

void testHash() {

    ifstream gamefile;
    string filename = "basket_analysis.csv";
    string str;

    gamefile.open(filename.c_str());
    if (!gamefile) {
        cerr << "ERROR" << endl;
        exit(1);
    }

    staticHash<BasketHash> hash(filename);
    
    bool first = true;
    getline(gamefile, str, '\n');
    while (getline(gamefile, str, '\n')) {
        // cout << str;
        BasketHash* g = new BasketHash();
        g->serialization(str);
        // hash.addToHash(g, g->getKey());
    }
    cout << endl;
    //hash.printHash();
    /*
    staticHash hash;
    string s = "TZJHLljE,FALSE,1.50421E+12,1.50421E+12,13,outoftime,white,15+2,bourgris,1500,a-00,1191,d4 d5 c4 c6 cxd5 e6 dxe6 fxe6 Nf3 Bb4+ Nc3 Ba5 Bf4,D10,Slav Defense: Exchange Variation,5";
    game* g = new game();
    g->serialize(s);
    hash.addToHash(g, "TZJHLljE");

    // game* n = hash->find("hola");
    */

    gamefile.close();
}

void testSequential() {
    sequentialFile<long, Basket> sf("basket_analysis.csv", 3);

    cout << "\nAgregar un registro:\n";
    cout << "--------------\n";
    Basket basket1(1002, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    sf.add(basket1);
    Basket basket2(997, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    sf.add(basket2);
    Basket basket3(1045, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    sf.add(basket3);
    //Basket basket4(1000, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    //sf.add(basket4);

    long key, start, end;

    cout << "\nBusqueda puntual:\n";
    cout << "--------------\n";
    key = 998;
    auto r = sf.search(key);
    r.printData();

    cout << "\nEliminar un regsitro:\n";
    cout << "--------------\n";
    key = 2000;
    sf.remove(key);

    cout << "\nBusqueda en rango:\n";
    cout << "--------------\n";
    start = 996;
    end = 9999;
    auto v = sf.rangeSearch(start, end);
    for (auto x : v) {
        x.printData();
    }
}