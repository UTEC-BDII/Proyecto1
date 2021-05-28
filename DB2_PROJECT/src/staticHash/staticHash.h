//
// Created by Jorge on 21/05/2021.
//

#ifndef DB2_PROJECT_EXTENDIBLEHASH_H
#define DB2_PROJECT_EXTENDIBLEHASH_H

#include "../libs.h"

#define MAX_SIZE_BUCKET 10
#define MAX_SIZE_HASH 100

class game;

struct Element{
    long index;
    string key;
    Element(){}
    Element(long _index_, string _key_){}
};

struct Bucket{
    Bucket* next;           // next
    Element* indexes[MAX_SIZE_BUCKET];      // indexes
    int size;               // actual size of the bucket

    explicit Bucket() : next(nullptr), size(0) {
        for (int i=0; i<MAX_SIZE_BUCKET; i++) {
            indexes[i] = new Element();
        }
    }

    void add(long newIndex, string newKey) {
        indexes[size]->index = newIndex;
        indexes[size]->key = newKey;
        size++;
    }
};


class extendibleHash {
private:
    Bucket* buckets[MAX_SIZE_HASH];       // Array de punteros a buckets

public:
    extendibleHash() {
        for (int i=0; i<MAX_SIZE_HASH; i++) {
            buckets[i] = new Bucket();
        }
    }

    int hashFunction(const string& id) {
        int value = 0;
        int exp = 1;
        for (auto letter : id) {
            value += letter * exp;
            exp *= 10;
        }
        return value % MAX_SIZE_HASH;
    }

    void addToHash(game* strct, const string& key) {
        long address;

        /*
         * Add to file & save the position in the hash table in "address"
         */

        address = 0;
        int hashKey = hashFunction(key);
        if ( buckets[hashKey]->size < MAX_SIZE_BUCKET ) {
            buckets[hashKey]->add(address, key);
        } else {
            // Create a new bucket using LIFO
            auto* newBucket = new Bucket();
            newBucket->next = buckets[hashKey];
            buckets[hashKey] = newBucket;

            // Adding the position in the hash table
            buckets[hashKey]->add(address, key);
        }
    }

    game* find(const string& key) {
        // Search in array
        game* strct;
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
        return nullptr;
    }

    void printHash() {
        for (auto i=0; i<MAX_SIZE_HASH; i++) {
            cout << i << ": " << endl;
            auto curr = buckets[i];
            while (curr != nullptr) {
                cout << "\tsize:" << curr->size << " {:} ";
                for (int j=0; j<curr->size; j++) {
                    cout << "\t" << curr->indexes[j]->key << " -> ";
                }
                cout << endl;
                curr = curr->next;
            }
        }
    }

};

// string::size_type sz;

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

    /*
    game(string object) {
        serialize(object);
    }
     */

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


#endif //DB2_PROJECT_EXTENDIBLEHASH_H
