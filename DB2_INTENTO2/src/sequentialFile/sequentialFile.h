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
};

class Basket : public Record {
private:
    int key;    //id
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
};

class WorldPopulation : public Record {
private: 
    int key;   //year
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
        //auto infile = ;
    }
};


class sequentialFile {
public:
    string filename;
    size_t recordCount;

    sequentialFile(string filename) {
        this->filename = filename;
    }

    size_t count() 
    {
        ifstream infile;
        infile.open(filename);
        if (!infile) {
            cerr << "ERROR" << endl;
            exit(1);
        }
        string str;
        int s = -1;
        while (getline(infile, str, '\n'))
            s++;

        return s;
    }
};

template <typename T, typename Rec>
bool binarySearch(T key, sequentialFile seqFile, long &pos) {
    ifstream inFile;
    inFile.open(seqFile.filename);
    Rec record;
    long left = 0;
    long right = seqFile.recordCount - 1;
    long mid;
    while (right >= left) {
        mid = floor((left+right)/2);
        inFile.seekg(mid*sizeof(Rec));
        inFile.read((char*)&record, sizeof(record));
        if (key < record.key) {
            right = mid;
        } else if (key > record.key){
            left = mid;
        } else {
            return true;
        }
    }
    inFile.close();
    return false;
}


#endif //DB2_PROJECT_SEQUENTIALFILE_H
