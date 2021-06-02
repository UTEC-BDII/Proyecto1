#pragma once

#include "../../libs.h"

/* Base class for record classes on Static Hash. Unlike records for Sequential
file, doesn't need a pointer to the position of the next record. Has three methods 
for serialization, printing the record data and initializing from input. */
class RecordHash {
protected:
    virtual void serialization(string object) = 0;
    virtual void printData() = 0;
    virtual void input() = 0;
};