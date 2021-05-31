#include "Record.h"

class WorldPopulationSeq : public RecordSeq {
public:
    long key;   //year
    long Population;
    float ChangePerc;
    long NetChange;
    int Density;
    long Urban;
    int UrbanPerc;
public:
    WorldPopulationSeq(){}

    WorldPopulationSeq(long key, long Population, float ChangePerc, 
                    long NetChange, int Density, long Urban, int UrbanPerc) {
        this->key = key;
        this->Population = Population;
        this->ChangePerc = ChangePerc;
        this->NetChange = NetChange;
        this->Density = Density;
        this->Urban = Urban;
        this->UrbanPerc = UrbanPerc;
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
                        Population = stol(att);
                        break;
                    case 2:
                        ChangePerc = stof(att);
                        break;
                    case 3:
                        NetChange = stol(att);
                        break;
                    case 4:
                        Density = stoi(att);
                        break;
                    case 5:
                        Urban = stol(att);
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

    void printData() override {
        cout << "Year: " << key << endl;
        cout << "Population: " << Population << endl;
        cout << "ChangePerc: " << ChangePerc << endl;
        cout << "NetChange: " << NetChange << endl;
        cout << "Density: " << Density << endl;
        cout << "Urban: " << Urban << endl;
        cout << "UrbanPerc: " << UrbanPerc << endl;
        cout << "Next record (logic position): " << next << endl;
        cout << "--------------\n";
    }
};