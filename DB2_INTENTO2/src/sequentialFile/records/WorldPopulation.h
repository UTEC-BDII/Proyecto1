#include "Record.h"

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

    }

    void write() override{
        
    }

    void serialization(string object) override {

    }

    void printData() override {
        
    }
};