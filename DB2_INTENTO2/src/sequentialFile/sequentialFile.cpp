
#include "sequentialFile.h"

// Constructor of sequentialFile class
template <typename T, typename Record>
sequentialFile<T, Record>::sequentialFile(string filename, size_t auxFactor) {
    this->filename = filename; // Name of data file
    this->auxFactor = auxFactor; // Max number of auxiliary records
    createBinaryFile();
    this->validRecords = countRecords(); // Number of non-auxiliary records (initially the number of records)
    this->auxRecords = 0; // Number of auxiliary records (initially 0)
}

// Create a binary file from the main data file to work on
template <typename T, typename Record>
void sequentialFile<T, Record>::createBinaryFile() {
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
    Record r;
    while (getline(infile, str, '\n')) {
        r.serialization(str);
        r.next = (++s);
        outfile.write((char*) &r, sizeof(Record));
    }
    
    r.next = -1;
    outfile.seekp((--s)*sizeof(Record));
    outfile.write((char*) &r, sizeof(Record));

    outfile.close();
    infile.close();
}

// Count total number of records on binary file
template <typename T, typename Record>
size_t sequentialFile<T, Record>::countRecords() {
    ifstream inFile;
    inFile.open(datfile, ios::binary);
    inFile.seekg(0, inFile.end);
    size_t size = inFile.tellg();
    inFile.close();
    return size/sizeof(Record);
}

// Add record to binary file as an auxiliary record
template <typename T, typename Record>
void sequentialFile<T, Record>::add(Record record) {
    // If number of auxiliary records reaches auxFactor, reconstruct file
    if (auxRecords >= auxFactor) reconstruct();

    fstream fs;
    fs.open(datfile, ios::binary | ios::out | ios::in);

    // Find position of record previous to the position where new record should be inserted
    long pos;
    binarySearch(record.key, this, pos);

    // Read previous record
    Record prevRecord;
    fs.seekg(pos*sizeof(Record));
    fs.read((char*)&prevRecord, sizeof(Record));

    // New record points to the next record of prevRecord
    record.next = prevRecord.next;
    // prevRecord points to the position of new record (last record on file)
    prevRecord.next = validRecords + auxRecords;

    // Write updated records to file
    fs.seekp(0, fs.end);
    fs.write((char*) &record, sizeof(Record));
    fs.seekp(pos*sizeof(Record));
    fs.write((char*) &prevRecord, sizeof(Record));

    auxRecords++;
}

// Remove record from file (logically, not phisycally)
template <typename T, typename Record>
void sequentialFile<T, Record>::remove(T key) {
    ifstream inFile;
    inFile.open(datfile, ios::binary);
}

// Search for record on fiel by its key value
template <typename T, typename Record>
Record sequentialFile<T, Record>::search(T key) {
    Record record;
    ifstream inFile;
    inFile.open(datfile, ios::binary);
    // Find record's position
    long pos;
    bool found = binarySearch(key, this, pos);
    if (!found) {
        if (pos < 0) {
            return Record();
        } else { // If not found, read record
            inFile.seekg(pos*sizeof(Record));
            inFile.read((char*)&record, sizeof(Record));
            // While next record belongs to the auxiliary part, keep searching for key
            while (record.next >= validRecords && record.next != -1) {
                inFile.seekg(record.next*sizeof(Record));
                inFile.read((char*)&record, sizeof(Record));
                if (record.key == key) return record;
            }
        }
        cout << "Error. Record not found.\n";
        return Record();
    } else { // If found, return record at position
        inFile.seekg(pos*sizeof(Record));
        inFile.read((char*)&record, sizeof(Record));
    }

    return record;
}

