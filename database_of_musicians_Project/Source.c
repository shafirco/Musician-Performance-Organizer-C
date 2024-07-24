#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>



typedef struct treeNode {
	char* instrument;
	unsigned short insId;
	struct treeNode* left;
	struct treeNode* right;
} TreeNode;

typedef struct tree {
	TreeNode* root;
} InstrumentTree;



typedef struct
{
	unsigned short insId;
	float price;
}MusicianPriceInstrument;

typedef struct lnode {
	MusicianPriceInstrument data;
	struct lnode* next;
} LNODE;

typedef struct list {
	LNODE* head;
	LNODE* tail;
}MPIList;

typedef struct
{
	char** name;
	MPIList instruments;
}Musician;





TreeNode* createNewTNode(int data, TreeNode* left, TreeNode* right);
int findInsId(InstrumentTree tree, char* instrument);
TreeNode* findHelper(TreeNode* root, char* instrument);

void main(FILE* instruments, FILE* musicians)
{
	FILE* fp = fopen(instruments, "r");
	FILE* fpM = fopen(musicians, "r");
	if (fp == NULL || fp == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		exit(1);
	}

	TreeNode* runnerNode = NULL;
	InstrumentTree treeInstrument;

	int theFileNotFinish;
	char* strHelper;
	theFileNotFinish = arrayToString(fp, strHelper);
	treeInstrument.root = createNewTNode(strHelper, NULL, NULL);

	strHelper = NULL;
	theFileNotFinish = arrayToString(fp, strHelper);

	while (theFileNotFinish == 0)
	{

		runnerNode = treeInstrument.root;
		while (runnerNode != NULL)
		{
			if (strcmp(strHelper, runnerNode->instrument) > 0)
				runnerNode = runnerNode->right;
			else
				runnerNode = runnerNode->left;
		}
		runnerNode = createNewTNode(strHelper, NULL, NULL);

		strHelper = NULL;
		theFileNotFinish = arrayToString(fp, strHelper);
	}

	///////fpM

	Musician* MusiciansGroup;
	MusiciansGroup = (Musician*)malloc(sizeof (Musician)*2);
	int logiSizeM = 0;
	int phisySizeM = 2;
	char seps[] = " ,.;:?!-\t'()[]{}<>~_";
	char* currToken, *nextToken;
	strHelper = NULL;
	theFileNotFinish = arrayToString(fpM, strHelper);
	int numOfNames, numOfMusucsain = 0;
	int sizeStr;
	MusicianPriceInstrument dataM;
	while (theFileNotFinish == 0)
	{
		numOfNames = 0;
		currToken = strtok(strHelper, seps);
		MusiciansGroup[numOfMusucsain].name[numOfNames] = strdup(currToken);
		numOfNames++;

		currToken = strtok(NULL, seps);
		MusiciansGroup[numOfMusucsain].name[numOfNames] = strdup(currToken);
		numOfNames++;

		currToken = strtok(NULL, seps);
		MPIList instrunemtListHelper;
		makeEmptyList(&instrunemtListHelper);
		while (currToken != NULL)
		{
			nextToken = strtok(NULL, seps);
			if (nextToken != NULL)
			{
				if (nextToken[0] >= '0' && nextToken[0] <= '9')
				{
					dataM.insId = findInsId(treeInstrument, currToken);
					dataM.price = fromStringToNum(nextToken);

					insertDataToEndList(&instrunemtListHelper, dataM);

					//free(currToken);
					//free(nextToken);

					currToken = strtok(NULL, seps);
				}
			}
			else //not a num and not null
			{
				MusiciansGroup[numOfMusucsain].name[numOfNames] = strdup(currToken);
				numOfNames++;

				currToken = nextToken;
			}

		}



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

int arrayToString(FILE* fp, char* str)
{
	str = (char*)malloc(sizeof 2 * (char));
	int  phisysize = 2, logSize = 0;
	//alloc
	char ch = fgetc(fp);
	while (ch != '\n' && ch != EOF)
	{
		if (logSize == phisysize)
		{
			phisysize = 2 * phisysize;
			str = realloc(str, phisysize);
		}
		str[logSize] = ch;
		logSize++;
		ch = fgetc(fp);
	}

	str = realloc(str, logSize);
	str[logSize] = '\0';
	if (ch == EOF)
		return EOF;
	else
		return 0;
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
