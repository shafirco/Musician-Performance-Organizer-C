//shafir cohen 315995589
//amit kochavi 315409102

#ifndef _INST_HEADER_H
#define _INST_HEADER_H

#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NONSTDC_NO_DEPRECATE
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

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

//prototipes
TreeNode* createNewTNode(char* data, TreeNode* left, TreeNode* right);
char* changeRowFromFileToString(FILE* fp, BOOL* theFileIsNotFinished);
InstrumentTree buildInstrumentTree(FILE* instrumentsFile, int* size);
int findInsId(InstrumentTree tree, char* instrument);
TreeNode* findHelper(TreeNode* root, char* instrument);
char* findInstrumentName(InstrumentTree tree, unsigned short id);
TreeNode* findInstrumentNameHelper(TreeNode* root, unsigned short id);

#endif