#include "menu.h"

string choosefile() {
  int n;
  do {
    clear();
    cout << "  Choose dataset:  \n";
    cout << "-------------------\n";
    cout << "1. basket_analysis\n";
    cout << "2. WorldPopulation\n";
    cin >> n;
  } while(n < 1 || n > 2);
  switch (n) {
    case 1:
      return "basket_analysis.csv";
    case 2:
      return "WorldPopulation.csv";
    default:
      cerr << "ERROR";
      break;
  }
  return "";
}

void clear() {
  for (int i=0; i<30; i++) {
    cout << "\n";
  }
}

string choosetechnique() {
  int n;
  do {
    clear();
    cout << "  Choose technique:  \n";
    cout << "-------------------\n";
    cout << "1. Sequential File\n";
    cout << "2. Static Hash\n";
    cout << "3. Test execution time of both techniques on dataset\n";
    cin >> n;
  } while(n < 1 || n > 3);
  switch (n) {
    case 1:
      return "sequential";
    case 2:
      return "hash";
    case 3:
      return "test";
    default:
      cerr << "ERROR";
      break;
  }
  return "";
}

template <typename Record>
void testHash(string filename) {
  staticHash<Record> hash(filename);

  int n;
  do {
    do {
      clear();
      cout << "   Choose action:   \n";
      cout << "--------------------\n";
      cout << "1. Add record\n";
      cout << "2. Remove record\n";
      cout << "3. Search record\n";
      cout << "4. Search records in range\n";
      cin >> n;
    } while(n < 1 || n > 4);
    
    switch (n) {
      case 1: {
        clear();
        cout << "Insert key: ";
        Record record;
        record.input();
        hash.addToHash(record);
        break;
      }
      case 2: {
        clear();
        cout << "Insert key: ";
        long key;
        cin >> key;
        Record record;
        if (hash.remove(key, record)) {
          cout << "Record has been removed\n";
        } else {
          cout << "Record has not been removed\n";
        }
        break;
      }
      case 3: {
        clear();
        cout << "Insert key: ";
        long key;
        cin >> key;
        Record record;
        if (hash.find(key, record)) {
          cout << "\nRecord was found\n";
          record.printData();
        } else {
          cout << "Record was not found\n";
        }
        break;
      }
      case 4: {
        clear();
        long beginkey, endkey;
        cout << "Insert start key: ";
        cin >> beginkey;
        cout << "Insert final key: ";
        cin >> endkey;
        cout << endl;
        vector<Record> v = hash.rangeSearch(beginkey, endkey);
        for (auto i : v) {
          i.printData();
        }
        break;
      }
    }

    cout << "Enter any key to continue or 0 to exit...\n";
    cin >> n;
  } while (n != 0);
}

template <typename Record>
void testSequential(string filename) {
  int auxFactor;
  clear();
  cout << "Define auxiliary record factor: ";
  cin >> auxFactor;
  sequentialFile<long, Record> sf(filename, auxFactor);

  int n;
  do {
    do {
      clear();
      cout << "   Choose action:   \n";
      cout << "--------------------\n";
      cout << "1. Add record\n";
      cout << "2. Remove record\n";
      cout << "3. Search record\n";
      cout << "4. Search records in range\n";
      cin >> n;
    } while(n < 1 || n > 4);
    
    long key, start, end;
    switch (n) {
      case 1: {
        clear();
        Record record;
        record.input();
        cout << endl;
        sf.add(record);
        break;
      }
      case 2: {
        clear();
        cout << "Insert key: ";
        cin >> key;
        sf.remove(key);
        break;
      }
      case 3: {
        clear();
        cout << "Insert key: ";
        cin >> key;
        cout << endl;
        Record record2 = sf.search(key);
        record2.printData();
        break;
      }
      case 4: {
        clear();
        cout << "Insert start key: ";
        cin >> start;
        cout << "Insert end key: ";
        cin >> end;
        cout << endl;
        vector<Record> v = sf.rangeSearch(start, end);
        for (auto i : v) {
          i.printData();
        }
        break;
      }
      default:
        cerr << "ERROR";
        break;
    }

    cout << "Enter any key to continue or 0 to exit...\n";
    cin >> n;
  } while (n != 0);
}

