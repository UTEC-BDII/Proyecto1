
#include "sequentialFile.h"

template <typename T, typename Rec>
sequentialFile<T, Rec>::sequentialFile(string filename, int auxFactor) {
    this->filename = filename;
    this->auxFactor = auxFactor;
    createBinaryFile();
    this->recordCount = countRecords();
}

template <typename T, typename Rec>
void sequentialFile<T, Rec>::createBinaryFile() {
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
        exit(1);
    }

    getline(infile, str, '\n');
    Rec r;
    while (getline(infile, str, '\n')) {
        // cout << "str:" << str;
        r.serialization(str);
        r.next = (++s)*sizeof(r);
        outfile.write((char*) &r, sizeof(r));
    }
    r.next = -1;
    outfile.seekp((s)*sizeof(r));
    outfile.write((char*) &r, sizeof(r));

    outfile.close();
    infile.close();
}

template <typename T, typename Rec>
size_t sequentialFile<T, Rec>::countRecords() {
    ifstream inFile;
    inFile.open(datfile);
    inFile.seekg(0, inFile.end);
    size_t size = inFile.tellg();
    inFile.close();
    return size/sizeof(Rec);
}

template <typename T, typename Rec>
void sequentialFile<T, Rec>::add(Rec record) {
    ifstream inFile;
    inFile.open(datfile);
}

template <typename T, typename Rec>
void sequentialFile<T, Rec>::remove(T key) {
    Rec toRemove;
    long i;
    binarySearch(key, this, i);
    ifstream inFile;
    inFile.seekg(i*sizeof(Rec));
}

template <typename T, typename Rec>
Rec sequentialFile<T, Rec>::search(T key) {
    ifstream inFile;
    inFile.open(datfile);
    Rec record;
    return record;
}

template <typename T, typename Rec>
vector<Rec> sequentialFile<T, Rec>::rangeSearch(T beginkey, T endkey) {
    vector<Rec> v;
    ifstream inFile;
    inFile.open(datfile);
    Rec record;
    long beginpos;
    binarySearch(beginkey, this, beginpos);
    inFile.seekg(beginpos*sizeof(Rec));
    inFile.read((char*)&record, sizeof(record));
    v.push_back(record);

    T currentkey = record.key;
    while(currentkey < endkey && record.next != -1) {
        inFile.seekg(++beginpos * sizeof(Rec));
        inFile.read((char *) &record, sizeof(record));
        v.push_back(record);
        currentkey = record.key;
    }
    inFile.close();

    return v;
}

template <typename T, typename Rec>
bool binarySearch(T key, sequentialFile<T, Rec>* seqFile, long &pos) {
    ifstream inFile;
    inFile.open(seqFile->datfile);
    Rec record;
    long left = 0;
    long right = seqFile->recordCount - 1;
    long mid;
    //cout << "right:" << right << " - " << "left:" << left << "mid:" << mid;
    //cout << endl;
    while (right >= left) {
        mid = floor((left+right)/2);
        inFile.seekg(mid*sizeof(Rec));
        inFile.read((char*)&record, sizeof(record));
        if (key < record.key) {
            right = mid - 1;
        } else if (key > record.key){
            left = mid + 1;
        } else {
            //cout << "mid: " << mid << endl;
            pos = mid;
            return true;
        }
        //cout << "right:" << right << " - " << "left:" << left << "mid:" << mid << "key:" << record.key <<"\n";
        if (left == right)
            break;
    }
    inFile.close();
    pos = right;
    return false;
}

template <typename T, typename Rec>
void sequentialFile<T, Rec>::reconstruct() {

}