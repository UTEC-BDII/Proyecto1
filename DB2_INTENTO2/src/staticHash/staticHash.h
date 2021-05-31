//
// Created by Jorge on 21/05/2021.
//

#ifndef DB2_PROJECT_STATICHASH_H
#define DB2_PROJECT_STATICHASH_H

#include "../libs.h"

#define MAX_SIZE_BUCKET 10
#define MAX_SIZE_HASH 100

class RecordHash {
protected:

    virtual void read() = 0;
    virtual void write() = 0;
    virtual void serialization(string object) = 0;
};

class BasketHash : public RecordHash {
public:
    long key;    //id
    bool Apple;
    bool Bread;
    bool Butter;
    bool Cheese;
    bool Corn;
    bool Dill;
    bool Eggs;
    bool Ice_cream;
    bool Kidney_Beans;
    bool Milk;
    bool Nutmeg;
    bool Onion;
    bool Sugar;
    bool Unicorn;
    bool Yogurt;
    bool chocolate;

public:
    void read() override{

    }

    void write() override{

    }

    void serialization(string object) override {
        int i=0;
        string att;
        for (char letter : object) {
            if (letter != ',') {
                att.push_back(letter);
            } else {
                bool value = att == "True";
                switch (i) {
                    case 0:
                        key = stol(att);
                        break;
                    case 1:
                        Apple = value;
                        break;
                    case 2:
                        Bread = value;
                        break;
                    case 3:
                        Butter = value;
                        break;
                    case 4:
                        Cheese = value;
                        break;
                    case 5:
                        Corn = value;
                        break;
                    case 6:
                        Dill = value;
                        break;
                    case 7:
                        Eggs = value;
                        break;
                    case 8:
                        Ice_cream = value;
                        break;
                    case 9:
                        Kidney_Beans = value;
                        break;
                    case 10:
                        Milk = value;
                        break;
                    case 11:
                        Nutmeg = value;
                        break;
                    case 12:
                        Onion = value;
                        break;
                    case 13:
                        Sugar = value;
                        break;
                    case 14:
                        Unicorn = value;
                        break;
                    case 15:
                        Yogurt = value;
                        break;
                    default:
                        cerr << "Error in serializing\n";
                        break;
                }
                i++;
                att.clear();
            }
        }
        chocolate = att == "True";
    }

    void print() {
        cout << key << "," << Apple << "," << Bread << "," << Butter << "," << Cheese << "," << Corn << "," << Dill << "," << Eggs << "," << Ice_cream << "," << Kidney_Beans << "," <<  Milk << "," << Nutmeg << "," << Onion << "," << Sugar << "," << Unicorn << "," << Yogurt << "," << chocolate;
    }
};


struct indexElement{
    long index;     // en el datafile no en el index
    long key;
    indexElement(){}
    //indexElement(long _index_, long _key_) : index(_index_), key(_key_){}
};

struct indexBucket{
    long next;
    indexElement* indexes[MAX_SIZE_BUCKET];      // indexes
    int size;                               // actual size of the bucket

    explicit indexBucket() : next(-1), size(0) {}

    void add(long newIndex, long newKey) {
        indexes[size] = new indexElement();
        indexes[size]->index = newIndex;
        indexes[size]->key = newKey;
        size++;
    }

    bool remove(long key) {
        if (size == 0)
            return false;
        if (indexes[size-1]->key == key) {
            size--;
            return true;
        }
        for (int i=0; i<size; i++) {
            if (indexes[i]->key == key) {
                indexes[i] = indexes[size-1];
                size--;
                return true;
            }
        }
        return false;
    }
};

