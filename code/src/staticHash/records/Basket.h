#include "Record.h"

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