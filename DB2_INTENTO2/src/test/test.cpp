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
    sequentialFile<long, BasketSeq> sf("basket_analysis.csv", 3);

    cout << "\nAgregar un registro:\n";
    cout << "--------------\n";
    BasketSeq basket1(1002);
    sf.add(basket1);
    BasketSeq basket2(997);
    sf.add(basket2);
    BasketSeq basket3(1045);
    sf.add(basket3);
    //BasketSeq basket4(1000);
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

void testTimeSeq() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(-100, 1500);

    ofstream outFile("results_seq.csv");
    sequentialFile<long, BasketSeq> sf("basket_analysis.csv", 10);
    long key;

    cout << "Add test.\n";
    outFile << "add,";
    for (size_t i = 0; i < 5; i++) {
        key = distr(gen);
        BasketSeq basket(key);
        auto t1 = high_resolution_clock::now();
        sf.add(basket);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        outFile << ms_double.count() << ",";
    }

    cout << "Search test.\n";
    outFile << "\nsearch,";
    for (size_t i = 0; i < 5; i++) {
        key = distr(gen);
        auto t1 = high_resolution_clock::now();
        sf.search(key);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        outFile << ms_double.count() << ",";
    }
}

void testTimeHash() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(-100, 1500);

    ofstream outFile("results_hash.csv");
    staticHash<BasketSeq> hash("basket_analysis.csv");
    //long key;

    cout << "Add test.\n";
    outFile << "add,";
    for (size_t i = 0; i < 5; i++) {
        //key = distr(gen);
        //BasketSeq basket(key);
        auto t1 = high_resolution_clock::now();
        //hash.add(basket);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        outFile << ms_double.count() << ",";
    }

    cout << "Search test.\n";
    outFile << "\nsearch,";
    for (size_t i = 0; i < 5; i++) {
        //key = distr(gen);
        auto t1 = high_resolution_clock::now();
        //hash.search(key);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        outFile << ms_double.count() << ",";
    }
}