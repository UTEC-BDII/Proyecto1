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
    virtual void serialization(string object) = 0;
    virtual void printData() = 0;
    virtual void input() = 0;
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
    BasketHash(){}

    BasketHash(long key, bool Apple, bool Bread, 
            bool Butter, bool Cheese, bool Corn, 
            bool Dill, bool Eggs, bool Ice_cream, 
            bool Kidney_Beans, bool Milk, bool Nutmeg, 
            bool Onion, bool Sugar, bool Unicorn, 
            bool Yogurt, bool chocolate) {
        this->key = key;
        this->Apple = Apple;
        this->Bread = Bread;
        this->Butter = Butter;
        this->Cheese = Cheese;
        this->Corn = Corn;
        this->Dill = Dill;
        this->Eggs = Eggs;
        this->Ice_cream = Ice_cream;
        this->Kidney_Beans = Kidney_Beans;
        this->Milk = Milk;
        this->Nutmeg = Nutmeg;
        this->Onion = Onion;
        this->Sugar = Sugar;
        this->Unicorn = Unicorn;
        this->Yogurt = Yogurt;
        this->chocolate = chocolate;
    }

    // Constructor for testing
    BasketHash(long key) {
        this->key = key;
        this->Apple = 1;
        this->Bread = 1;
        this->Butter = 1;
        this->Cheese = 1;
        this->Corn = 1;
        this->Dill = 1;
        this->Eggs = 1;
        this->Ice_cream = 1;
        this->Kidney_Beans = 1;
        this->Milk = 1;
        this->Nutmeg = 1;
        this->Onion = 1;
        this->Sugar = 1;
        this->Unicorn = 1;
        this->Yogurt = 1;
        this->chocolate = 1;
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

    void printData() override {
        cout << "ID: " << key << endl;
        cout << "Apple: " << Apple << endl;
        cout << "Bread: " << Bread << endl;
        cout << "Butter: " << Butter << endl;
        cout << "Cheese: " << Cheese << endl;
        cout << "Corn: " << Corn << endl;
        cout << "Dill: " << Dill << endl;
        cout << "Eggs: " << Eggs << endl;
        cout << "Ice_cream: " << Ice_cream << endl;
        cout << "Kidney_Beans: " << Kidney_Beans << endl;
        cout << "Milk: " << Milk << endl;
        cout << "Nutmeg: " << Nutmeg << endl;
        cout << "Onion: " << Onion << endl;
        cout << "Sugar: " << Sugar << endl;
        cout << "Unicorn: " << Unicorn << endl;
        cout << "Yogurt: " << Yogurt << endl;
        cout << "chocolate: " << chocolate << endl;
        cout << "--------------\n";
    }

    void input() override {
        cout << "ID (key): "; cin >> key;
        cout << "Apple: "; cin >> Apple;
        cout << "Bread: "; cin >> Bread;
        cout << "Butter: "; cin >> Butter;
        cout << "Cheese: "; cin >> Cheese;
        cout << "Corn: "; cin >> Corn;
        cout << "Dill: "; cin >> Dill;
        cout << "Eggs: "; cin >> Eggs;
        cout << "Ice_cream: "; cin >> Ice_cream;
        cout << "Kidney_Beans: "; cin >> Kidney_Beans;
        cout << "Milk: "; cin >> Milk;
        cout << "Nutmeg: "; cin >> Nutmeg;
        cout << "Onion: "; cin >> Onion;
        cout << "Sugar: "; cin >> Sugar;
        cout << "Unicorn: "; cin >> Unicorn;
        cout << "Yogurt: "; cin >> Yogurt;
        cout << "chocolate: "; cin >> chocolate;
    }
};

class WorldPopulationHash : public RecordHash {
public:
    long key;   //year
    long long Population;
    float ChangePerc;
    long long NetChange;
    int Density;
    long long Urban;
    int UrbanPerc;
public:
    WorldPopulationHash(){}