template<typename Record>
class staticHash {
private:
    string filename;
    string indexfilename;
    string datafilename;
    long recordCount;
    long indexCount;
    // Bucket* buckets[MAX_SIZE_HASH];      // Array de punteros a buckets

public:
    staticHash(string name) : filename(name), recordCount(0), indexCount(0) {
        ifstream infile, indexinfile;
        ofstream outfile, indexoutfile;

        infile.open(filename.c_str());

        datafilename = regex_replace(filename, regex("csv"), "dat");
        outfile.open(datafilename, ios::out | ios::binary);

        indexfilename = "index.dat";
        indexoutfile.open(indexfilename, ios::binary);

        indexinfile.open(indexfilename, ios::in | ios::binary);

        if(!infile || !outfile || !indexoutfile || !indexinfile) {
            cerr << "ERROR" << endl;
            exit(1);
        }

        indexBucket bucket{};
        // cout << bucket.next << "::::::::::::::" << endl;
        // cout << sizeof(indexBucket) << "::::::::::::::" << endl;
        for (int i=0; i<MAX_SIZE_HASH; i++)
            indexoutfile.write((char*)&bucket, sizeof(indexBucket));

        indexCount = MAX_SIZE_HASH;

        string str;

        getline(infile, str, '\n');
        while (getline(infile, str, '\n')) {
            Record r;
            r.serialization(str);

            // escribir en file.dat
            outfile.write((char*)&r, sizeof(r));

            long address = (recordCount++)*sizeof(Record);
            long hashKey = hashFunction(r.key);
            indexBucket nbucket;    //cambiar por bucket luego
            indexinfile.seekg(hashKey*sizeof(indexBucket));
            indexinfile.read((char*)&nbucket, sizeof(indexBucket));
            if ( nbucket.size < MAX_SIZE_BUCKET ) {
                //cout << "HASHKEY: " << hashKey << " - " << "OLD SIZE: " << nbucket.size << " - ";
                nbucket.add(address, r.key);
                indexoutfile.seekp(hashKey*sizeof(indexBucket));
                indexoutfile.write((char*)&nbucket, sizeof(indexBucket));
                //cout << "ADDRESS: " << address << " - " << "KEY: " << r.key << " - " << "NEW SIZE: " << nbucket.size << endl;
            } else {
                cout << "YA NO POR FAVOR";
                indexBucket newBucket;

                newBucket.add(address, r.key);
                newBucket.next = (indexCount++)*sizeof(indexBucket);
                cout << endl << "INDEX: " << indexCount << " - NEXT:" << newBucket.next << endl;

                indexoutfile.seekp(hashKey*sizeof(indexBucket));
                indexoutfile.write((char*)&newBucket, sizeof(indexBucket));

                indexoutfile.seekp((indexCount-1)*sizeof(indexBucket));
                indexoutfile.write((char*)&nbucket, sizeof(indexBucket));
            }
        }
        indexoutfile.close();
        indexinfile.close();

        outfile.close();
        infile.close();

        cout << endl << "recordCount: " << recordCount << endl;
    }

    int hashFunction(const long& id) {
        return id % MAX_SIZE_HASH;
    }

    void addToHash(Record record) {
        long address = recordCount*sizeof(record);

        fstream outfile;
        outfile.open(datafilename, ios::app | ios::binary);
        outfile.write((char*)&record, sizeof(Record));
        outfile.close();

        long hashKey = hashFunction(record.key);
        indexBucket bucket;
        ifstream infile;
        infile.open(indexfilename, ios::in | ios::binary);
        infile.seekg(hashKey*sizeof(indexBucket));
        infile.read((char*)&bucket, sizeof(indexBucket));
        infile.close();

        if ( bucket.size < MAX_SIZE_BUCKET ) {
            bucket.add(address, record.key);
            //cout << endl << "[" << bucket.size << "]" << endl;

            outfile.open(indexfilename, ios::out | ios::binary);
            outfile.seekp(hashKey*sizeof(indexBucket));
            outfile.write((char*) &bucket, sizeof(indexBucket));
            outfile.close();
        } else {
            // Create a new bucket using LIFO
            indexBucket newBucket;

            // Add the new index in a new empty bucket
            newBucket.add(address, record.key);
            newBucket.next = (indexCount++)*sizeof(indexBucket);

            // write the new bucket in old bucket's position
            outfile.open(indexfilename);
            outfile.seekp(hashKey*sizeof(indexBucket));
            outfile.write((char*)&newBucket, sizeof(indexBucket));

            // Save the old bucket to add it into the end of the file
            outfile.seekp((indexCount-1)*sizeof(indexBucket));
            outfile.write((char*)&bucket, sizeof(indexBucket));
            outfile.close();
        }

    }

