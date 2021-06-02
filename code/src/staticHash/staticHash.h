
#ifndef DB2_PROJECT_STATICHASH_H
#define DB2_PROJECT_STATICHASH_H

#include "../libs.h"
#include "records/Basket.h"
#include "records/WorldPopulation.h"

#define MAX_SIZE_BUCKET 10
#define MAX_SIZE_HASH 100

struct indexElement{
    long index;     // en el datafile no en el index
    long key;
    indexElement(){}
};

struct indexBucket{
    long next;
    indexElement* indexes[MAX_SIZE_BUCKET];      // indexes
    int size;                               // actual size of the bucket

    explicit indexBucket();
    void add(long newIndex, long newKey);
    bool remove(long key);
};

template<typename Record>
class staticHash {
private:
    string filename;
    string indexfilename;
    string datafilename;
    long recordCount;
    long indexCount;

public:
    staticHash(string name);
    long hashFunction(const long& id);
    void addToHash(Record record);
    bool find(const long key, Record& record);
    bool remove(long key, Record& record);
    vector<Record> rangeSearch(long beginkey, long endkey);
    void printHash();
    void printLOQUESEA();
    void printIndexFile();
};

#endif //DB2_PROJECT_STATICHASH_H