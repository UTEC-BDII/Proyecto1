
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

    size_t position = filename.find(".");
    string extractName = (string::npos == position)? filename : filename.substr(0, position);
    string newFile = extractName + "_seq.csv";
    datfile = regex_replace(newFile, regex("csv"), "dat");

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

    Record prevRecord;

    // If the record should be inserted at the beginning, replace with first record so
    // that the first record is never in the auxiliary part
    if (pos < 0) {
        fs.seekg(0);
        fs.read((char*)&prevRecord, sizeof(Record));
        record.next = validRecords + auxRecords;
        fs.seekp(0);
        fs.write((char*) &record, sizeof(Record));
        fs.seekp(0, fs.end);
        fs.write((char*) &prevRecord, sizeof(Record));
        auxRecords++;
        cout << "Added record.\n";
        return;
    }

    // Read previous record
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
    cout << "Added record.\n";
}

// Remove record from file (logically, not physically)
template <typename T, typename Record>
void sequentialFile<T, Record>::remove(T key) {
    fstream fs;
    fs.open(datfile, ios::in | ios::out | ios::binary);
    Record record;
    Record prevRecord;
    long prevPos;
    // Find record's position
    long pos;
    bool found = binarySearch(key, this, pos);
    if (!found) {
        // The record with the lowest key is always a valid record, so if pos < 0 the searched
        // record is not on the dataset. Return.
        if (pos < 0) {
            cout << "Error. Record with key " << key << " not found.\n";
            return;
        }
        else { // If not found and pos >= 0, read record at pos
            prevPos = pos;
            fs.seekg(prevPos*sizeof(Record));
            fs.read((char*)&prevRecord, sizeof(Record));
            if (prevRecord.next == -1) { // If read record is the last one, return
                cout << "Error. Record with key " << key << " not found.\n";
                return;
            }
            pos = prevRecord.next;
            fs.seekg(pos*sizeof(Record));
            fs.read((char*)&record, sizeof(Record));

            // While next record belongs to the auxiliary part, keep searching for key
            while (pos >= validRecords && pos != -1) {
                // If record is found on auxiliary part, remove
                if (record.key == key) {
                    prevRecord.next = record.next;
                    record.next = -2;
                    fs.seekp(prevPos*sizeof(Record));
                    fs.write((char*) &prevRecord, sizeof(Record));
                    fs.seekp(pos*sizeof(Record));
                    fs.write((char*) &record, sizeof(Record));
                    cout << "Removed record with key " << key << ".\n";
                    return;
                }
                prevPos = pos;
                prevRecord = record;
                fs.seekg(prevRecord.next*sizeof(Record));
                fs.read((char*)&record, sizeof(Record));
                pos = prevRecord.next;
            }
            // If record wasn't found on auxiliary part, return
            cout << "Error. Record with key " << key << " not found.\n";
            return;
        }
    } else {
        prevPos = pos - 1;
        // Read record on the position physically before the record to remove
        fs.seekg(prevPos*sizeof(Record));
        fs.read((char*)&prevRecord, sizeof(Record));
        // Read next record to the previously read
        fs.seekg(prevRecord.next*sizeof(Record));
        fs.read((char*)&record, sizeof(Record));
        // In case the previous record is in the auxiliary part, iterate through the positions
        // of next while keeping the last read record
        while (record.key != key) {
            prevPos = prevRecord.next;
            prevRecord = record;
            fs.seekg(prevRecord.next*sizeof(Record));
            fs.read((char*)&record, sizeof(Record));
        }
        // Removed record points to -2 while the previous record points to its next
        prevRecord.next = record.next;
        record.next = -2;
        // Write changes to the file
        fs.seekp(prevPos*sizeof(Record));
        fs.write((char*) &prevRecord, sizeof(Record));
        fs.seekp(pos*sizeof(Record));
        fs.write((char*) &record, sizeof(Record));
    }

    cout << "Removed record with key " << key << ".\n";
}

// Search for record on file by its key value
template <typename T, typename Record>
Record sequentialFile<T, Record>::search(T key) {
    Record record;
    ifstream inFile;
    inFile.open(datfile, ios::binary);
    // Find record's position
    long pos;
    bool found = binarySearch(key, this, pos);
    if (!found) {
        // The record with the lowest key is always a valid record, so if pos < 0 the searched
        // record is not on the dataset. Return.
        if (pos < 0) {
            cout << "Error. Record not found.\n";
            return Record();
        }
        else { // If not found and pos >= 0, read record at pos
            inFile.seekg(pos*sizeof(Record));
            inFile.read((char*)&record, sizeof(Record));
            // While next record belongs to the auxiliary part, keep searching for key
            while (record.next >= validRecords && record.next != -1) {
                inFile.seekg(record.next*sizeof(Record));
                inFile.read((char*)&record, sizeof(Record));
                if (record.key == key) { 
                    cout << "Record with key " << key << " found.\n";
                    return record;
                }
            }
        }
        cout << "Error. Record not found.\n";
        return Record();
    } else { // If found, return record at position
        inFile.seekg(pos*sizeof(Record));
        inFile.read((char*)&record, sizeof(Record));
    }
    cout << "Record with key " << key << " found.\n";
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
            inFile.seekg(beginpos*sizeof(Record));
            inFile.read((char*)&record, sizeof(record));
            inFile.seekg(record.next*sizeof(Record));
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

    // Replace previous binary file with new one
    if (std::remove(datfile.c_str()) != 0) {
        cout << "Error. Failed to remove previous datfile.";
        return;
    }
    if (rename(reconstructFile.c_str(), datfile.c_str()) != 0) {
        cout << "Error. Failed to rename new datfile.";
        return;
    }

    validRecords = countRecords(); // The number of valid records is the total number of records
    auxRecords = 0; // The number of auxiliary records is 0

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
        if (key < record.key || record.next == -2) {
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