    bool find(const long key, Record& record) {
        long hashKey = hashFunction(key);
        indexBucket bucket;
        ifstream indexfile, infile;

        indexfile.open(indexfilename, ios::binary);

        long address;
        long n = hashKey*sizeof(indexBucket);
        do{
            indexfile.seekg(n);
            indexfile.read((char*)&bucket, sizeof(indexBucket));
            for (int i=0; i<bucket.size; i++) {
                if (bucket.indexes[i]->key == key) {
                    address = bucket.indexes[i]->index;
                    indexfile.close();

                    infile.open(datafilename, ios::binary);
                    infile.seekg(address);
                    infile.read((char*)&record, sizeof(Record));
                    infile.close();
                    return true;
                }
            }
            n = bucket.next;
        } while (n != -1);
        return false;
    }

    bool remove(long key, Record& record) {
        // Podría crear un array que tenga posiciones eliminadas y
        // que al momento de insertar vea si este array tiene un
        // elemento para tomar esa posicion e insertar en el datafile
        // en esa posicion
        long hashKey = hashFunction(key);
        indexBucket bucket;

        ifstream indexfile;
        indexfile.open(indexfilename, ios::in | ios::binary);
        indexfile.seekg(hashKey*sizeof(indexBucket));
        indexfile.read((char*)&bucket, sizeof(indexBucket));
        indexfile.close();

        cout << "BUCKET:" << bucket.size << "-" << bucket.next << "-" << bucket.indexes[bucket.size-1]->key << endl;

        /// Stratagy: swap the last element from de first bucket
        /// with the element to remove and do a size-- in this bucket
        /// case1: the element to remove is in the first bucket
        /// case2: the element to remove is in the first bucket & is the last element
        /// case3: the element to remove is not in the first bucket

        if (bucket.remove(key)) {
            fstream outfile;
            outfile.open(indexfilename, ios::out | ios::binary);
            outfile.seekp(hashKey*sizeof(indexBucket), ios::beg);
            outfile.write((char*)&bucket, sizeof(indexBucket));
            outfile.close();
        } else {
            // cogemos el next bucket

        }

        indexfile.close();
        /*
        ofstream outfile;
        // cout << "KEY: " << swap->key << "INDEX: " << swap->index << bucket.indexes[bucket.size-1]->index << " {:} " << "REAL KEY: " << key << endl;
        if (swap->key == key) {
            /// case2
            bucket.size = bucket.size-1;
            cout << "BUCKET:" << bucket.size << "-" << bucket.next << "-" << bucket.indexes[bucket.size-1]->key << endl;
            outfile.open(indexfilename, ios::binary);
            outfile.seekp(hashKey*sizeof(indexBucket));
            outfile.write((char*)&bucket, sizeof(indexBucket));
            outfile.close();

            // borrar
            indexBucket b;
            ifstream in;
            in.open(indexfilename, ios::in | ios::binary);
            in.seekg(bucket.next);
            in.read((char*)&b, sizeof(indexBucket));
            cout << "UPDATED BUCKET:" << b.size << "-" << b.next << "-" << b.indexes[b.size-1]->key << endl;
            return true;
        } else {
            cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
            /// case1
            for (int i=0; i<bucket.size-1; i++) {
                if (bucket.indexes[i]->key == key) {
                    bucket.indexes[i] = swap;
                    bucket.size--;

                    outfile.open(indexfilename, ios::binary);
                    outfile.seekp(hashKey*sizeof(indexBucket));
                    outfile.write((char*)&bucket, sizeof(indexBucket));
                    outfile.close();
                    return true;
                }
            }
            /// case2
            indexfile.open(indexfilename);
            indexBucket otherBucket;
            long n = bucket.next;
            do {
                indexfile.seekg(n);
                indexfile.read((char*)&otherBucket, sizeof(indexBucket));
                for (int i=0; i<otherBucket.size; i++) {
                    if (otherBucket.indexes[i]->key == key) {
                        otherBucket.indexes[i] = swap;
                        bucket.size--;

                        outfile.open(indexfilename, ios::binary);
                        outfile.seekp(hashKey*sizeof(indexBucket));
                        outfile.write((char*)&bucket, sizeof(indexBucket));
                        outfile.seekp(n);
                        outfile.write((char*)&otherBucket, sizeof(indexBucket));
                        outfile.close();
                        return true;
                    }
                }
                n = otherBucket.next;
            } while (n != -1);
        }

        indexfile.close();
        */
        return false;
    }

