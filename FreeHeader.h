//shafir cohen 315995589
//amit kochavi 315409102

#ifndef _FREE_HEADER_H
#define _FREE_HEADER_H

#include "ConcertsHeader.h"


//prototipes
void freeMPIList(MPIList* lst);
void freeCIList(CIList* lst);
void freeMusician(Musician musician);
void freeMusiciansGroup(Musician* MusiciansGroup, int numOfMusicians);
void freeMusiciansCollection(Musician*** MusiciansCollection, int numOfInstruments);
void freeTree(InstrumentTree* tr);
void freeTreeHelper(TreeNode* root);

#endif