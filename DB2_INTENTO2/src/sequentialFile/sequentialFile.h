//
// Created by Jorge on 21/05/2021.
//

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
                //att += letter;
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
public:
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
    
    WorldPopulation()
    {
        
    }

    void serialization(string object) override {

    }
};

template<typename Record>
class sequentialFile {
public:
    string filename;
    size_t recordCount;
    string datfile;

    sequentialFile(string filename) {
        this->filename = filename;
        recordCount = count();
    }

    size_t count() 
    {
        ifstream infile;
        ofstream outfile;
        
        infile.open(filename.c_str());
        if (!infile) {
            cerr << "ERROR" << endl;
            exit(1);
        }
        size_t s = -1;

        string str;
        datfile = regex_replace(filename, regex("csv"), "dat");

        outfile.open(datfile, ios::out | ios::binary);

        if(!outfile) {
            cerr << "ERROR" << endl;
        }

        getline(infile, str, '\n');
        while (getline(infile, str, '\n')) {
            // cout << "str:" << str;
            Record r;
            r.serialization(str);
            outfile.write((char*) &r, sizeof(r));
            s++; 
        }
        outfile.close();
        infile.close();
        return s;
    }
};

template <typename T, typename Rec>
bool binarySearch(T key, sequentialFile<Rec> seqFile, long &pos) {
    ifstream inFile;
    inFile.open(seqFile.datfile);
    Rec record;
    long left = 0;
    long right = seqFile.recordCount - 1;
    long mid;
    cout << "right:" << right << " - " << "left:" << left << "mid:" << mid << "\n";
    cout << endl;
    while (right >= left) {
        mid = floor((left+right)/2);
        inFile.seekg(mid*sizeof(Rec));
        inFile.read((char*)&record, sizeof(record));
        if (key < record.key) {
            right = mid;
        } else if (key > record.key){
            left = mid;
        } else {
            cout << "mid: " << mid << endl;
            pos = mid;
            return true;
        }
        cout << "right:" << right << " - " << "left:" << left << "mid:" << mid << "key:" << record.key <<"\n";
        if (left == right)
            break;
    }
    inFile.close();
    pos = -1;
    return false;
}

template <typename T, typename Rec>
vector<Rec> rangeSearch(T beginkey, T endkey, sequentialFile<Rec> seqFile) {
    vector<Rec> v;
    ifstream inFile;
    inFile.open(seqFile.datfile);
    Rec record;
    long beginpos;
    binarySearch(beginkey, seqFile, beginpos);
    inFile.seekg(beginpos*sizeof(Rec));
    inFile.read((char*)&record, sizeof(record));
    v.push_back(record);

    T currentkey = record.key;
    while(currentkey != endkey) {
        inFile.seekg(++beginpos * sizeof(Rec));
        inFile.read((char *) &record, sizeof(record));
        v.push_back(record);
        currentkey = record.key;
    }
    inFile.close();

    return v;
}

template <typename T, typename Rec>
bool remove(T key, sequentialFile<Rec> seqFile) {
    Rec toRemove;
    long i;
    binarySearch(key, seqFile, i);
    ifstream inFile;
    inFile.seekg(i*sizeof(Rec));
    
    return true;
}

#endif //DB2_PROJECT_SEQUENTIALFILE_H