    vector<Record> rangeSearch(long beginkey, long endkey) {
        vector<Record> r;
        ifstream infile, datafile;
        infile.open(indexfilename, ios::in | ios::binary);
        datafile.open(datafilename, ios::in | ios::binary);
        for (auto i=0; i<MAX_SIZE_HASH; i++) {
            indexBucket curr;
            long n = i*sizeof(indexBucket);
            do {
                infile.seekg(n);
                infile.read((char*)&curr, sizeof(indexBucket));
                for (int j=0; j<curr.size; j++) {
                    long currkey = curr.indexes[j]->key;
                    if (currkey >= beginkey && currkey <= endkey) {
                        Record record;
                        datafile.seekg(curr.indexes[j]->index);
                        datafile.read((char*)&record, sizeof(Record));
                        r.push_back(record);
                    }
                }
                n = curr.next;
            } while (n != -1);
        }
        datafile.close();
        infile.close();
        return r;
    }

    void printHash() {
        ifstream infile;
        infile.open(indexfilename, ios::in | ios::binary);
        for (auto i=0; i<MAX_SIZE_HASH; i++) {
            cout << i << ": " << endl;
            indexBucket curr;
            long n = i*sizeof(indexBucket);
            do {
                cout << "\taddress: " << n;
                infile.seekg(n);
                infile.read((char*)&curr, sizeof(indexBucket));
                cout << "\tsize:" << curr.size << " {:} " << "NEXT: " << curr.next << endl;
                for (int j=0; j<curr.size; j++) {
                    cout << "\t" << curr.indexes[j]->key << " -> ";
                }
                cout << endl;
                n = curr.next;
            } while (n != -1);
        }
        infile.close();
    }

    void printLOQUESEA() {
        ifstream infile;
        infile.open(datafilename, ios::in | ios::binary);
        Record record;
        long i=0;
        while (i < recordCount) {
            infile.seekg((i++)*sizeof(Record));
            infile.read((char*)&record, sizeof(Record));
            cout << record.key << " - ";
        }
        infile.close();
    }

    void printIndexFile() {
        cout << "INDEXCOUNT: " << indexCount << endl;
        ifstream infile;
        infile.open(indexfilename, ios::in | ios::binary);
        indexBucket bucket;
        long i=0;
        while (i < indexCount) {
            infile.seekg((i++)*sizeof(indexBucket));
            infile.read((char*)&bucket, sizeof(indexBucket));
            cout << bucket.size << "{:}" << "ADDRESS: " << i*sizeof(indexBucket) << endl;
            for (int j=0; j<bucket.size; j++) {
                cout << bucket.indexes[j]->key << "-";
            }
            cout << endl;
        }
        infile.close();
    }

};

#endif //DB2_PROJECT_STATICHASH_H