    WorldPopulationHash(long key, long long Population, float ChangePerc, 
                    long long NetChange, int Density, long long Urban, int UrbanPerc) {
        this->key = key;
        this->Population = Population;
        this->ChangePerc = ChangePerc;
        this->NetChange = NetChange;
        this->Density = Density;
        this->Urban = Urban;
        this->UrbanPerc = UrbanPerc;
    }

    // Constructor for testing
    WorldPopulationHash(long key) {
        this->key = key;
        this->Population = 100;
        this->ChangePerc = 100;
        this->NetChange = 100;
        this->Density = 100;
        this->Urban = 100;
        this->UrbanPerc = 100;
    }

    void serialization(string object) override {
        int i=0;
        string att;
        for (char letter : object) {
            if (letter != ',') {
                att.push_back(letter);
            } else {
                switch (i) {
                    case 0:
                        key = stol(att);
                        break;
                    case 1:
                        Population = stoll(att);
                        break;
                    case 2:
                        ChangePerc = stof(att);
                        break;
                    case 3:
                        NetChange = stoll(att);
                        break;
                    case 4:
                        Density = stoi(att);
                        break;
                    case 5:
                        Urban = stoll(att);
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
        UrbanPerc = stoi(att);
    }

    void printData(){
        cout << "Year: " << key << endl;
        cout << "Population: " << Population << endl;
        cout << "ChangePerc: " << ChangePerc << endl;
        cout << "NetChange: " << NetChange << endl;
        cout << "Density: " << Density << endl;
        cout << "Urban: " << Urban << endl;
        cout << "UrbanPerc: " << UrbanPerc << endl;
        cout << "--------------\n";
    }

    void input() override {
        cout << "Year (key): "; cin >> key;
        cout << "Population: "; cin >> Population;
        cout << "ChangePerc: "; cin >> ChangePerc;
        cout << "NetChange: "; cin >> NetChange;
        cout << "Density: "; cin >> Density;
        cout << "Urban: "; cin >> Urban;
        cout << "UrbanPerc: "; cin >> UrbanPerc;
    }
};

struct indexElement{
    long index;     // en el datafile no en el index
    long key;
    indexElement(){}
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
                auto temp = indexes[i];
                indexes[i] = indexes[size-1];
                indexes[size-1] = temp;
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

public:
    staticHash(){}
    staticHash(string name) : filename(name), recordCount(0), indexCount(0) {
        ifstream infile, indexinfile;
        ofstream outfile, indexoutfile;

        size_t position = filename.find(".");
        string extractName = (string::npos == position)? filename : filename.substr(0, position);
        string newFile = extractName + "_hash.csv";
        datafilename = regex_replace(newFile, regex("csv"), "dat");
        indexfilename = "index.dat";

        infile.open(filename.c_str());
        indexinfile.open(indexfilename, ios::in | ios::binary);
        outfile.open(datafilename, ios::out | ios::binary);
        indexoutfile.open(indexfilename, ios::binary);

        if(!infile || !outfile || !indexoutfile || !indexinfile) {
            cerr << "ERROR" << endl;
            exit(1);
        }

        indexBucket bucket{};
        for (int i=0; i<MAX_SIZE_HASH; i++)
            indexoutfile.write((char*)&bucket, sizeof(indexBucket));

        indexCount = MAX_SIZE_HASH;

        string str;

        getline(infile, str, '\n');
        while (getline(infile, str, '\n')) {
            Record r;
            r.serialization(str);

            /// write in file.dat
            outfile.write((char*)&r, sizeof(r));

            long address = (recordCount++)*sizeof(Record);
            long hashKey = hashFunction(r.key);

            indexinfile.seekg(hashKey*sizeof(indexBucket));
            indexinfile.read((char*)&bucket, sizeof(indexBucket));
            if ( bucket.size < MAX_SIZE_BUCKET ) {
                bucket.add(address, r.key);
                indexoutfile.seekp(hashKey*sizeof(indexBucket));
                indexoutfile.write((char*)&bucket, sizeof(indexBucket));
            } else {
                indexBucket newBucket;

                newBucket.add(address, r.key);
                newBucket.next = (indexCount++)*sizeof(indexBucket);

                indexoutfile.seekp(hashKey*sizeof(indexBucket));
                indexoutfile.write((char*)&newBucket, sizeof(indexBucket));

                indexoutfile.seekp((indexCount-1)*sizeof(indexBucket));
                indexoutfile.write((char*)&bucket, sizeof(indexBucket));
            }
        }
        indexoutfile.close();
        indexinfile.close();

        outfile.close();
        infile.close();
    }

    long hashFunction(const long& id) {
        return id % MAX_SIZE_HASH;
    }

    void addToHash(Record record) {
        long address = recordCount*sizeof(record);

        /// Write in the data file
        ofstream outfile;
        outfile.open(datafilename, ios::app | ios::binary);
        outfile.write((char*)&record, sizeof(Record));
        outfile.close();

        /// Take the bucket in the index file
        long hashKey = hashFunction(record.key);
        indexBucket bucket;
        ifstream infile;
        infile.open(indexfilename, ios::in | ios::binary);
        infile.seekg(hashKey*sizeof(indexBucket));
        infile.read((char*)&bucket, sizeof(indexBucket));
        infile.close();

        fstream indexoutfile;
        indexoutfile.open(indexfilename, ios::in | ios::out | ios::binary);
        if ( bucket.size < MAX_SIZE_BUCKET ) {
            if ( !indexoutfile ) {
                cerr << "ERROR";
                exit(1);
            }
            bucket.add(address, record.key);
            indexoutfile.seekp(hashKey*sizeof(indexBucket));
            indexoutfile.write((char*)&bucket, sizeof(indexBucket));
            indexoutfile.close();

        } else {
            /// Create a new bucket using LIFO
            indexBucket newBucket;

            /// Add the new index in a new empty bucket
            newBucket.add(address, record.key);
            newBucket.next = (indexCount++)*sizeof(indexBucket);

            /// write the new bucket in old bucket's position
            indexoutfile.seekp(hashKey*sizeof(indexBucket));
            indexoutfile.write((char*)&newBucket, sizeof(indexBucket));

            /// Save the old bucket to add it into the end of the file
            indexoutfile.seekp((indexCount-1)*sizeof(indexBucket));
            indexoutfile.write((char*)&bucket, sizeof(indexBucket));
            indexoutfile.close();
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

        if (indexfile.is_open())
            indexfile.close();
        return false;
    }

    /// Stratagy to remove: swap the last element from de first bucket
    /// with the element to remove and do a size-- in this bucket
    /// See the next cases:
    /// case1: the element to remove is in the first bucket
    /// case2: the element to remove is in the first bucket & is the last element
    /// case3: the element to remove is not in the first bucket

    bool remove(long key, Record& record) {
        long hashKey = hashFunction(key);
        long savedPosition;
        indexBucket bucket;

        ifstream indexfile, read;
        indexfile.open(indexfilename, ios::in | ios::binary);
        indexfile.seekg(hashKey*sizeof(indexBucket));
        indexfile.read((char*)&bucket, sizeof(indexBucket));
        indexfile.close();

        /// need a bucket with a size > 0
        if ( bucket.size == 0 && bucket.next == -1 ) {
            return false;
        } else if ( bucket.size == 0 ) {
            indexfile.open(indexfilename, ios::in | ios::binary);
            while (bucket.size == 0 && hashKey != -1) {
                // To write in that position
                hashKey = bucket.next / sizeof(indexBucket);
                indexfile.seekg(hashKey * sizeof(indexBucket));
                indexfile.read((char*)&bucket, sizeof(indexBucket));
            }
            indexfile.close();
        }

        fstream outfile;
        outfile.open(indexfilename, ios::in | ios::out | ios::binary);
        read.open(datafilename, ios::in | ios::binary);
        if ( bucket.remove(key) ) {
            /// Write the changes if the element is in this bucket
            outfile.seekp(hashKey*sizeof(indexBucket), ios::beg);
            outfile.write((char*)&bucket, sizeof(indexBucket));
            outfile.close();

            /// Save the removed element (we are sure that element is in that position)
            savedPosition = bucket.indexes[bucket.size]->index;
            read.seekg(savedPosition);
            read.read((char*)&record, sizeof(Record));
            read.close();
            return true;
        } else if ( bucket.next != -1 ) {
            /// Save the next position
            long newNext = bucket.next;
            indexBucket otherBucket;
            indexElement* swap = bucket.indexes[bucket.size-1];
            indexfile.open(indexfilename, ios::in | ios::binary);
            do {
                indexfile.seekg(newNext);
                indexfile.read((char*)&otherBucket, sizeof(indexBucket));
                for ( int i=0; i<otherBucket.size; i++ ) {
                    if ( otherBucket.indexes[i]->key == key ) {
                        /// Save the element to remove
                        savedPosition = otherBucket.indexes[i]->index;
                        read.seekg(savedPosition);
                        read.read((char*)&record, sizeof(Record));
                        read.close();

                        /// Overwrite the element
                        otherBucket.indexes[i] = swap;
                        bucket.size--;

                        /// Save the changes
                        outfile.seekp(hashKey*sizeof(indexBucket));
                        outfile.write((char*)&bucket, sizeof(indexBucket));

                        outfile.seekp(newNext);
                        outfile.write((char*)&otherBucket, sizeof(indexBucket));

                        indexfile.close();
                        outfile.close();
                        return true;
                    }
                }
                newNext = otherBucket.next;
            } while ( newNext != -1 );

        }

        if (indexfile.is_open())
            indexfile.close();
        if (outfile.is_open())
            outfile.close();
        return false;
    }

    vector<Record> rangeSearch(long beginkey, long endkey) {
        vector<Record> r;
        ifstream infile, datafile;
        infile.open(indexfilename, ios::in | ios::binary);
        datafile.open(datafilename, ios::in | ios::binary);
        for ( auto i=0; i<MAX_SIZE_HASH; i++ ) {
            indexBucket curr;
            long n = i*sizeof(indexBucket);
            do {
                infile.seekg(n);
                infile.read((char*)&curr, sizeof(indexBucket));
                for ( int j=0; j<curr.size; j++ ) {
                    long currkey = curr.indexes[j]->key;
                    if ( currkey >= beginkey && currkey <= endkey ) {
                        Record record;
                        datafile.seekg(curr.indexes[j]->index);
                        datafile.read((char*)&record, sizeof(Record));
                        r.push_back(record);
                    }
                }
                n = curr.next;
            } while ( n != -1 );
        }
        if ( datafile.is_open() )
            datafile.close();
        if ( infile.is_open() )
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
        cout << "\nINDEXCOUNT: " << indexCount << endl;
        ifstream infile;
        infile.open(indexfilename, ios::in | ios::binary);
        indexBucket bucket;
        long i=0;

        ifstream inFile;
        inFile.open(indexfilename, ios::binary);
        inFile.seekg(0, inFile.end);
        size_t size = inFile.tellg();
        inFile.close();
        long s = size/sizeof(indexBucket);

        while (i < s) {
            infile.seekg((i++)*sizeof(indexBucket));
            infile.read((char*)&bucket, sizeof(indexBucket));
            cout << bucket.size << "{:}" << "ADDRESS: " << i*sizeof(indexBucket) << endl;
            for (int j=0; j<bucket.size; j++) {
                cout << bucket.indexes[j]->key << "-";
            }
            cout << endl << endl;
        }
        infile.close();
    }

};

#endif //DB2_PROJECT_STATICHASH_H