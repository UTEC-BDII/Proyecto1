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

    cout << "Agregar un registro:\n";
    cout << "--------------\n";
    Basket basket1(1002, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    sf.add(basket1);
    Basket basket2(1012, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    sf.add(basket2);
    Basket basket3(1045, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    sf.add(basket3);
    Basket basket4(1000, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1);
    sf.add(basket4);

    cout << "Busqueda puntual:\n";
    cout << "--------------\n";
    long key = 1045;
    auto r = sf.search(key);
    r.printData();

    cout << "Busqueda en rango:\n";
    cout << "--------------\n";
    long start = 997;
    long end = 9999;
    vector<Basket> v;
    v = sf.rangeSearch(start, end);
    for (auto x : v) {
        x.printData();
    }
}