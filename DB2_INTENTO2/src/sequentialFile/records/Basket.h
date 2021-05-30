#include "Record.h"

class Basket : public RecordSeq {
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
    Basket(){}
    
    Basket(long key, bool Apple, bool Bread, 
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

    void printData() override {
        cout << "ID: " << key << endl;
        cout << "Apple: " << Apple << endl;
        cout << "Bread: " << Bread << endl;
        /* cout << "Butter: " << Butter << endl;
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
        cout << "chocolate: " << chocolate << endl; */
        cout << "Next record (logic position): " << next << endl;
        cout << "--------------" << endl;
    }
};