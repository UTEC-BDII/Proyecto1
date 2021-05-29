//
// Created by Jorge on 25/05/2021.
//

#include "test.h"

void testHash() {

    ifstream gamefile;
    string filename = "games.csv";
    string str;

    gamefile.open(filename.c_str());
    if (!gamefile) {
        cerr << "ERROR" << endl;
        exit(1);
    }

    staticHash hash;
    
    bool first = true;
    getline(gamefile, str, '\n');
    while (getline(gamefile, str, '\n')) {
        // cout << str;
        game* g = new game();
        g->serialize(str);
        hash.addToHash(g, g->getKey());
    }
    cout << endl;
    hash.printHash();
    /*
    staticHash hash;
    string s = "TZJHLljE,FALSE,1.50421E+12,1.50421E+12,13,outoftime,white,15+2,bourgris,1500,a-00,1191,d4 d5 c4 c6 cxd5 e6 dxe6 fxe6 Nf3 Bb4+ Nc3 Ba5 Bf4,D10,Slav Defense: Exchange Variation,5";
    game* g = new game();
    g->serialize(s);
    hash.addToHash(g, "TZJHLljE");
     */
    // game* n = hash->find("hola");

    gamefile.close();
}

void testSequential() {
    sequentialFile<Basket> sf("basket_analysis.csv");
    // cout << sf.count(); // funciona
    long pos;
    binarySearch<int, Basket>(5, sf, pos);
    ///cout << "POS: " << pos << endl;
    auto v = rangeSearch(5, 10, sf);
    for (auto x : v) {
        cout << x.key << " - ";
    }

}