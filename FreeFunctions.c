//shafir cohen 315995589
//amit kochavi 315409102

#include "FreeHeader.h"

//The function free the MusiciansCollection array
void freeMusiciansCollection(Musician*** MusiciansCollection, int numOfInstruments)
{
	int i;
	for (i = 0; i < numOfInstruments; i++)
		free(MusiciansCollection[i]);
	free(MusiciansCollection);
}

/* free all memory of a tree */
void freeTree(InstrumentTree* tr)
{
	freeTreeHelper(tr->root);
	tr->root = NULL;
}

void freeTreeHelper(TreeNode* root)
{
	if (root == NULL)
		return;
	else
	{
		freeTreeHelper(root->left);
		freeTreeHelper(root->right);
		free(root->instrument);
		free(root);
	}
}

//free all memory of a MPIList
void freeMPIList(MPIList* lst)
{
	LNODE* runner, * saver;
	runner = lst->head;
	while (runner != NULL)
	{
		saver = runner->next;
		free(runner);
		runner = saver;
	}
}
//free all memory of a CIList
void freeCIList(CIList* lst)
{
	LNODECI* runner, * saver;
	runner = lst->head;
	while (runner != NULL)
	{
		saver = runner->next;
		free(runner);
		runner = saver;
	}
}
//The function free one musician 
void freeMusician(Musician musician)
{
	int i;
	for (i = 0; i < musician.numOfNames; i++)
		free(musician.name[i]);
	freeMPIList(&(musician.instruments));
}
//The function free MusiciansGroup array 
void freeMusiciansGroup(Musician* MusiciansGroup, int numOfMusicians)
{
	int i;
	for (i = 0; i < numOfMusicians; i++)
		freeMusician(MusiciansGroup[i]);
	free(MusiciansGroup);
}