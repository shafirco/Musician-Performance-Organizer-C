//shafir cohen 315995589
//amit kochavi 315409102

#include "MusiciansHeader.h"
#include "CheckingHeader.h"

//gets a list and returns if it's empty or not
bool isEmptyList(MPIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}
//gets a list and makes it empty
void makeEmptyList(MPIList* lst)
{
	lst->head = lst->tail = NULL;
}
//get a MPIList and data(MusicianPriceInstrument) and makes new node to the end list
void insertDataToEndList(MPIList* lst, MusicianPriceInstrument data)
{
	LNODE* newTail;
	newTail = createNewListNode(data, NULL);
	insertNodeToEndList(lst, newTail);
}
////gets data(MusicianPriceInstrument) and the ptr of the next (LNODE*) and creates new list node and returns it
LNODE* createNewListNode(MusicianPriceInstrument data, LNODE* next)
{
	LNODE* res;
	res = (LNODE*)malloc(sizeof(LNODE));
	checkMemoryAllocation(res);
	res->data = data;
	res->next = next;
	return res;
}
//get a MPIList and the ptr of the tail and inserts the node to the end list
void insertNodeToEndList(MPIList* lst, LNODE* tail)
{
	if (isEmptyList(lst) == true)
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}
//The function build arr Of arrs of pointers to musicians according to the instrument they play and returns it
Musician*** buildArrOfArrsPointersToMusician(Musician* MusiciansGroup, int numOfInstruments, int numOfMusicians, DinamicArrSizes* sizesArr)
{
	int i, logSize, phiSize, currId;
	LNODE* currNode;
	Musician*** MusiciansCollection = (Musician***)malloc(numOfInstruments * sizeof(Musician**));
	checkMemoryAllocation(MusiciansCollection);
	for (i = 0; i < numOfInstruments; i++) {
		MusiciansCollection[i] = (Musician**)malloc(sizeof(Musician*));
		checkMemoryAllocation(MusiciansCollection[i]);
		sizesArr[i].logSize = 0;
		sizesArr[i].phisiSize = 1;
	}
	for (i = 0; i < numOfMusicians; i++) {
		currNode = MusiciansGroup[i].instruments.head;
		while (currNode != NULL) {
			currId = currNode->data.insId;
			if (sizesArr[currId].logSize == sizesArr[currId].phisiSize) {
				sizesArr[currId].phisiSize *= 2;
				MusiciansCollection[currId] = realloc(MusiciansCollection[currId], (sizesArr[currId].phisiSize) * sizeof(Musician*));
				checkMemoryReallocation(MusiciansCollection[currId]);
			}
			MusiciansCollection[currId][(sizesArr[currId].logSize)] = (MusiciansGroup + i);
			(sizesArr[currId].logSize)++;
			currNode = currNode->next;
		}
	}
	for (i = 0; i < numOfInstruments; i++) {
		MusiciansCollection[i] = realloc(MusiciansCollection[i], sizesArr[i].logSize * sizeof(Musician*));
		checkMemoryReallocation(MusiciansCollection[i]);
	}
	return MusiciansCollection;
}
//the function insert data of instrument of one musician
void getDataOfInstrument(MusicianPriceInstrument* dataOfInstrument, InstrumentTree instrumentTr, char* currToken, char* nextToken)
{
	dataOfInstrument->insId = findInsId(instrumentTr, currToken);//finds and saves it's ID
	dataOfInstrument->price = atoi(nextToken);//saves it's price
	dataOfInstrument->flag = false;
}
//the function bulids array of musicians according to the musicians file and returns it
Musician* buildArrOfMusicians(FILE* musiciansFile, int* size, InstrumentTree instrumentTr)
{
	MPIList instrunemtList;
	BOOL theFileIsNotFinished;
	int phisySize = 2, numOfNames, numOfMusucsain = 0, sizeStr, phisySizeNames;
	Musician* MusiciansGroup = (Musician*)malloc(phisySize * sizeof(Musician));
	checkMemoryAllocation(MusiciansGroup);
	char seps[] = " ,.;:?!-\t'()[]{}<>~_";
	char* currToken, * nextToken, * rowFromMusFile;
	MusicianPriceInstrument dataOfInstrument;
	rowFromMusFile = changeRowFromFileToString(musiciansFile, &theFileIsNotFinished);
	while (theFileIsNotFinished == TRUE) {
		currToken = strtok(rowFromMusFile, seps);//get first name
		MusiciansGroup[numOfMusucsain].name = (char**)malloc(2 * sizeof(char*));
		checkMemoryAllocation(MusiciansGroup[numOfMusucsain].name);
		MusiciansGroup[numOfMusucsain].name[0] = strdup(currToken);
		currToken = strtok(NULL, seps); //get second name (there are at least 2)
		MusiciansGroup[numOfMusucsain].name[1] = strdup(currToken);
		numOfNames = 2;
		phisySizeNames = 2;
		currToken = strtok(NULL, seps); //get the next word from the row
		makeEmptyList(&instrunemtList);
		while (currToken != NULL) {
			nextToken = strtok(NULL, seps);//get the next word
			if (nextToken[0] >= '0' && nextToken[0] <= '9') {//if the next word is a number so the current word is an instrument and the next is it's price
				getDataOfInstrument(&dataOfInstrument, instrumentTr, currToken, nextToken);
				insertDataToEndList(&instrunemtList, dataOfInstrument);
				currToken = strtok(NULL, seps);//get the next word
			}
			else { //the next token is not a num and not a null- so it is a name
				if (phisySizeNames == numOfNames)
				{
					phisySizeNames *= 2;
					MusiciansGroup[numOfMusucsain].name = realloc(MusiciansGroup[numOfMusucsain].name, phisySizeNames * sizeof(char*));
				}
				MusiciansGroup[numOfMusucsain].name[numOfNames] = strdup(currToken);
				numOfNames++;
				currToken = nextToken;
			}
		}
		MusiciansGroup[numOfMusucsain].name = realloc(MusiciansGroup[numOfMusucsain].name, numOfNames * sizeof(char*));
		insertDataOfMus(MusiciansGroup + numOfMusucsain, instrunemtList, numOfNames);
		numOfMusucsain++;
		if (phisySize == numOfMusucsain) {
			phisySize *= 2;
			MusiciansGroup = realloc(MusiciansGroup, phisySize * sizeof(Musician));
			checkMemoryReallocation(MusiciansGroup);
		}
		free(rowFromMusFile);
		rowFromMusFile = changeRowFromFileToString(musiciansFile, &theFileIsNotFinished);
	}
	MusiciansGroup = realloc(MusiciansGroup, numOfMusucsain * sizeof(Musician));
	checkMemoryReallocation(MusiciansGroup);
	*size = numOfMusucsain;
	return MusiciansGroup;
}
//the function gets data of one musician and inserts it to the musician struct 
void insertDataOfMus(Musician* musician, MPIList instrunemtList, int numOfNames)
{
	musician->instruments = instrunemtList;
	musician->available = false;
	musician->numOfNames = numOfNames;
}