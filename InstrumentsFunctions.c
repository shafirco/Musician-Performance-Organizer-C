//shafir cohen 315995589
//amit kochavi 315409102

#include "InstrumentsHeader.h"
#include "CheckingHeader.h"

//The function get a string and create a new tree node according to the data (the str) it gets and set an ID number.returns the node
TreeNode* createNewTNode(char* data, TreeNode* left, TreeNode* right)
{
	TreeNode* res;
	static int idCounter = 0;
	res = (TreeNode*)malloc(sizeof(TreeNode));
	checkMemoryAllocation(res);
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
	str = realloc(str, (logSize + 1) * sizeof(char));//remove unecessary place in the memory
	checkMemoryReallocation(str);
	str[logSize] = '\0';
	if (ch == EOF)//if failed to get a char
		*theFileIsNotFinished = EOF;
	else
		*theFileIsNotFinished = SUCCEEDED;
	return str;
}

//get an instrument id and return its name. The function gets an id and a tree of instruments
char* findInstrumentName(InstrumentTree tree, unsigned short id)
{
	TreeNode* node = findInstrumentNameHelper(tree.root, id);
	if (node)
		return node->instrument;
	else
		return NULL;
}
//findInstrumentName's helper. Searching the id in the tree recursively.The function gets an id and a tree of instruments
TreeNode* findInstrumentNameHelper(TreeNode* root, unsigned short id)
{
	TreeNode* res;
	if (root == NULL)
		return NULL;
	else if (root->insId == id)
		return root;
	else
	{
		res = findInstrumentNameHelper(root->left, id);//search in the left side
		if (res == NULL) //Not found in left side, go to right side
			return findInstrumentNameHelper(root->right, id); //Return the result of the right side
		else
			return res;
	}
}

//the function gets a file of instuments and according to that- builds a tree of instuments and return it
//the function saves the number of nodes in the tree
InstrumentTree buildInstrumentTree(FILE* instrumentsFile, int* size)
{
	int numOfTNodes = 1;
	TreeNode* runnerNode = NULL, * node = NULL;
	InstrumentTree instrumentTr;
	BOOL theFileIsNotFinished;
	char* instrumentName = NULL;
	instrumentName = changeRowFromFileToString(instrumentsFile, &theFileIsNotFinished);
	instrumentTr.root = createNewTNode(instrumentName, NULL, NULL);
	instrumentName = changeRowFromFileToString(instrumentsFile, &theFileIsNotFinished);
	while (theFileIsNotFinished == TRUE) {
		runnerNode = instrumentTr.root;
		while (runnerNode != NULL) {
			if (strcmp(instrumentName, runnerNode->instrument) > 0)//if runnerNode instrument's name is lexicographic smaller than instrumentName
			{
				node = runnerNode;
				runnerNode = runnerNode->right;//search on the right side
				if (runnerNode == NULL)
					node->right = createNewTNode(instrumentName, NULL, NULL);
			}
			else {
				node = runnerNode;
				runnerNode = runnerNode->left;
				if (runnerNode == NULL)
					node->left = createNewTNode(instrumentName, NULL, NULL);
			}
		}
		numOfTNodes++;
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