//shafir cohen 315995589
//amit kochavi 315409102

#ifndef _CHECKING_HEADER_H
#define _CHECKING_HEADER_H

#include "ConcertsHeader.h"

//prototipes
void checkOpeningFile(FILE* f);
void checkMemoryAllocation(void* res);
void checkMemoryReallocation(void* res);

#endif