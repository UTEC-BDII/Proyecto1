
#ifndef DB2_PROJECT_SEQUENTIALFILE_H
#define DB2_PROJECT_SEQUENTIALFILE_H

#include "../libs.h"
#include "records/Basket.h"
#include "records/WorldPopulation.h"

template<typename T, typename Rec>
class sequentialFile {
private:
    string filename;
    string datfile;
    size_t validRecords;
    size_t auxRecords;
    size_t auxFactor;

public:
    sequentialFile(string filename, size_t auxFactor);
    void createBinaryFile();
    size_t countRecords();
    void add(Rec record);
    void remove(T key); //TODO
    Rec search(T key);
    vector<Rec> rangeSearch(T beginkey, T endkey);
    void reconstruct();

    template <typename T1, typename Rec1>
    friend bool binarySearch(T1 key, sequentialFile<T1, Rec1>* seqFile, long &pos);
};

template <typename T, typename Rec>
bool binarySearch(T key, sequentialFile<T, Rec>* seqFile, long &pos);

#endif //DB2_PROJECT_SEQUENTIALFILE_H
