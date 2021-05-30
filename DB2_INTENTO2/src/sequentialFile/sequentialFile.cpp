
#include "sequentialFile.h"

template <typename T, typename Rec>
sequentialFile<T, Rec>::sequentialFile(string filename, size_t auxFactor) {
    this->filename = filename;
    this->auxFactor = auxFactor;
    createBinaryFile();
    this->validRecords = countRecords();
    this->auxRecords = 0;
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
    long s = 0;

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
        r.serialization(str);
        r.next = (++s);
        outfile.write((char*) &r, sizeof(Rec));
    }
    
    r.next = -1;
    outfile.seekp((--s)*sizeof(Rec));
    outfile.write((char*) &r, sizeof(Rec));

    outfile.close();
    infile.close();
}

template <typename T, typename Rec>
size_t sequentialFile<T, Rec>::countRecords() {
    ifstream inFile;
    inFile.open(datfile, ios::binary);
    inFile.seekg(0, inFile.end);
    size_t size = inFile.tellg();
    inFile.close();
    return size/sizeof(Rec);
}

template <typename T, typename Rec>
void sequentialFile<T, Rec>::add(Rec record) {
    if (auxRecords >= auxFactor) reconstruct();

    fstream fs;
    fs.open(datfile, ios::binary | ios::out | ios::in);
    long pos;
    binarySearch(record.key, this, pos);

    Rec prevRecord;
    fs.seekg(pos*sizeof(Rec));
    fs.read((char*)&prevRecord, sizeof(Rec));
    record.next = prevRecord.next;
    prevRecord.next = validRecords + auxRecords;

    fs.seekp(0, fs.end);
    fs.write((char*) &record, sizeof(Rec));
    fs.seekp(pos*sizeof(Rec));
    fs.write((char*) &prevRecord, sizeof(Rec));

    auxRecords++;
}

template <typename T, typename Rec>
void sequentialFile<T, Rec>::reconstruct() {
    string reconstructFile = "reconstruct.dat";
    ifstream inFile(datfile, ios::binary);
    ofstream outFile(reconstructFile, ios::binary);
    Rec record;
    long next;
    long cont = 1;

    inFile.seekg(0);
    inFile.read((char *) &record, sizeof(Rec));
    next = record.next;
    record.next = cont++;
    outFile.seekp(0);
    outFile.write((char *) &record, sizeof(Rec));

    while (next != -1) {
        inFile.seekg(next*sizeof(Rec));
        inFile.read((char *) &record, sizeof(Rec));
        next = record.next;
        if (next != -1) record.next = cont++;
        outFile.write((char *) &record, sizeof(Rec));

        vector<Rec> auxRec;
        vector<long> auxNext;
        while (next >= validRecords && next != -1) {
            inFile.seekg(next*sizeof(Rec));
            inFile.read((char*)&record, sizeof(Rec));
            next = record.next;
            auxRec.push_back(record);
            auxNext.push_back(record.next);
        }

        sort(auxRec.begin(), auxRec.end(), [](Rec &r1, Rec &r2){return r1.key < r2.key;});
        for (size_t i = 0; i < auxRec.size(); i++) {
            auxRec[i].next = auxNext[i];
            if (auxRec[i].next != -1) auxRec[i].next = cont++;
            outFile.write((char *) &auxRec[i], sizeof(Rec));
        }
    }
    
    inFile.close();
    outFile.close();
    //if (std::remove(datfile.c_str())) cout << "removed " << datfile << endl;
    //rename(reconstructFile.c_str(), datfile.c_str());
    
    datfile = reconstructFile;
    validRecords = countRecords();
    auxRecords = 0;

    cout << "File reconstructed.\n";
}

template <typename T, typename Rec>
void sequentialFile<T, Rec>::remove(T key) {
    ifstream inFile;
    inFile.open(datfile, ios::binary);
}

template <typename T, typename Rec>
Rec sequentialFile<T, Rec>::search(T key) {
    Rec record;
    ifstream inFile;
    inFile.open(datfile, ios::binary);
    long pos;
    bool found = binarySearch(key, this, pos);
    if (!found) {
        if (pos < 0) {
            return Rec();
        } else {
            inFile.seekg(pos*sizeof(Rec));
            inFile.read((char*)&record, sizeof(Rec));
            while (record.next >= validRecords && record.next != -1) {
                inFile.seekg(record.next*sizeof(Rec));
                inFile.read((char*)&record, sizeof(Rec));
                if (record.key == key) return record;
            }
        }
        cout << "Error. Record not found.\n";
        return Rec();
    } else {
        inFile.seekg(pos*sizeof(Rec));
        inFile.read((char*)&record, sizeof(Rec));
    }

    return record;
}

template <typename T, typename Rec>
vector<Rec> sequentialFile<T, Rec>::rangeSearch(T beginkey, T endkey) {
    vector<Rec> v;
    if (endkey < beginkey) {
        cout << "Error. End key is lower than start key";
        return v;
    }

    ifstream inFile;
    inFile.open(datfile, ios::binary);
    Rec record;
    long beginpos;
    bool found = binarySearch(beginkey, this, beginpos);

    if (!found) {
        if (beginpos < 0) {
            beginpos = 0;
            inFile.seekg(0);
        }
        else {
            beginpos++;
            inFile.seekg(beginpos*sizeof(Rec));
        }
    } else {
        inFile.seekg(beginpos*sizeof(Rec));
    }

    inFile.read((char*)&record, sizeof(record));
    T currentkey = record.key;

    while(currentkey <= endkey && record.next != -1) {
        v.push_back(record);
        inFile.seekg(record.next*sizeof(Rec));
        inFile.read((char *) &record, sizeof(record));
        currentkey = record.key;
    }

    if (record.key <= endkey) v.push_back(record);

    inFile.close();
    return v;
}

template <typename T, typename Rec>
bool binarySearch(T key, sequentialFile<T, Rec>* seqFile, long &pos) {
    ifstream inFile;
    inFile.open(seqFile->datfile, ios::binary);
    Rec record;
    long left = 0;
    long right = seqFile->validRecords - 1;
    long mid;
    while (right >= left) {
        mid = floor((left+right)/2);
        inFile.seekg(mid*sizeof(Rec));
        inFile.read((char*)&record, sizeof(Rec));
        if (key < record.key) {
            right = mid - 1;
        } else if (key > record.key){
            left = mid + 1;
        } else {
            pos = mid;
            return true;
        }
    }
    inFile.close();
    pos = right;
    return false;
}