template <typename T, typename Record>
vector<Record> sequentialFile<T, Record>::rangeSearch(T beginkey, T endkey) {
    vector<Record> v;
    // If the endkey is lower that the beginkey, return
    if (endkey < beginkey) {
        cout << "Error. End key is lower than start key";
        return v;
    }

    ifstream inFile;
    inFile.open(datfile, ios::binary);
    Record record;
    // Find position to start search
    long beginpos;
    bool found = binarySearch(beginkey, this, beginpos);

    // If not found
    if (!found) {
        // If position is before the beginning, start search from 1st record
        if (beginpos < 0) {
            beginpos = 0;
            inFile.seekg(0);
        } else { // Else, start search from the next record to beginpos
            beginpos++;
            inFile.seekg(beginpos*sizeof(Record));
        }
    } else { // If found, start search from that record
        inFile.seekg(beginpos*sizeof(Record));
    }

    inFile.read((char*)&record, sizeof(record));
    T currentkey = record.key;

    // Add records to result until the current key is greater than endkey or all records are read
    while(currentkey <= endkey && record.next != -1) {
        v.push_back(record);
        inFile.seekg(record.next*sizeof(Record));
        inFile.read((char *) &record, sizeof(record));
        currentkey = record.key;
    }

    if (record.key <= endkey) v.push_back(record);

    inFile.close();
    return v;
}

// Create a new file from the binary file where all records become valid and are stored in physical order
template <typename T, typename Record>
void sequentialFile<T, Record>::reconstruct() {
    string reconstructFile = "reconstruct.dat";
    ifstream inFile(datfile, ios::binary);
    ofstream outFile(reconstructFile, ios::binary);
    Record record;
    long next;
    long cont = 1;

    // Read first record from original file and write to new
    inFile.seekg(0);
    inFile.read((char *) &record, sizeof(Record));
    next = record.next;
    record.next = cont++;
    outFile.seekp(0);
    outFile.write((char *) &record, sizeof(Record));

    // Read through original file following the pointers to the next record until end is reached
    while (next != -1) {
        inFile.seekg(next*sizeof(Record));
        inFile.read((char *) &record, sizeof(Record));
        next = record.next;
        if (next != -1) record.next = cont++;
        outFile.write((char *) &record, sizeof(Record));

        vector<Record> auxRec;
        vector<long> auxNext;
        // If the next record is in auxiliary part, store all records until auxiliary part is left
        // or the end is reached
        while (next >= validRecords && next != -1) {
            inFile.seekg(next*sizeof(Record));
            inFile.read((char*)&record, sizeof(Record));
            next = record.next;
            auxRec.push_back(record);
            auxNext.push_back(record.next);
        }

        // Sort vector of records that belong to the auxiliary part by key to write them in order
        // to the new file
        sort(auxRec.begin(), auxRec.end(), [](Record &r1, Record &r2){return r1.key < r2.key;});
        for (size_t i = 0; i < auxRec.size(); i++) {
            auxRec[i].next = auxNext[i];
            if (auxRec[i].next != -1) auxRec[i].next = cont++;
            outFile.write((char *) &auxRec[i], sizeof(Record));
        }
    }
    
    inFile.close();
    outFile.close();
    //if (std::remove(datfile.c_str())) cout << "removed " << datfile << endl;
    //rename(reconstructFile.c_str(), datfile.c_str());
    
    datfile = reconstructFile; // replace previous binary file with new one
    validRecords = countRecords(); // the number of valid records is the total number of records
    auxRecords = 0; // the number of auxiliary records is 0

    cout << "File reconstructed.\n";
}

// Modified binary search for Sequential File. Returns true if record is found by its key or
// false if not. Also, receives a long by reference and modifies it so that it stores the
// position of the record (if found) or the one before it (if not found)
template <typename T, typename Record>
bool binarySearch(T key, sequentialFile<T, Record>* seqFile, long &pos) {
    ifstream inFile;
    inFile.open(seqFile->datfile, ios::binary);
    Record record;
    long left = 0;
    long right = seqFile->validRecords - 1;
    long mid;
    while (right >= left) {
        mid = floor((left+right)/2);
        inFile.seekg(mid*sizeof(Record));
        inFile.read((char*)&record, sizeof(Record));
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
