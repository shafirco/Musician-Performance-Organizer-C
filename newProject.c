#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


#define TRUE 0
#define SUCCEEDED 0
#define BOOL int


typedef struct treeNode
{
	char* instrument;
	unsigned short insId;
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree
{
	TreeNode* root;
} InstrumentTree;


typedef struct dinamicArrSizes
{
	int logSize;
	int phisiSize;
} DinamicArrSizes;

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
	bool used;
}Musician;


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


TreeNode* createNewTNode(char* data, TreeNode* left, TreeNode* right);
void checkOpeningFile(FILE* f);
char* changeRowFromFileToString(FILE* fp, BOOL* theFileIsNotFinished);
void checkMemoryAllocation(void* res);
void checkMemoryReallocation(void* res);
InstrumentTree buildInstrumentTree(FILE* instrumentsFile, int* size);
int findInsId(InstrumentTree tree, char* instrument);
TreeNode* findHelper(TreeNode* root, char* instrument);
Musician* buildArrOfPtrToMusician(FILE* musicianFile, int* size, InstrumentTree instrumentTr);
int fromStringToNum(char* str);
bool isEmptyList(MPIList* lst);
void makeEmptyList(MPIList* lst);
LNODE* createNewListNode(MusicianPriceInstrument data, LNODE* next);
void insertDataToEndList(MPIList* lst, MusicianPriceInstrument data);
void insertNodeToEndList(MPIList* lst, LNODE* tail);
Musician*** buildArrOfArrsPointersToMusician(Musician* MusiciansGroup, int numOfInstruments, int numOfMusicians, DinamicArrSizes* sizesArr);
char* getWordFromUser(bool* lineFinish);

bool isEmptyCList(CIList* lst);
void makeEmptyCList(CIList* lst);
void insertDataToEndCList(CIList* lst, ConcertInstrument data);
LNODECI* createNewCListNode(ConcertInstrument data, LNODECI* next);
void insertNodeToEndCIList(CIList* lst, LNODECI* tail);

void printConcert(InstrumentTree tr, Musician*** MusiciansCollection, DinamicArrSizes* sizesArr);
int comparePrice(void** musician1, void** musician2);
void turnOnFlags(Musician** Musicians, unsigned short id, int sizeArr);
void turnOnFlag(Musician* Musician, unsigned short id);
void turnOffFlags(Musician** Musicians, int sizeArr);
void turnOffFlag(Musician* Musician);
Concert* getConcertData(InstrumentTree tr);

char* findInstrumentName(InstrumentTree tree, unsigned short id);
TreeNode* findInstrumentNameHelper(TreeNode* root, unsigned short id);
void printInstrumentConcert(InstrumentTree tr, Musician*** MusiciansCollection, int sizeArr, Concert* concert, LNODECI* curr, unsigned short i);

void main(int argc, char** argv)
{
	int numOfInstruments, numOfMusicians;
	FILE* instrumentsFile = fopen(argv[1], "r");
	FILE* musiciansFile = fopen(argv[2], "r");
	checkOpeningFile(instrumentsFile);
	checkOpeningFile(musiciansFile);

	InstrumentTree instrumentTr = buildInstrumentTree(instrumentsFile, &numOfInstruments);

	Musician* MusiciansGroup;
	MusiciansGroup = buildArrOfPtrToMusician(musiciansFile, &numOfMusicians, instrumentTr);

	Musician*** MusiciansCollection;
	DinamicArrSizes* sizesArr = (DinamicArrSizes*)malloc(numOfInstruments * sizeof(DinamicArrSizes));
	checkMemoryAllocation(sizesArr);
	MusiciansCollection = buildArrOfArrsPointersToMusician(MusiciansGroup, numOfInstruments, numOfMusicians, sizesArr);


	printConcert(instrumentTr, MusiciansCollection, sizesArr);
	
	fclose(instrumentsFile);

}

