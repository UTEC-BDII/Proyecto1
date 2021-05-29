
#ifndef DB2_PROJECT_SEQUENTIALFILE_H
#define DB2_PROJECT_SEQUENTIALFILE_H

#include "../libs.h"

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
    long next;
public:
    Basket(){}

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
                switch (i) {
                    case 0:
                        key = stol(att);
                        break;
                    case 1:
                        Apple = att == "True";
                        break;
                    case 2:
                        Bread = att == "True";
                        break;
                    case 3:
                        Butter = att == "True";
                        break;
                    case 4:
                        Cheese = att == "True";
                        break;
                    case 5:
                        Corn = att == "True";
                        break;
                    case 6:
                        Dill = att == "True";
                        break;
                    case 7:
                        Eggs = att == "True";
                        break;
                    case 8:
                        Ice_cream = att == "True";
                        break;
                    case 9:
                        Kidney_Beans = att == "True";
                        break;
                    case 10:
                        Milk = att == "True";
                        break;
                    case 11:
                        Nutmeg = att == "True";
                        break;
                    case 12:
                        Onion = att == "True";
                        break;
                    case 13:
                        Sugar = att == "True";
                        break;
                    case 14:
                        Unicorn = att == "True";
                        break;
                    case 15:
                        Yogurt = att == "True";
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

class WorldPopulation : public Record {
public:
    long key;   //year
    long Population;
    float ChangePerc;
    long NetChange;
    int Density;
    long Urban;
    int UrbanPerc;
    long next;
public:
    WorldPopulation(){}

    void read() override{
        /*
        ifstream inFile;
        inFile.open(file);
	    Alumno a;
        inFile.seekg(pos*(sizeof(Alumno)+2));
        inFile >> a;
        inFile.close();
        return a;
        */
    }

    void write() override{
        
    }

    void serialization(string object) override {

    }
};

template<typename T, typename Rec>
class sequentialFile {
private:
    string filename;
    size_t recordCount;
    string datfile;
    int auxFactor;

public:
    sequentialFile(string filename, int auxFactor);
    void createBinaryFile();
    size_t countRecords();
    void add(Rec record); //TODO
    void remove(T key); //TODO
    Rec search(T key); //TODO
    vector<Rec> rangeSearch(T beginkey, T endkey);
    void reconstruct();

    template <typename T1, typename Rec1>
    friend bool binarySearch(T1 key, sequentialFile<T1, Rec1>* seqFile, long &pos);
};

template <typename T, typename Rec>
bool binarySearch(T key, sequentialFile<T, Rec>* seqFile, long &pos);

/* template <typename T, typename Rec>
Rec rangeEqual(T key, sequentialFile<T, Rec> seqFile) {
    Rec record;
    long pos;
    binarySearch(key, seqFile, pos);
    ifstream inFile;
    inFile.open(seqFile.datfile);
    inFile.seekg(pos*sizeof(Rec));
    inFile.read((char*)&record, sizeof(record));
    inFile.close();
    return record;
} */

#endif //DB2_PROJECT_SEQUENTIALFILE_H
