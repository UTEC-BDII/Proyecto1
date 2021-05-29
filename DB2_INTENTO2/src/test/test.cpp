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

    staticHash<Basket> hash(filename);
    
    bool first = true;
    getline(gamefile, str, '\n');
    while (getline(gamefile, str, '\n')) {
        // cout << str;
        Basket* g = new Basket();
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
    sequentialFile<long, Basket> sf("basket_analysis.csv", 5);
    // cout << sf.count(); // funciona
    long pos;
    binarySearch<long, Basket>(5, &sf, pos);
    ///cout << "POS: " << pos << endl;
    
    long start = 993;
    long end = 997;
    auto v = sf.rangeSearch(start, end);
    for (auto x : v) {
        cout << x.key << " - " << x.Apple << " - " << x.Bread << " - " << x.next << "\n";
    }

    Basket basket;
    sf.add(basket);
}