void printConcert(InstrumentTree tr, Musician*** MusiciansCollection, DinamicArrSizes* sizesArr)
{
	Concert* concert = getConcertData(tr);
	LNODECI* curr = NULL;
	LNODE* runner = NULL;
	curr = concert->instruments.head;
	unsigned short i;
	int j, counter;

	while (curr != NULL) 
	{
		i = curr->data.inst;

		if (curr->data.num < sizesArr[i].logSize)
		{
			turnOnFlags(MusiciansCollection[i], i, sizesArr[i].logSize);
			qsort(MusiciansCollection[i], sizesArr[i].logSize, sizeof(Musician*), comparePrice);
			turnOffFlags(MusiciansCollection[i], sizesArr[i].logSize);
			printInstrumentConcert(tr, MusiciansCollection, sizesArr[i].logSize, concert, curr, i);
			
		}
		else
		{
			printf("Could not find musicians for the concert %s", concert->name);
			return;
		}
	}

}

void printInstrumentConcert(InstrumentTree tr, Musician*** MusiciansCollection, int sizeArr, Concert* concert, LNODECI* curr, unsigned short i)
{
	int counter = 0, j;
	LNODE* runner;
	char* str = (char*)malloc(sizeof(char));
	checkMemoryAllocation(str);
	str[0] = 0;
	if (curr->data.importance == 0)
		j = 0;
	else
		j = sizeArr - 1;
	while (counter < curr->data.num)
	{
		if (MusiciansCollection[i][j]->used == false)
		{
			MusiciansCollection[i][j]->used = true;
			strcat(str, MusiciansCollection[i][j]->name);
			strcat(str, " ");
			runner = MusiciansCollection[i][j]->instruments.head;
			while (runner->data.insId != i)
				runner = runner->next;
			strcat(str, findInstrumentName(tr, i));
			strcat(str, " ");
			strcat(str, (char*)runner->data.price);   ////*******  ////need a func
			strcat(str, " ");
			counter++;
		}
		if (curr->data.importance == 0) {
			j++;
			if (sizeArr - j < curr->data.num - counter)
			{
				printf("Could not find musicians for the concert %s", concert->name);
				return;
			}
		}
		else {
			j--;
			if (j < curr->data.num - counter)
			{
				printf("Could not find musicians for the concert %s", concert->name);
				return;
			}
		}
	}
}


char* findInstrumentName(InstrumentTree tree, unsigned short id)
{
	TreeNode* node = findHelper(tree.root, id);
	if (node)
		return node->instrument;
	else
		return NULL;
}

TreeNode* findInstrumentNameHelper(TreeNode* root, unsigned short id)
{
	TreeNode* res;
	if (root == NULL)
		return NULL;
	else if (root->insId== id) 
		return root;
	else
	{
		res = findInstrumentNameHelper(root->left, id);
		if (res == NULL) //Not found in left side, go to right side
			return findInstrumentNameHelper(root->right, id); //Return the result of the right side
		else
			return res;
	}
}

int comparePrice(void** musician1, void** musician2)
{

	Musician** a = (Musician**)musician1;
	Musician** b = (Musician**)musician2;

	LNODE* curr1 = (*a)->instruments.head;
	LNODE* curr2 = (*b)->instruments.head;

	while (curr1->data.flag != true)
		curr1 = curr1->next;

	while (curr2->data.flag != true)
		curr2 = curr2->next;

	if (curr1->data.price< curr2->data.price) return -1;
	else if (curr1->data.price > curr2->data.price) return 1;
	else return 0;
}


void turnOnFlags(Musician** Musicians, unsigned short id,int sizeArr)
{
	int i;
	for (i = 0; i < sizeArr; i++) {
		turnOnFlag(Musicians[i], id);
	}
}
void turnOnFlag(Musician* Musician, unsigned short id)
{
	LNODE* curr = Musician->instruments.head;
	while (curr->data.insId != id)
		curr = curr->next;
	curr->data.flag = true;
}

void turnOffFlags(Musician** Musicians, int sizeArr)
{
	int i;
	for (i = 0; i < sizeArr; i++) {
		turnOffFlag(Musicians[i]);
	}
}
void turnOffFlag(Musician* Musician)
{
	LNODE* curr = Musician->instruments.head;
	while (curr->data.flag == false)
		curr = curr->next;
	curr->data.flag = false;
}


