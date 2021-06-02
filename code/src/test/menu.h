#include "../staticHash/staticHash.h"
#include "../staticHash/staticHash.cpp"
#include "../sequentialFile/sequentialFile.h"
#include "../sequentialFile/sequentialFile.cpp"

template <typename Record>
void testHash(string filename);

template <typename Record>
void testSequential(string filename);

void clear();
string choosefile();
string choosetechnique();
void testTimeBasket(string filename, int auxFactor, long start, long end);