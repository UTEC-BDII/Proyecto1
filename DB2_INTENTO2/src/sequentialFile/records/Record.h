#pragma once

#include "../../libs.h"

class Record {
protected:
    virtual void read() = 0;
    virtual void write() = 0;
    virtual void serialization(string object) = 0;
    virtual void printData() = 0;
};