Concert* getConcertData(InstrumentTree tr)
{
	bool lineFinish = false;
	/*int logSize = 0, phiSize = 1;
	Concert* arrOfConcerts = (Concert*)malloc(sizeof(Concert));*/

	Concert* Concert;
	ConcertInstrument data;
	Concert->name = getWordFromUser(&lineFinish);

	if (lineFinish == true)
		return NULL;

	Concert->date_of_concert.day = atoi(getWordFromUser(&lineFinish));
	Concert->date_of_concert.month = atoi(getWordFromUser(&lineFinish));
	Concert->date_of_concert.year = atoi(getWordFromUser(&lineFinish));
	Concert->date_of_concert.hour = calculateHour(getWordFromUser(&lineFinish));

	while (lineFinish == false)
	{
		makeEmptyCList(&(Concert->instruments));
		data.inst = findInsId(tr, getWordFromUser(&lineFinish));
		data.num = atoi(getWordFromUser(&lineFinish));
		data.importance = atoi(getWordFromUser(&lineFinish));
	}
	return Concert;
}

float calculateHour(char* str)
{
	float hour, min;
	hour = (float)atoi(strtok(str, ":"));
    min = (float)atoi(strtok(NULL, "\0"));
	hour += (min / 60);
	return hour;
}

char* getWordFromUser(bool* lineFinish)
{
	int c;
	int logSize = 0, phiSize = 1;
	c = getchar();
	char* line = (char*)malloc(sizeof(char));
	checkMemoryAllocation(line);
	while (c != ' ' && c != '\n')
	{
		if (logSize == phiSize)
		{
			phiSize *= 2;
			line = realloc(line, phiSize * sizeof(char));
		}
		line[logSize] = c;
		logSize++;
		c = getchar();
	}
	line = realloc(line, (logSize + 1) * sizeof(char));
	line[logSize] = 0;
	if (c == '\n')
		lineFinish = true;

	return line;
}

Musician*** buildArrOfArrsPointersToMusician(Musician* MusiciansGroup, int numOfInstruments,int numOfMusicians, DinamicArrSizes* sizesArr)
{
	int i, j, logSize, phiSize, currId;
	LNODE* currNode;
	Musician*** MusiciansCollection = (Musician***)malloc(numOfInstruments * sizeof(Musician**));
	checkMemoryAllocation(MusiciansCollection);

	for (i = 0; i < numOfInstruments; i++)
	{
		MusiciansCollection[i] = (Musician**)malloc(sizeof(Musician*));
		checkMemoryAllocation(MusiciansCollection[i]);
		sizesArr[i].logSize = 0;
		sizesArr[i].phisiSize = 1;
	}
	for (j = 0; j < numOfMusicians; j++)
	{
		currNode = MusiciansGroup[j].instruments.head;
		while (currNode != NULL)
		{
			currId = currNode->data.insId;
			if (sizesArr[currId].logSize == sizesArr[currId].phisiSize)
			{
				sizesArr[currId].phisiSize *= 2;
				MusiciansCollection[currId] = realloc(MusiciansCollection[currId], (sizesArr[currId].phisiSize) * sizeof(Musician*));
				checkMemoryReallocation(MusiciansCollection[currId]);
			}
			MusiciansCollection[currId][(sizesArr[currId].logSize)] = (MusiciansGroup + j);
			(sizesArr[currId].logSize)++;
			currNode = currNode->next;
		}
	}
	for (i = 0; i < numOfInstruments; i++)
	{
		MusiciansCollection[i] = realloc(MusiciansCollection[i], sizesArr[i].logSize * sizeof(Musician*));
		checkMemoryReallocation(MusiciansCollection[i]);
	}
	
	return MusiciansCollection;
}

