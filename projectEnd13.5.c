#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define TRUE 0
#define FALSE 1
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

typedef struct
{
	unsigned short insId;
	float price;
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
}Musician;

LNODE* createNewListNode(MusicianPriceInstrument data, LNODE* next);
void insertDataToEndList(MPIList* lst, MusicianPriceInstrument data);

void insertNodeToEndList(MPIList* lst, LNODE* tail);
bool isEmptyList(MPIList* lst);
void makeEmptyList(MPIList* lst);
TreeNode* createNewTNode(char* data, TreeNode* left, TreeNode* right);
BOOL changeRowFromFileToString(FILE* fp, char* str);
TreeNode* findHelper(TreeNode* root, char* instrument);
int findInsId(InstrumentTree tree, char* instrument);
TreeNode* findHelper(TreeNode* root, char* instrument);
int fromStringToNum(char* str);
void checkMemoryAllocation(void* res);
void checkMemoryReallocation(void* res);
void checkOpeningFile(FILE* f);
void freeList(MPIList* lst);
void freeTree(InstrumentTree tr);
void freeTreeHelper(TreeNode* tr);
//TreeNode* createNewTNode(int data, TreeNode* left, TreeNode* right);

void main(FILE* instruments, FILE* musicians)
{
	FILE* instrumentsFile = fopen(instruments, "r");
	FILE* musiciansFile = fopen(musicians, "r");
	checkOpeningFile(instrumentsFile);
	checkOpeningFile(musiciansFile);

	TreeNode* runnerNode = NULL;
	InstrumentTree instrumentTr;

	BOOL theFileIsNotFinished;
	char* instrumentName;
	theFileIsNotFinished = changeRowFromFileToString(instrumentsFile, instrumentName);
	//check theFileIsNotFinished value??
	instrumentTr.root = createNewTNode(instrumentName, NULL, NULL);

	int numOfTNodes = 1;
	instrumentName = NULL;
	theFileIsNotFinished = changeRowFromFileToString(instrumentsFile, instrumentName);


	while (theFileIsNotFinished == TRUE)/// (q1)
	{
		runnerNode = instrumentTr.root;
		while (runnerNode != NULL)
		{
			if (strcmp(instrumentName, runnerNode->instrument) > 0)//if runnerNode instrument's name is lexicographic smaller than instrumentName
				runnerNode = runnerNode->right;//search on the right side
			else
				runnerNode = runnerNode->left;
		}
		runnerNode = createNewTNode(instrumentName, NULL, NULL);
		numOfTNodes++;
		instrumentName = NULL;//??
		theFileIsNotFinished = changeRowFromFileToString(instrumentsFile, instrumentName);
	}

	///////fpM
	int phisySize = 2, numOfNames, numOfMusucsain = 0, sizeStr;
	Musician* MusiciansGroup;
	MusiciansGroup = (Musician*)malloc(phisySize*sizeof(Musician));
	char seps[] = " ,.;:?!-\t'()[]{}<>~_";
	char* currToken, *nextToken, *rowFromMusFile;
	MusicianPriceInstrument dataOfInstrument;
	rowFromMusFile = NULL;//??
	theFileIsNotFinished = changeRowFromFileToString(musiciansFile, rowFromMusFile);
	while (theFileIsNotFinished == TRUE)
	{
		numOfNames = 0;//count how many names there are for a musician
		//get first name
		currToken = strtok(rowFromMusFile, seps);
		MusiciansGroup[numOfMusucsain].name[numOfNames] = strdup(currToken);
		numOfNames++;
		//get second name (there are at least 2)
		currToken = strtok(NULL, seps);
		MusiciansGroup[numOfMusucsain].name[numOfNames] = strdup(currToken);
		numOfNames++;
		//get the next word from the row
		currToken = strtok(NULL, seps);
		MPIList instrunemtList;//??
		makeEmptyList(&instrunemtList);
		while (currToken != NULL)
		{
			nextToken = strtok(NULL, seps);//get the next word
			if (nextToken != NULL)
			{
				if (nextToken[0] >= '0' && nextToken[0] <= '9')//if the next word is a number so the current word is an instrument and the next is it's price
				{
					dataOfInstrument.insId = findInsId(instrumentTr, currToken);//finds and saves it's ID
					dataOfInstrument.price = fromStringToNum(nextToken);//saves it's price

					insertDataToEndList(&instrunemtList, dataOfInstrument);

					//free(currToken);
					//free(nextToken);

					currToken = strtok(NULL, seps);//get the next word
				}
			}
			else //the next token is not a num and not a null- so it is a name
			{
				MusiciansGroup[numOfMusucsain].name[numOfNames] = strdup(currToken);
				numOfNames++;

				currToken = nextToken;
			}
			numOfMusucsain++;
			if (phisySize == numOfMusucsain)
			{
				phisySize *= 2;
				MusiciansGroup = (Musician*)realloc(MusiciansGroup, phisySize * sizeof(Musician));
			}
			
		}
	}
	Musician*** MusiciansCollection = (Musician***)malloc(numOfTNodes * sizeof(Musician**));

}
Musician*** BuildArrOfMusiciansCollection(Musician** Musicians, int size)
{
	Musician** instrument;
	int i, logiSize = 0, phisySize = 2;
	instrument = (Musician**)malloc(sizeof(Musician*));

	for (i = 0; i <size;i++ )
	{

	}
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
BOOL changeRowFromFileToString(FILE* fp, char* str)
{
	char ch;
	int  phisySize = 2, logSize = 0;
	str = (char*)malloc(phisySize * sizeof(char));
	checkMemoryAllocation(str);
	ch = fgetc(fp);//get a char from the file
	while (ch != '\n' && ch != EOF)//while succeeded to get a char and it's not the end of the row
	{
		if (logSize == phisySize)//in case there isn't enough place-double the size of the str
		{
			phisySize = 2 * phisySize;
			str = (char*)realloc(str, phisySize * sizeof(char));
			checkMemoryReallocation(str);
		}
		str[logSize] = ch;
		logSize++;
		ch = fgetc(fp);//get a char from the file
	}
	str[logSize] = '\0';
	str = (char* )realloc(str, logSize * sizeof(char));//remove unecessary place in the memory
	if (ch == EOF)//if failed to get a char
		return EOF;
	else
		return SUCCEEDED;
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


int fromStringToNum(char* str)
{
	int i, j;
	int size = strlen(str);
	int num = 0;
	for (i = 0, j = 1; i < size; j *= 10, i++)
		num += ('0' - str[size - 1 - i]) * j;
	return num;
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
//free list
void freeList(MPIList* lst)
{
	LNODE* tmp, * curr;
	curr = lst->head;
	while (curr != NULL)
	{
		tmp = curr->next;
		free(curr);
		curr = tmp;
	}
}
/* free all memory of a tree */
void freeTree(InstrumentTree tr)
{
	freeTreeHelper(tr.root);
	tr.root = NULL;
}

void freeTreeHelper(TreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		freeTreeHelper(root->left);
		freeTreeHelper(root->right);
		free(root);
	}
}