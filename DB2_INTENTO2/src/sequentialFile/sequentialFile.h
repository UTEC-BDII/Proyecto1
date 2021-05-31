
#ifndef DB2_PROJECT_SEQUENTIALFILE_H
#define DB2_PROJECT_SEQUENTIALFILE_H

#include "../libs.h"
#include "records/Basket.h"
#include "records/WorldPopulation.h"

/* Sequential File class. Manages two files, a main data file and a binary file 
 where operations are executed. New records aren't managed through and auxiliary 
 file, instead they are all inserted to the end of the same file where valid records
 are stored. To do this while retaining the properties of a Sequential File, we
 hold the number of valid and auxiliary records to perform operations such as binary
 search only on the valid records. Moreover, valid records are physically ordered
 while auxiliary records are not necessarily.
 
 This Sequential File is structured to manage only fixed-length records since it
 uses binary search for most of its methods. Aditionally, it can work with any
 record class through the use of templates, T being the data type of the key and
 Record being the class of the Record. Records should also have at least two attributes
 named key (identifier of the record) and next (position of the next record), with 
 the last one being of type long. */
 
template<typename T, typename Record>
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
    void add(Record record);
    void remove(T key);
    Record search(T key);
    vector<Record> rangeSearch(T beginkey, T endkey);
    void reconstruct();

    template <typename T1, typename Rec1>
    friend bool binarySearch(T1 key, sequentialFile<T1, Rec1>* seqFile, long &pos);
};

template <typename T, typename Record>
bool binarySearch(T key, sequentialFile<T, Record>* seqFile, long &pos);

#endif //DB2_PROJECT_SEQUENTIALFILE_H