void testTimeBasket(string filename, int auxFactor, long start, long end) {
    clear();
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> distr(start, end);

    ofstream outFile;
    long key;
    
    outFile.open("results_basket_seq.csv");
    sequentialFile<long, BasketSeq> sf(filename, auxFactor);

    cout << "Sequential File add test.\n";
    cout << "--------------------------\n";
    outFile << "Operacion,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10\n";
    outFile << "add,";
    for (size_t i = 0; i < 10; i++) {
        key = distr(gen);
        BasketSeq basket(key);
        auto t1 = high_resolution_clock::now();
        sf.add(basket);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        outFile << ms_double.count();
        if (i < 9) outFile << ",";
    }

    cout << "\nSequential File search test.\n";
    cout << "--------------------------\n";
    outFile << "\nsearch,";
    for (size_t i = 0; i < 10; i++) {
        key = distr(gen);
        auto t1 = high_resolution_clock::now();
        sf.search(key);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        outFile << ms_double.count();
        if (i < 9) outFile << ",";
    }
    outFile.close();

    outFile.open("results_basket_hash.csv");
    staticHash<BasketHash> hash(filename);
    BasketHash record;

    cout << "\nStatic Hash add test.\n";
    cout << "--------------------------\n";
    outFile << "Operacion,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10\n";
    outFile << "add,";
    for (size_t i = 0; i < 10; i++) {
        key = distr(gen);
        BasketHash basket(key);
        auto t1 = high_resolution_clock::now();
        hash.addToHash(basket);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        outFile << ms_double.count();
        if (i < 9) outFile << ",";
    }

    cout << "\nStatic Hash search test.\n";
    cout << "--------------------------\n";
    outFile << "\nsearch,";
    for (size_t i = 0; i < 10; i++) {
        key = distr(gen);
        auto t1 = high_resolution_clock::now();
        hash.find(key, record);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        outFile << ms_double.count();
        if (i < 9) outFile << ",";
    }
    outFile.close();
    cout << "Results can be viewed on results_basket_seq.csv and results_basket_hash.csv\n";
}

void testTimeWorld(string filename, int auxFactor, long start, long end) {
    clear();
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 gen(seed);
    std::uniform_int_distribution<> distr(start, end);

    ofstream outFile;
    long key;
    
    outFile.open("results_world_seq.csv");
    sequentialFile<long, WorldPopulationSeq> sf(filename, auxFactor);

    cout << "Sequential File add test.\n";
    cout << "--------------------------\n";
    outFile << "Operacion,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10\n";
    outFile << "add,";
    for (size_t i = 0; i < 10; i++) {
        key = distr(gen);
        WorldPopulationSeq world(key);
        auto t1 = high_resolution_clock::now();
        sf.add(world);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        outFile << ms_double.count();
        if (i < 9) outFile << ",";
    }

    cout << "\nSequential File search test.\n";
    cout << "--------------------------\n";
    outFile << "\nsearch,";
    for (size_t i = 0; i < 10; i++) {
        key = distr(gen);
        auto t1 = high_resolution_clock::now();
        sf.search(key);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        outFile << ms_double.count();
        if (i < 9) outFile << ",";
    }
    outFile.close();

    outFile.open("results_world_hash.csv");
    staticHash<WorldPopulationHash> hash(filename);
    WorldPopulationHash record;

    cout << "\nStatic Hash add test.\n";
    cout << "--------------------------\n";
    outFile << "Operacion,T1,T2,T3,T4,T5,T6,T7,T8,T9,T10\n";
    outFile << "add,";
    for (size_t i = 0; i < 10; i++) {
        key = distr(gen);
        WorldPopulationHash world(key);
        auto t1 = high_resolution_clock::now();
        hash.addToHash(world);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        outFile << ms_double.count();
        if (i < 9) outFile << ",";
    }

    cout << "\nStatic Hash search test.\n";
    cout << "--------------------------\n";
    outFile << "\nsearch,";
    for (size_t i = 0; i < 10; i++) {
        key = distr(gen);
        auto t1 = high_resolution_clock::now();
        hash.find(key, record);
        auto t2 = high_resolution_clock::now();
        duration<double, std::milli> ms_double = t2 - t1;
        outFile << ms_double.count();
        if (i < 9) outFile << ",";
    }
    outFile.close();
    cout << "Results can be viewed on results_world_seq.csv and results_world_hash.csv\n";
}