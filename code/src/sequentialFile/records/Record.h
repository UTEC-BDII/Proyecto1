#pragma once

#include "../../libs.h"

/* Base class for record classes on Sequential File. Each record has a pointer to 
the next record and three methods for serialization, printing the record data and
initializing from input. */
class RecordSeq {
public:
    long next;
protected:
    virtual void serialization(string object) = 0;
    virtual void printData() = 0;
    virtual void input() = 0;
};
