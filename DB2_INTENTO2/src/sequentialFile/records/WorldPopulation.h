#include "Record.h"

class WorldPopulation : public RecordSeq {
public:
    long key;   //year
    long Population;
    float ChangePerc;
    long NetChange;
    int Density;
    long Urban;
    int UrbanPerc;
public:
    WorldPopulation(){}

    void serialization(string object) override {

    }

    void printData() override {
        
    }
};