Musician* buildArrOfPtrToMusician(FILE* musiciansFile, int* size, InstrumentTree instrumentTr)
{
	BOOL theFileIsNotFinished;
	int phisySize = 2, numOfNames, numOfMusucsain = 0, sizeStr;
	Musician* MusiciansGroup;

	MusiciansGroup = (Musician*)malloc(phisySize * sizeof(Musician));

	char seps[] = " ,.;:?!-\t'()[]{}<>~_";
	char* currToken, * nextToken, * rowFromMusFile;
	MusicianPriceInstrument dataOfInstrument;
	rowFromMusFile = NULL;//??
	rowFromMusFile = changeRowFromFileToString(musiciansFile, &theFileIsNotFinished);
	while (theFileIsNotFinished == TRUE)
	{
		numOfNames = 0;//count how many names there are for a musician
		//get first name
		currToken = strtok(rowFromMusFile, seps);
		MusiciansGroup[numOfMusucsain].name = (char**)malloc(2 * sizeof(char*));
		MusiciansGroup[numOfMusucsain].name[0] = strdup(currToken);
		//get second name (there are at least 2)
		currToken = strtok(NULL, seps);
		MusiciansGroup[numOfMusucsain].name[1] = strdup(currToken);
		numOfNames = 2;
		//get the next word from the row
		currToken = strtok(NULL, seps);
		MPIList instrunemtList;//??
		makeEmptyList(&instrunemtList);
		while (currToken != NULL)
		{
			nextToken = strtok(NULL, seps);//get the next word

			if (nextToken[0] >= '0' && nextToken[0] <= '9')//if the next word is a number so the current word is an instrument and the next is it's price
			{
				dataOfInstrument.insId = findInsId(instrumentTr, currToken);//finds and saves it's ID
				dataOfInstrument.price = fromStringToNum(nextToken);//saves it's price
				dataOfInstrument.flag = false;

				insertDataToEndList(&instrunemtList, dataOfInstrument);

				//free(currToken);
				//free(nextToken);

				currToken = strtok(NULL, seps);//get the next word
			}
			else //the next token is not a num and not a null- so it is a name
			{
				MusiciansGroup[numOfMusucsain].name[numOfNames] = strdup(currToken);
				numOfNames++;

				currToken = nextToken;
			}
		}
		MusiciansGroup[numOfMusucsain].instruments = instrunemtList;
		numOfMusucsain++;
		if (phisySize == numOfMusucsain)
		{
			phisySize *= 2;
			MusiciansGroup = realloc(MusiciansGroup, phisySize * sizeof(Musician));
		}	
		rowFromMusFile = NULL;
		rowFromMusFile = changeRowFromFileToString(musiciansFile, &theFileIsNotFinished);
	}
	MusiciansGroup = realloc(MusiciansGroup, numOfMusucsain * sizeof(Musician));

	*size = numOfMusucsain;
	return MusiciansGroup;

}

int fromStringToNum(char* str)
{
	int i, j;
	int size = strlen(str);
	int num = 0;
	for (i = 0, j = 1; i < size; j *= 10, i++)
		num += (str[size - 1 - i] - '0') * j;
	return num;
}

InstrumentTree buildInstrumentTree(FILE* instrumentsFile, int* size)
{
	TreeNode* runnerNode = NULL;
	TreeNode* node = NULL;
	InstrumentTree instrumentTr;

	BOOL theFileIsNotFinished;
	char* instrumentName = NULL;
	instrumentName = changeRowFromFileToString(instrumentsFile, &theFileIsNotFinished);
	//check theFileIsNotFinished value??
	instrumentTr.root = createNewTNode(instrumentName, NULL, NULL);

	int numOfTNodes = 1;
	instrumentName = NULL;
	instrumentName = changeRowFromFileToString(instrumentsFile, &theFileIsNotFinished);


	while (theFileIsNotFinished == TRUE)/// (q1)
	{
		runnerNode = instrumentTr.root;
		while (runnerNode != NULL)
		{
			if (strcmp(instrumentName, runnerNode->instrument) > 0)//if runnerNode instrument's name is lexicographic smaller than instrumentName
			{
				node = runnerNode;
				runnerNode = runnerNode->right;//search on the right side
				if (runnerNode == NULL)
					node->right = createNewTNode(instrumentName, NULL, NULL);
			}
			else
			{
				node = runnerNode;
				runnerNode = runnerNode->left;
				if (runnerNode == NULL)
					node->left = createNewTNode(instrumentName, NULL, NULL);
			}
		}
		//runnerNode = createNewTNode(instrumentName, NULL, NULL);
		numOfTNodes++;
		instrumentName = NULL;//??
		instrumentName = changeRowFromFileToString(instrumentsFile, &theFileIsNotFinished);;
	}
	*size = numOfTNodes;
	return instrumentTr;
}

/* Searching for a value in a binary tree - returning the address of the node
containing it or NULL */

