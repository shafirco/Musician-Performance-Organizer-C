//shafir cohen 315995589
//amit kochavi 315409102

#ifndef _MUS_HEADER_H
#define _MUS_HEADER_H

#include "InstrumentsHeader.h"

typedef struct
{
	unsigned short insId;
	float price;
	bool flag;
}MusicianPriceInstrument;

typedef struct lnode
{
	MusicianPriceInstrument data;
	struct lnode* next;
} LNODE;

typedef struct list
{
	LNODE* head;
	LNODE* tail;
}MPIList;

typedef struct
{
	char** name;
	MPIList instruments;
	bool available;
	int numOfNames;
}Musician;

typedef struct dinamicArrSizes
{
	int logSize;
	int phisiSize;
} DinamicArrSizes;

//prototipes
Musician* buildArrOfMusicians(FILE* musicianFile, int* size, InstrumentTree instrumentTr);
bool isEmptyList(MPIList* lst);
void makeEmptyList(MPIList* lst);
LNODE* createNewListNode(MusicianPriceInstrument data, LNODE* next);
void insertDataToEndList(MPIList* lst, MusicianPriceInstrument data);
void insertNodeToEndList(MPIList* lst, LNODE* tail);
void getDataOfInstrument(MusicianPriceInstrument* dataOfInstrument, InstrumentTree instrumentTr, char* currToken, char* nextToken);
void insertDataOfMus(Musician* musician, MPIList instrunemtList, int numOfNames);
Musician*** buildArrOfArrsPointersToMusician(Musician* MusiciansGroup, int numOfInstruments, int numOfMusicians, DinamicArrSizes* sizesArr);

#endif