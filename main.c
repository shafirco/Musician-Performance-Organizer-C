//shafir cohen 315995589
//amit kochavi 315409102

#include "ConcertsHeader.h"
#include "FreeHeader.h"
#include "CheckingHeader.h"

void main(int argc, char** argv)
{
	int numOfInstruments, numOfMusicians;
	Musician* MusiciansGroup;
	Musician*** MusiciansCollection;
	DinamicArrSizes* sizesArr;
	FILE* instrumentsFile = fopen(argv[1], "r");
	FILE* musiciansFile = fopen(argv[2], "r");
	checkOpeningFile(instrumentsFile);
	checkOpeningFile(musiciansFile);

	InstrumentTree instrumentTr = buildInstrumentTree(instrumentsFile, &numOfInstruments);
	fclose(instrumentsFile);

	MusiciansGroup = buildArrOfMusicians(musiciansFile, &numOfMusicians, instrumentTr);
	fclose(musiciansFile);

	sizesArr = (DinamicArrSizes*)malloc(numOfInstruments * sizeof(DinamicArrSizes));
	checkMemoryAllocation(sizesArr);
	MusiciansCollection = buildArrOfArrsPointersToMusician(MusiciansGroup, numOfInstruments, numOfMusicians, sizesArr);

	printConcerts(instrumentTr, MusiciansCollection, sizesArr, MusiciansGroup, numOfMusicians);

	freeTree(&instrumentTr);
	freeMusiciansGroup(MusiciansGroup, numOfMusicians);
	freeMusiciansCollection(MusiciansCollection, numOfInstruments);
	free(sizesArr);
}