int findInsId(InstrumentTree tree, char* instrument)
{
	TreeNode* node = findHelper(tree.root, instrument);
	if (node)
		return node->insId;
	else
		return -1;
}

TreeNode* findHelper(TreeNode* root, char* instrument)
{
	TreeNode* res;
	if (root == NULL)
		return NULL;
	else if (strcmp(root->instrument, instrument) == 0)
		return root;
	else
	{
		res = findHelper(root->left, instrument);
		if (res == NULL) //Not found in left side, go to right side
			return findHelper(root->right, instrument); //Return the result of the right side
		else
			return res;
	}
}


bool isEmptyList(MPIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}
void makeEmptyList(MPIList* lst)
{
	lst->head = lst->tail = NULL;
}

void insertDataToEndList(MPIList* lst, MusicianPriceInstrument data)
{
	LNODE* newTail;
	newTail = createNewListNode(data, NULL);
	insertNodeToEndList(lst, newTail);
}
LNODE* createNewListNode(MusicianPriceInstrument data, LNODE* next)
{
	LNODE* res;
	res = (LNODE*)malloc(sizeof(LNODE));
	res->data = data;
	res->next = next;
	return res;
}

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

////////////////////////////////////////////////////////////////////////////////////

bool isEmptyCList(CIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}
void makeEmptyCList(CIList* lst)
{
	lst->head = lst->tail = NULL;
}

void insertDataToEndCList(CIList* lst, ConcertInstrument data)
{
	LNODECI* newTail;
	newTail = createNewCListNode(data, NULL);
	insertNodeToEndCList(lst, newTail);
}
LNODECI* createNewCListNode(ConcertInstrument data, LNODECI* next)
{
	LNODECI* res;
	res = (LNODECI*)malloc(sizeof(LNODECI));
	res->data = data;
	res->next = next;
	return res;
}

void insertNodeToEndCIList(CIList* lst, LNODECI* tail)
{
	if (isEmptyCList(lst) == true)
		lst->head = lst->tail = tail;
	else
	{
		lst->tail->next = tail;
		lst->tail = tail;
	}
	tail->next = NULL;
}

////////////////////////////////////////////////////////////////////////////////////

//The function get a string and create a new tree node according to the data (the str) it gets and set an ID number.returns the node
TreeNode* createNewTNode(char* data, TreeNode* left, TreeNode* right)
{
	TreeNode* res;
	static int idCounter = 0;
	res = (TreeNode*)malloc(sizeof(TreeNode));
	res->instrument = data;
	res->insId = idCounter;
	res->left = left;
	res->right = right;
	idCounter++;
	return res;
}
//the function gets a file and a string.the function puts in the string a row from the file and return if it succeeded or not
char* changeRowFromFileToString(FILE* fp, BOOL* theFileIsNotFinished)
{
	char ch;
	int  phisySize = 2, logSize = 0;
	char* str = (char*)malloc(phisySize * sizeof(char));
	checkMemoryAllocation(str);
	ch = fgetc(fp);//get a char from the file
	while (ch != '\n' && ch != EOF)//while succeeded to get a char and it's not the end of the row
	{
		if (logSize == phisySize)//in case there isn't enough place-double the size of the str
		{
			phisySize = 2 * phisySize;
			str = realloc(str, phisySize * sizeof(char));
			checkMemoryReallocation(str);
		}
		str[logSize] = ch;
		logSize++;
		ch = fgetc(fp);//get a char from the file
	}
	str = realloc(str, (logSize+1) * sizeof(char));//remove unecessary place in the memory
	str[logSize] = '\0';
	
	if (ch == EOF)//if failed to get a char
		*theFileIsNotFinished = EOF;
	else
		*theFileIsNotFinished = SUCCEEDED;
	return str;
}

//check memory allocation
void checkMemoryAllocation(void* res)
{
	if (res == NULL)
	{
		printf("Memory allocation faild!\n");
		exit(1);
	}
}
void checkMemoryReallocation(void* res)
{
	if (res == NULL)
	{
		printf("Memory reallocation faild!\n");
		exit(1);
	}
}
void checkOpeningFile(FILE* f)
{
	if (f == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		exit(1);
	}
}
