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
};

/*
struct Bucket{
    long next2;                             // ubicacion del sgt bucket
    Bucket* next;                           // next
    indexElement* indexes[MAX_SIZE_BUCKET]; // indexes
    int size;                               // actual size of the bucket

    explicit Bucket() : next(nullptr), size(0) {
        for (int i=0; i<MAX_SIZE_BUCKET; i++) {
            indexes[i] = new indexElement();
        }
    }

    void add(long newIndex, long newKey) {
        indexes[size]->index = newIndex;
        indexes[size]->key = newKey;
        size++;
    }
};
 */

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
                indexoutfile.write((char*) &nbucket, sizeof(indexBucket));
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
        /*
        int value = 0;
        int exp = 1;
        for (auto letter : id) {
            value += letter * exp;
            exp *= 10;
        }
         */
        return id % MAX_SIZE_HASH;
    }

    void addToFile(Record record) {
        ofstream outfile;
        outfile.open(datafilename);
        outfile.write((char*)&record, sizeof(Record));
        outfile.close();
        ++recordCount;
    }

    void addToHash(Record record) {
        long address = recordCount*sizeof(record);

        ofstream outfile;
        outfile.open(datafilename, ios::out | ios::binary);
        // outfile.seekp(0, ios::end);
        outfile.write((char*)&record, sizeof(Record));
        outfile.close();

        long hashKey = hashFunction(record.key);
        indexBucket bucket;
        ifstream infile;
        infile.open(indexfilename, ios::in | ios::binary);
        infile.seekg(hashKey*sizeof(indexBucket));
        infile.read((char*)&bucket, sizeof(indexBucket));
        infile.close();

        //cout << endl << "address: " << address;
        //cout << endl << "(" << bucket.size << ")(" << bucket.next << ")";

        if ( bucket.size < MAX_SIZE_BUCKET ) {
            bucket.add(address, record.key);
            //cout << endl << "[" << bucket.size << "]" << endl;

            outfile.open(indexfilename, ios::binary);
            outfile.seekp(hashKey*sizeof(indexBucket));
            outfile.write((char*) &bucket, sizeof(indexBucket));
            outfile.close();
            /*
            indexBucket n;
            infile.open(indexfilename, ios::in | ios::binary);
            infile.seekg(hashKey*sizeof(indexBucket));
            infile.read((char*)&n, sizeof(indexBucket));
            cout << "[" << n.size << "]" << endl;
            infile.close();
             */
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
    /*
    bool find(const string& key, Record r) {
        // Search in array
        Record record;
        int hashKey = hashFunction(key);
        Bucket* it = buckets[hashKey];

        // For all the buckets connected
        while ( it != nullptr ) {
            auto elements = it->indexes;
            // For all the elements in a bucket
            for ( int i=0; i<it->size; i++ ) {
                if ( elements[i]->key == key ) {
                    // Se supone que aquí lees el archivo, guardas en "strct" y retornas

                    break;
                }
            }
            it = it->next;
        }
        return true;
    }
     */

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

    void remove(long key, Record& record) {
        // Podría crear un array que tenga posiciones eliminadas y
        // que al momento de insertar vea si este array tiene un
        // elemento para tomar esa posicion e insertar en el datafile
        // en esa posicion
        long hashkey = hashFunction(key);
        indexBucket bucket;

        ifstream indexfile;
        indexfile.open(indexfilename);

        indexfile.seekg(hashkey*sizeof(indexBucket));
        indexfile.read((char*)&bucket, sizeof(indexBucket));

        /// Stratagy:

        indexfile.close();
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
            for (int i=0; i<bucket.size; i++) {
                cout << "index: " << bucket.indexes[i]->key << "-";
            }
            cout << endl;
        }
        infile.close();
    }
};




// string::size_type sz;
/*
class game{
private:
    string id;

    bool rated;
    double created_at;
    double last_move_at;
    int turns;

    string victory_status;
    string winner;
    string increment_code;

    string white_id;
    int white_rating;
    string black_id;
    int black_rating;

    string moves;
    string opening_eco;
    string opening_name;
    int opening_ply;

    double expToDouble(string s) {
        string str;
        int i=0;
        char x = s[i];

        while (x != 'E') {
            str.push_back(x);
            x = s[++i];
        }

        i = s.size()-1;
        x = s[i];
        int digito = 0;
        int e = 1;
        while (x != '+') {
            int c = x - '0';
            digito = digito + c*e;
            e *= 10;
            x = s[--i];
        }

        double d = stod(str) * pow(10, digito);
        return d;
    }
public:
    explicit game() {}

    void serialize(string object) {
        int i=0;
        string att;
        for (char letter : object) {
            if (letter != ',') {
                //att += letter;
                att.push_back(letter);
            } else {
                switch (i) {
                    case 0:
                        id = att;
                        break;
                    case 1:
                        // cout << att << ", ";
                        rated = att == "TRUE";
                        break;
                    case 2:
                        // cout << att << ", ";
                        created_at = expToDouble(att);
                        break;
                    case 3:
                        // cout << att << ", ";
                        last_move_at = expToDouble(att);
                        break;
                    case 4:
                        // cout << att << ", ";
                        turns = stoi(att);
                        break;
                    case 5:
                        // cout << att << ", ";
                        victory_status = att;
                        break;
                    case 6:
                        // cout << att << ", ";
                        winner = att;
                        break;
                    case 7:
                        // cout << att << ", ";
                        increment_code = att;
                        break;
                    case 8:
                        // cout << att << ", ";
                        white_id = att;
                        break;
                    case 9:
                        // cout << att << ", ";
                        white_rating = stoi(att);
                        break;
                    case 10:
                        // cout << att << ", ";
                        black_id = att;
                        break;
                    case 11:
                        // cout << att << ", ";
                        black_rating = stoi(att);
                        break;
                    case 12:
                        // cout << att << ", ";
                        moves = att;
                        break;
                    case 13:
                        // cout << att << ", ";
                        opening_eco = att;
                        break;
                    case 14:
                        // cout << att << ", ";
                        opening_name = att;
                        break;
                    default:
                        cerr << "Error in serializing\n";
                        break;
                }
                i++;
                att.clear();
            }
        }
        // case 15:
        // after "for" ends
        // cout << att << ", ";
        opening_ply = stoi(att);
    }

    string getKey() {
        return id;
    }
};
*/

#endif //DB2_PROJECT_STATICHASH_H
