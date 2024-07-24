//shafir cohen 315995589
//amit kochavi 315409102

#ifndef _CONCERT_HEADER_H
#define _CONCERT_HEADER_H

#include "MusiciansHeader.h"

#define IMPORTANT 1
#define NOT_IMPORTANT 0
#define FIRST_SMALLER_THAN_SECOND -1
#define FIRST_BIGGER_THAN_SECOND 1
#define EVEN 0

typedef struct
{
	int day, month, year;
	float hour;
} Date;

typedef struct
{
	int num;
	int inst;
	char importance;
} ConcertInstrument;

typedef struct LNODECI
{
	ConcertInstrument data;
	struct LNODECI* next;
}LNODECI;

typedef struct
{
	LNODECI* head;
	LNODECI* tail;
}CIList;

typedef struct
{
	Date date_of_concert;
	char* name;
	CIList instruments;
} Concert;


//prototipes
bool isEmptyCList(CIList* lst);
void makeEmptyCList(CIList* lst);
void insertDataToEndCList(CIList* lst, ConcertInstrument data);
LNODECI* createNewCListNode(ConcertInstrument data, LNODECI* next);
void insertNodeToEndCIList(CIList* lst, LNODECI* tail);
int comparePrice(void** musician1, void** musician2);
void turnOnFlags(Musician** Musicians, unsigned short id, int sizeArr);
void turnOnFlag(Musician* Musician, unsigned short id);
void turnOffFlags(Musician** Musicians, int sizeArr);
void turnOffFlag(Musician* Musician);
Concert* getConcertData(InstrumentTree tr, bool* concertIsCanceled);
float calculateHour(char* str);
char* getFullNameMus(Musician* musician);
char* fromFloatToStr(float num);
char* getWordFromUser(bool* lineFinish);
char* printInstrumentConcert(InstrumentTree tr, Musician*** MusiciansCollection, int sizeArr, Concert* concert, LNODECI* curr, unsigned short i);
void printConcerts(InstrumentTree tr, Musician*** MusiciansCollection, DinamicArrSizes* sizesArr, Musician* MusiciansGroup, int numOfMusicians);
void printCancelMessage(char* nameConcert);
void printConcertData(Concert* concert, char* concertData);
void strcatData(char* str, char* fullName, char* instrumentName, char* price);
void printConcert(InstrumentTree tr, Musician*** MusiciansCollection, DinamicArrSizes* sizesArr, bool* readingConcertsIsFinished);

#endif