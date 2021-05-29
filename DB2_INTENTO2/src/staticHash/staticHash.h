//
// Created by Jorge on 21/05/2021.
//

#ifndef DB2_PROJECT_STATICHASH_H
#define DB2_PROJECT_STATICHASH_H

#include "../libs.h"

#define MAX_SIZE_BUCKET 10
#define MAX_SIZE_HASH 100

class Record {
protected:

    virtual void read() = 0;
    virtual void write() = 0;
    virtual void serialization(string object) = 0;
};

class Basket : public Record {
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
        // case 16:
        // after "for" ends
        // cout << att << ", ";
        chocolate = att == "True";
    }
};


struct indexElement{
    long index;     // en el datafile no en el index
    long key;
    indexElement(){}
    indexElement(long _index_, long _key_) : index(_index_), key(_key_){}
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
    string datfile;
    long recordCount;                        //
    long indexCount;
    // Bucket* buckets[MAX_SIZE_HASH];      // Array de punteros a buckets

public:
    staticHash(string name) : filename(name), recordCount(0), indexCount(0) {
        ifstream infile;
        ofstream outfile, indexoutfile;

        infile.open(filename.c_str());

        datfile = regex_replace(filename, regex("csv"), "dat");
        outfile.open(datfile, ios::out | ios::binary);

        indexfilename = "index.dat";
        indexoutfile.open(indexfilename, ios::out | ios::binary);

        if(!infile || !outfile || !indexoutfile) {
            cerr << "ERROR" << endl;
            exit(1);
        }

        indexBucket bucket{};
        for (int i=0; i<MAX_SIZE_HASH; i++)
            indexoutfile.write((char*)&bucket, sizeof(indexBucket));

        indexCount = MAX_SIZE_BUCKET;

        outfile.close();
        indexoutfile.close();

        size_t s = 0;
        string str;

        getline(infile, str, '\n');
        while (getline(infile, str, '\n')) {
            cout << s << "-";
            Record r;
            r.serialization(str);
            ++s;
            addToHash(r, r.key);
        }
        infile.close();
        recordCount = s;
        cout << "recordCount: " << recordCount << endl;
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

    void addToHash(Record record, long key) {
        long address = (++recordCount)*sizeof(record);

        ofstream outfile;
        outfile.open(datfile);
        outfile.write((char*)&record, sizeof(Record));
        outfile.close();

        int hashKey = hashFunction(key);
        indexBucket bucket;
        ifstream infile;
        infile.open(indexfilename);
        infile.seekg(hashKey*sizeof(indexBucket));
        infile.read((char*)&bucket, sizeof(indexBucket));
        infile.close();

        if ( bucket.size < MAX_SIZE_BUCKET ) {
            bucket.add(address, key);

            outfile.open(indexfilename);
            outfile.seekp(hashKey*sizeof(indexBucket));
            outfile.write((char*) &bucket, sizeof(indexBucket));
            outfile.close();
        } else {
            // Create a new bucket using LIFO
            Record newBucket, oldBucket;

            // Save the oldBucket to add it into the end of the file
            infile.open(indexfilename);
            infile.seekg(hashKey*sizeof(indexBucket));
            infile.read((char*)&oldBucket, sizeof(indexBucket));
            infile.close();

            outfile.open(indexfilename);
            outfile.seekp(hashKey*sizeof(indexBucket));
            outfile.write((char*)&newBucket, sizeof(indexBucket));
            outfile.seekp((++indexCount)*sizeof(indexBucket));
            outfile.write((char*)&oldBucket, sizeof(indexBucket));
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


    void printHash() {
        ifstream infile;
        infile.open(indexfilename);
        for (auto i=0; i<MAX_SIZE_HASH; i++) {
            cout << i << ": " << endl;
            indexBucket curr;
            infile.seekg(i*sizeof(indexCount));
            infile.read((char*)&curr, sizeof(indexBucket));
            while (curr.next != -1) {
                cout << "\tsize:" << curr.size << " {:} ";
                for (int j=0; j<curr.size; j++) {
                    cout << "\t" << curr.indexes[j]->key << " -> ";
                }
                cout << endl;
                infile.seekg(curr.next*sizeof(indexCount));
                infile.read((char*)&curr, sizeof(indexBucket));
            }
        }
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
