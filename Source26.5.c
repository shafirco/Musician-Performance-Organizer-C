//#define _CRT_SECURE_NO_WARNINGS
//#define _CRT_NONSTDC_NO_DEPRECATE
//#include <stdio.h>
//#include <string.h>
//#include <stdbool.h>
//#include <stdlib.h>
//#include <math.h>
//
//#define TRUE 0
//#define SUCCEEDED 0
//#define BOOL int
//
//
//#define IMPORTANT 1
//#define NOT_IMPORTANT 0
//#define FIRST_SMALLER_THAN_SECOND -1
//#define FIRST_BIGGER_THAN_SECOND 1
//#define EVEN 0

//typedef struct treeNode
//{
//	char* instrument;
//	unsigned short insId;
//	struct treeNode* left;
//	struct treeNode* right;
//} TreeNode;
//
//typedef struct tree
//{
//	TreeNode* root;
//} InstrumentTree;
//
//
//
//
//typedef struct dinamicArrSizes
//{
//	int logSize;
//	int phisiSize;
//} DinamicArrSizes;
//
//
//
//typedef struct
//{
//	unsigned short insId;
//	float price;
//	bool flag;
//}MusicianPriceInstrument;
//
//typedef struct lnode
//{
//	MusicianPriceInstrument data;
//	struct lnode* next;
//} LNODE;
//
//typedef struct list
//{
//	LNODE* head;
//	LNODE* tail;
//}MPIList;
//
//typedef struct
//{
//	char** name;
//	MPIList instruments;
//	bool available;
//	int numOfNames;
//}Musician;

//typedef struct
//{
//	int day, month, year;
//	float hour;
//} Date;
//
//typedef struct
//{
//	int num;
//	int inst;
//	char importance;
//} ConcertInstrument;
//
//typedef struct LNODECI
//{
//	ConcertInstrument data;
//	struct LNODECI* next;
//}LNODECI;
//
//typedef struct
//{
//	LNODECI* head;
//	LNODECI* tail;
//}CIList;
//
//typedef struct
//{
//	Date date_of_concert;
//	char* name;
//	CIList instruments;
//} Concert;

//TreeNode* createNewTNode(char* data, TreeNode* left, TreeNode* right);
//char* changeRowFromFileToString(FILE* fp, BOOL* theFileIsNotFinished);
//InstrumentTree buildInstrumentTree(FILE* instrumentsFile, int* size);
//int findInsId(InstrumentTree tree, char* instrument);
//TreeNode* findHelper(TreeNode* root, char* instrument);


//void checkOpeningFile(FILE* f);
//void checkMemoryAllocation(void* res);
//void checkMemoryReallocation(void* res);


//Musician* buildArrOfMusicians(FILE* musicianFile, int* size, InstrumentTree instrumentTr);
//bool isEmptyList(MPIList* lst);
//void makeEmptyList(MPIList* lst);
//LNODE* createNewListNode(MusicianPriceInstrument data, LNODE* next);
//void insertDataToEndList(MPIList* lst, MusicianPriceInstrument data);
//void insertNodeToEndList(MPIList* lst, LNODE* tail);
//void getDataOfInstrument(MusicianPriceInstrument* dataOfInstrument, InstrumentTree instrumentTr, char* currToken, char* nextToken);
//void insertDataOfMus(Musician* musician, MPIList instrunemtList, int numOfNames);


//Musician*** buildArrOfArrsPointersToMusician(Musician* MusiciansGroup, int numOfInstruments, int numOfMusicians, DinamicArrSizes* sizesArr);


//bool isEmptyCList(CIList* lst);
//void makeEmptyCList(CIList* lst);
//void insertDataToEndCList(CIList* lst, ConcertInstrument data);
//LNODECI* createNewCListNode(ConcertInstrument data, LNODECI* next);
//void insertNodeToEndCIList(CIList* lst, LNODECI* tail);


//int comparePrice(void** musician1, void** musician2);
//void turnOnFlags(Musician** Musicians, unsigned short id, int sizeArr);
//void turnOnFlag(Musician* Musician, unsigned short id);
//void turnOffFlags(Musician** Musicians, int sizeArr);
//void turnOffFlag(Musician* Musician);
//Concert* getConcertData(InstrumentTree tr, bool* concertIsCanceled);



//char* findInstrumentName(InstrumentTree tree, unsigned short id);
//TreeNode* findInstrumentNameHelper(TreeNode* root, unsigned short id);
//float calculateHour(char* str);
//char* getFullNameMus(Musician* musician);
//char* fromFloatToStr(float num);
//char* getWordFromUser(bool* lineFinish);
//char* printInstrumentConcert(InstrumentTree tr, Musician*** MusiciansCollection, int sizeArr, Concert* concert, LNODECI* curr, unsigned short i);
//void printConcerts(InstrumentTree tr, Musician*** MusiciansCollection, DinamicArrSizes* sizesArr, Musician* MusiciansGroup, int numOfMusicians);
//void printCancelMessage(char* nameConcert);
//void printConcertData(Concert* concert, char* concertData);
//void strcatData(char* str, char* fullName, char* instrumentName, char* price);
//void printConcert(InstrumentTree tr, Musician*** MusiciansCollection, DinamicArrSizes* sizesArr, bool* readingConcertsIsFinished);

//void freeList(MPIList* lst);
//void freeMusician(Musician musician);
//void freeMusiciansGroup(Musician* MusiciansGroup, int numOfMusicians);
//void freeMusiciansCollection(Musician*** MusiciansCollection, int numOfInstruments);
//void freeTree(InstrumentTree* tr);
//void freeTreeHelper(TreeNode* root);

//void main(int argc, char** argv)
//{
//	int numOfInstruments, numOfMusicians;
//	Musician* MusiciansGroup;
//	Musician*** MusiciansCollection;
//	DinamicArrSizes* sizesArr;
//	FILE* instrumentsFile = fopen(argv[1], "r");
//	FILE* musiciansFile = fopen(argv[2], "r");
//	checkOpeningFile(instrumentsFile);
//	checkOpeningFile(musiciansFile);
//
//	InstrumentTree instrumentTr = buildInstrumentTree(instrumentsFile, &numOfInstruments);
//	fclose(instrumentsFile);
//
//	MusiciansGroup = buildArrOfMusicians(musiciansFile, &numOfMusicians, instrumentTr);
//	fclose(musiciansFile);
//
//	sizesArr = (DinamicArrSizes*)malloc(numOfInstruments * sizeof(DinamicArrSizes));
//	checkMemoryAllocation(sizesArr);
//	MusiciansCollection = buildArrOfArrsPointersToMusician(MusiciansGroup, numOfInstruments, numOfMusicians, sizesArr);
//
//	printConcerts(instrumentTr, MusiciansCollection, sizesArr, MusiciansGroup, numOfMusicians);
//
//	freeTree(&instrumentTr);
//	freeMusiciansGroup(MusiciansGroup, numOfMusicians);
//	freeMusiciansCollection(MusiciansCollection, numOfInstruments);
//	free(sizesArr);
//}

//void freeMusiciansCollection(Musician*** MusiciansCollection, int numOfInstruments)
//{
//	int i;
//	for (i = 0; i < numOfInstruments; i++)
//		free(MusiciansCollection[i]);
//	free(MusiciansCollection);
//}
//
///* free all memory of a tree */
//void freeTree(InstrumentTree* tr)
//{
//	freeTreeHelper(tr->root);
//	tr->root = NULL;
//}
//
//void freeTreeHelper(TreeNode* root)
//{
//	if (root == NULL)
//		return;
//	else
//	{
//		freeTreeHelper(root->left);
//		freeTreeHelper(root->right);
//		free(root->instrument);
//		free(root);
//	}
//}
//
//void freeList(MPIList* lst)
//{
//	LNODE* runner, * saver;
//	runner = lst->head;
//	while (runner != NULL)
//	{
//		saver = runner->next;
//		free(runner);
//		runner = saver;
//	}
//}
//
//void freeMusician(Musician musician)
//{
//	int i;
//	for (i = 0; i < musician.numOfNames; i++)
//		free(musician.name[i]);
//	freeList(&(musician.instruments));
//}
//
//void freeMusiciansGroup(Musician* MusiciansGroup,int numOfMusicians)
//{
//	int i;
//	for (i = 0; i < numOfMusicians; i++)
//		freeMusician(MusiciansGroup[i]);
//	free(MusiciansGroup);
//}

//void printConcerts(InstrumentTree tr, Musician*** MusiciansCollection, DinamicArrSizes* sizesArr, Musician* MusiciansGroup,int numOfMusicians)
//{
//	int i;
//	bool readingConcertsIsFinished = false;
//	while (readingConcertsIsFinished != true)	{
//		printConcert(tr, MusiciansCollection, sizesArr, &readingConcertsIsFinished);
//		for (i = 0; i < numOfMusicians; i++)
//			MusiciansGroup[i].available = false;
//	}
//}
//
//void printConcert(InstrumentTree tr, Musician*** MusiciansCollection, DinamicArrSizes* sizesArr,bool* readingConcertsIsFinished)
//{
//	bool concertIsCanceled = false;
//	Concert* concert = getConcertData(tr, &concertIsCanceled);
//	LNODECI* curr = NULL;
//	LNODE* runner = NULL;
//	char* tmpStr,*concertData = NULL;
//	unsigned short i;
//	int j, counter;
//	if (concert == NULL){
//		*readingConcertsIsFinished = true; return;	
//	}
//	if (concertIsCanceled == true){
//		printCancelMessage(concert->name); return;
//	}
//	else
//		curr = concert->instruments.head;
//	while (curr != NULL)
//	{
//		i = curr->data.inst;
//		if (curr->data.num <= sizesArr[i].logSize){
//			turnOnFlags(MusiciansCollection[i], i, sizesArr[i].logSize);
//			qsort(MusiciansCollection[i], sizesArr[i].logSize, sizeof(Musician*), comparePrice); ////we need to check if we did this sort
//			turnOffFlags(MusiciansCollection[i], sizesArr[i].logSize);
//			tmpStr = printInstrumentConcert(tr, MusiciansCollection, sizesArr[i].logSize, concert, curr, i);
//			if (tmpStr == NULL)
//				return;
//			if (concertData == NULL)
//				concertData = tmpStr;
//			else{
//				concertData = realloc(concertData, (strlen(concertData) + strlen(tmpStr) + 1) * sizeof(char));
//				checkMemoryReallocation(concertData);
//				strcat(concertData, tmpStr);
//			}
//		}
//		else{
//			printCancelMessage(concert->name);	return;
//		}
//		curr = curr->next;
//	}
//	printConcertData(concert, concertData);
//	free(concertData);
//}
//
//void printConcertData(Concert* concert, char* concertData)
//{
//	printf("%s %d %02d %d %.2f %s\n", concert->name, concert->date_of_concert.day, concert->date_of_concert.month, concert->date_of_concert.year, concert->date_of_concert.hour, concertData);
//}
//
//void printCancelMessage(char* nameConcert) {
//	printf("Could not find musicians for the concert %s\n", nameConcert);
//}
//
//char* getFullNameMus(Musician* musician)
//{
//	int i;
//	char* name = (char*)malloc(sizeof(char));
//	checkMemoryAllocation(name);
//	name[0] = 0;
//	for (i = 0; i < musician->numOfNames; i++)
//	{
//		name = realloc(name, (strlen(name) + strlen(musician->name[i]) + 3) * sizeof(char));
//		checkMemoryReallocation(name);
//		strcat(name, musician->name[i]);
//		strcat(name," ");
//	}
//	return name;
//}
//
//char* printInstrumentConcert(InstrumentTree tr, Musician*** MusiciansCollection, int sizeArr, Concert* concert, LNODECI* curr, unsigned short i)
//{
//	int counter = 0, j, k;
//	LNODE* runner;
//	char* fullName, * instrumentName, * price, * str;
//	str = (char*)malloc(sizeof(char));
//	checkMemoryAllocation(str);
//	int* indUnusedMusician = (int*)malloc((curr->data.num) * sizeof(int));
//	checkMemoryAllocation(indUnusedMusician);
//	str[0] = 0;
//	if (curr->data.importance == NOT_IMPORTANT)
//		j = 0;
//	else//important
//		j = sizeArr - 1;
//	while (counter < curr->data.num) {//while the number of musicians who chosen is not enough
//		if (MusiciansCollection[i][j]->available == false) {//if that musician was not already chosen 
//		//update that now he is chosen and will not be available next time         
//			indUnusedMusician[counter] = j;
//			runner = MusiciansCollection[i][j]->instruments.head;//set it to be a pointer to the first instument in the musician (in place j)list
//			while (runner->data.insId != i)//move the runner to the instrument we need
//				runner = runner->next;
//			instrumentName = findInstrumentName(tr, i);
//			fullName = getFullNameMus(MusiciansCollection[i][j]);
//			price = fromFloatToStr(runner->data.price);
//			str = realloc(str, (strlen(str) + strlen(fullName)+ strlen(instrumentName) + strlen(price) + 3) * sizeof(char)); /// price less
//			checkMemoryReallocation(str);
//			strcatData(str, fullName, instrumentName, price);
//			counter++;//update the number of chosen musicians
//		}//update the index j and print a message in needed:
//		if (curr->data.importance == NOT_IMPORTANT) 	{	
//			j++;
//			if (sizeArr - j+1 < curr->data.num - counter){
//				printCancelMessage(concert->name);	
//				free(indUnusedMusician);
//				return NULL;
//			}
//		}
//		else {
//			j--;
//			if (j + 1 < curr->data.num - counter) {
//				printCancelMessage(concert->name);
//				free(indUnusedMusician);
//				return NULL;
//			}
//		}
//	}
//	for (k = 0; k < counter; k++)
//		MusiciansCollection[i][indUnusedMusician[k]]->available = true;
//	free(indUnusedMusician);
//	return str;
//}
//
//void strcatData(char* str, char* fullName, char* instrumentName, char* price)
//{
//	strcat(str, fullName);//save the concert name in the string
//	free(fullName);
//	strcat(str, instrumentName);//save the instrument name in the string
//	strcat(str, " ");
//	strcat(str, price);
//	free(price);
//	strcat(str, " ");
//}
//char* fromFloatToStr(float num)
//{
//	int tmpNum = (int)num;
//	int counterD = 0;
//	int i, digit;
//	while (tmpNum > 0){
//		tmpNum /= 10;
//		counterD++;
//	}
//	tmpNum = (int)num;
//	char* str = (char*)malloc((counterD + 4) * sizeof(char));
//	checkMemoryAllocation(str);
//	for (i = 0; i < counterD; i++)
//	{
//		digit = (tmpNum / (int)pow((double)10, (double)(counterD - i - 1))) % 10;
//		str[i] = (char)('0' + digit);
//	}
//	str[i] = '.';
//	str[i + 1] = (char)('0' + (int)((num - (float)tmpNum) * 10));
//	str[i + 2] = (char)('0' + ((int)((num - (float)tmpNum) * 100) % 10));
//	str[i + 3] = 0;
//	return str;
//}
////get an instrument id and return its name. The function gets an id and a tree of instruments
//char* findInstrumentName(InstrumentTree tree, unsigned short id)
//{
//	TreeNode* node = findInstrumentNameHelper(tree.root, id);
//	if (node)
//		return node->instrument;
//	else
//		return NULL;
//}
////findInstrumentName's helper. Searching the id in the tree recursively.The function gets an id and a tree of instruments
//TreeNode* findInstrumentNameHelper(TreeNode* root, unsigned short id)
//{
//	TreeNode* res;
//	if (root == NULL)
//		return NULL;
//	else if (root->insId == id)
//		return root;
//	else
//	{
//		res = findInstrumentNameHelper(root->left, id);//search in the left side
//		if (res == NULL) //Not found in left side, go to right side
//			return findInstrumentNameHelper(root->right, id); //Return the result of the right side
//		else
//			return res;
//	}
//}
////get 2 pointers to pointer to musicians and return if the price of using the instrument is the same,bigger/smaller than the other musician (as an int type)
////according to the instument its flag is on.
//int comparePrice(void** musician1, void** musician2)
//{
//	Musician** a = (Musician**)musician1;
//	Musician** b = (Musician**)musician2;
//	LNODE* curr1 = (*a)->instruments.head;
//	LNODE* curr2 = (*b)->instruments.head;
//	while (curr1->data.flag != true)
//		curr1 = curr1->next;
//	while (curr2->data.flag != true)
//		curr2 = curr2->next;
//	if (curr1->data.price < curr2->data.price) return FIRST_SMALLER_THAN_SECOND;
//	else if (curr1->data.price > curr2->data.price) return FIRST_BIGGER_THAN_SECOND;
//	else return EVEN;
//}
////change the flag in every instrument in the arr according to the id the function gets (from false to true)
//void turnOnFlags(Musician** Musicians, unsigned short id, int sizeArr)
//{
//	int i;
//	for (i = 0; i < sizeArr; i++)
//		turnOnFlag(Musicians[i], id);
//}
////"turnOnFlags"'s helper. change the flag in the instrument in the list according to the id the function gets (from false to true)
//void turnOnFlag(Musician* Musician, unsigned short id)
//{
//	LNODE* curr = Musician->instruments.head;
//	while (curr->data.insId != id)
//		curr = curr->next;
//	curr->data.flag = true;
//}
////change the flag from "true" to "false" in every list of a musician from the musicians arr 
//void turnOffFlags(Musician** Musicians, int sizeArr)
//{
//	int i;
//	for (i = 0; i < sizeArr; i++)
//		turnOffFlag(Musicians[i]);
//}
////"turnOffFlags"'s helper. change the flag to "false" when it finds an instrument in the musician's list with a turned on flag ("true").(always one instrument)
//void turnOffFlag(Musician* Musician)
//{
//	LNODE* curr = Musician->instruments.head;
//	while (curr->data.flag == false)
//		curr = curr->next;
//	curr->data.flag = false;
//}
////get an instrumentTree tree. build concert (struct) according to the data from the user and return it
//Concert* getConcertData(InstrumentTree tr,bool* concertIsCanceled)
//{
//	bool lineIsFinished = false;
//	Concert* concert=(Concert*)malloc(sizeof(Concert));
//	checkMemoryAllocation(concert);
//	ConcertInstrument data;
//	concert->name = getWordFromUser(&lineIsFinished);
//	if (lineIsFinished == true)
//	{
//		free(concert);
//		return NULL;
//	}
//	concert->date_of_concert.day = atoi(getWordFromUser(&lineIsFinished));
//	concert->date_of_concert.month = atoi(getWordFromUser(&lineIsFinished));
//	concert->date_of_concert.year = atoi(getWordFromUser(&lineIsFinished));
//	concert->date_of_concert.hour =(float)calculateHour(getWordFromUser(&lineIsFinished));
//	makeEmptyCList(&(concert->instruments));
//	while (lineIsFinished == false )//get data from the user about the instuments till he finishes giving more info about that concert
//	{
//		data.inst = findInsId(tr, getWordFromUser(&lineIsFinished));
//		if (data.inst == -1)
//			*concertIsCanceled = true;
//		data.num = atoi(getWordFromUser(&lineIsFinished));
//		data.importance = atoi(getWordFromUser(&lineIsFinished));
//		insertDataToEndCList(&concert->instruments, data);
//	}
//	return concert;
//}
////the function get a hour in a string type and returns in as a float type
//float calculateHour(char* str)
//{
//	float hour, min;
//	hour = (float)atoi(strtok(str, ":"));
//	min = (float)atoi(strtok(NULL, "\0"));
//	hour += (min / 60);
//	return hour;
//}
////the function scan one word from the user and returns it. if the user typed enter-lineIsFinished will be "true"
//char* getWordFromUser(bool* lineIsFinished)
//{
//	int c;
//	int logSize = 0, phiSize = 1;
//	c = getchar();
//	char* line = (char*)malloc(sizeof(char));
//	checkMemoryAllocation(line);
//	while (c != ' ' && c != '\n')
//	{
//		if (logSize == phiSize)//check if there is enough place
//		{
//			phiSize *= 2;
//			line = realloc(line, phiSize * sizeof(char));
//			checkMemoryReallocation(line);
//		}
//		line[logSize] = (char)c;
//		logSize++;
//		c = getchar();
//	}
//	line = realloc(line, (logSize + 1) * sizeof(char));
//	checkMemoryReallocation(line);
//	line[logSize] = 0;
//	if (c == '\n')//if the user typed enter-lineIsFinished will be "true"
//		*lineIsFinished = true;
//	return line;
//}

//Musician*** buildArrOfArrsPointersToMusician(Musician* MusiciansGroup, int numOfInstruments, int numOfMusicians, DinamicArrSizes* sizesArr)
//{
//	int i, logSize, phiSize, currId;
//	LNODE* currNode;
//	Musician*** MusiciansCollection = (Musician***)malloc(numOfInstruments * sizeof(Musician**));
//	checkMemoryAllocation(MusiciansCollection);
//	for (i = 0; i < numOfInstruments; i++){
//		MusiciansCollection[i] = (Musician**)malloc(sizeof(Musician*));
//		checkMemoryAllocation(MusiciansCollection[i]);
//		sizesArr[i].logSize = 0;
//		sizesArr[i].phisiSize = 1;
//	}
//	for (i = 0; i < numOfMusicians; i++){
//		currNode = MusiciansGroup[i].instruments.head;
//		while (currNode != NULL){
//			currId = currNode->data.insId;
//			if (sizesArr[currId].logSize == sizesArr[currId].phisiSize)	{
//				sizesArr[currId].phisiSize *= 2;
//				MusiciansCollection[currId] = realloc(MusiciansCollection[currId], (sizesArr[currId].phisiSize) * sizeof(Musician*));
//				checkMemoryReallocation(MusiciansCollection[currId]);
//			}
//			MusiciansCollection[currId][(sizesArr[currId].logSize)] = (MusiciansGroup + i);
//			(sizesArr[currId].logSize)++;
//			currNode = currNode->next;
//		}
//	}
//	for (i = 0; i < numOfInstruments; i++)	{
//		MusiciansCollection[i] = realloc(MusiciansCollection[i], sizesArr[i].logSize * sizeof(Musician*));
//		checkMemoryReallocation(MusiciansCollection[i]);
//	}
//	return MusiciansCollection;
//}
//
//void getDataOfInstrument(MusicianPriceInstrument* dataOfInstrument,InstrumentTree instrumentTr,char* currToken,char* nextToken)
//{
//	dataOfInstrument->insId = findInsId(instrumentTr, currToken);//finds and saves it's ID
//	dataOfInstrument->price = atoi(nextToken);//saves it's price
//	dataOfInstrument->flag = false;
//}
//
//Musician* buildArrOfMusicians(FILE* musiciansFile, int* size, InstrumentTree instrumentTr)
//{
//	MPIList instrunemtList;
//	BOOL theFileIsNotFinished;
//	int phisySize = 2, numOfNames, numOfMusucsain = 0, sizeStr, phisySizeNames;
//	Musician* MusiciansGroup = (Musician*)malloc(phisySize * sizeof(Musician)); 
//	checkMemoryAllocation(MusiciansGroup);
//	char seps[] = " ,.;:?!-\t'()[]{}<>~_";
//	char* currToken, * nextToken, * rowFromMusFile;
//	MusicianPriceInstrument dataOfInstrument;
//	rowFromMusFile = changeRowFromFileToString(musiciansFile, &theFileIsNotFinished);
//	while (theFileIsNotFinished == TRUE)	{
//		currToken = strtok(rowFromMusFile, seps);//get first name
//		MusiciansGroup[numOfMusucsain].name = (char**)malloc(2 * sizeof(char*));
//		checkMemoryAllocation(MusiciansGroup[numOfMusucsain].name);
//		MusiciansGroup[numOfMusucsain].name[0] = strdup(currToken);
//		currToken = strtok(NULL, seps); //get second name (there are at least 2)
//		MusiciansGroup[numOfMusucsain].name[1] = strdup(currToken);
//		numOfNames = 2;
//		phisySizeNames = 2;
//		currToken = strtok(NULL, seps); //get the next word from the row
//		makeEmptyList(&instrunemtList);
//		while (currToken != NULL){
//			nextToken = strtok(NULL, seps);//get the next word
//			if (nextToken[0] >= '0' && nextToken[0] <= '9'){//if the next word is a number so the current word is an instrument and the next is it's price
//				getDataOfInstrument(&dataOfInstrument, instrumentTr, currToken, nextToken);
//				insertDataToEndList(&instrunemtList, dataOfInstrument);
//				currToken = strtok(NULL, seps);//get the next word
//			}
//			else{ //the next token is not a num and not a null- so it is a name
//				if (phisySizeNames == numOfNames)
//				{
//					phisySizeNames *= 2;
//					MusiciansGroup[numOfMusucsain].name = realloc(MusiciansGroup[numOfMusucsain].name, phisySizeNames * sizeof(char*));
//				}
//				MusiciansGroup[numOfMusucsain].name[numOfNames] = strdup(currToken);
//				numOfNames++;
//				currToken = nextToken;
//			}
//		}
//		MusiciansGroup[numOfMusucsain].name = realloc(MusiciansGroup[numOfMusucsain].name, numOfNames * sizeof(char*));
//		insertDataOfMus(MusiciansGroup + numOfMusucsain, instrunemtList, numOfNames);
//		numOfMusucsain++;
//		if (phisySize == numOfMusucsain){
//			phisySize *= 2;
//			MusiciansGroup = realloc(MusiciansGroup, phisySize * sizeof(Musician));
//			checkMemoryReallocation(MusiciansGroup);
//		}
//		//free(rowFromMusFile);
//		rowFromMusFile = changeRowFromFileToString(musiciansFile, &theFileIsNotFinished);
//	}
//	MusiciansGroup = realloc(MusiciansGroup, numOfMusucsain * sizeof(Musician));
//	checkMemoryReallocation(MusiciansGroup);
//	*size = numOfMusucsain;
//	return MusiciansGroup;
//}
//
//void insertDataOfMus(Musician* musician,MPIList instrunemtList,int numOfNames)
//{
//	musician->instruments = instrunemtList;
//	musician->available = false;
//	musician->numOfNames = numOfNames;
//}

////the function gets a file of instuments and according to that- builds a tree of instuments and return it
////the function saves the number of nodes in the tree
//InstrumentTree buildInstrumentTree(FILE* instrumentsFile, int* size)
//{
//	int numOfTNodes = 1;
//	TreeNode* runnerNode = NULL, * node = NULL;
//	InstrumentTree instrumentTr;
//	BOOL theFileIsNotFinished;
//	char* instrumentName = NULL;
//	instrumentName = changeRowFromFileToString(instrumentsFile, &theFileIsNotFinished);
//	instrumentTr.root = createNewTNode(instrumentName, NULL, NULL);
//	instrumentName = changeRowFromFileToString(instrumentsFile, &theFileIsNotFinished);
//	while (theFileIsNotFinished == TRUE){
//		runnerNode = instrumentTr.root;
//		while (runnerNode != NULL)	{
//			if (strcmp(instrumentName, runnerNode->instrument) > 0)//if runnerNode instrument's name is lexicographic smaller than instrumentName
//			{
//				node = runnerNode;
//				runnerNode = runnerNode->right;//search on the right side
//				if (runnerNode == NULL)
//					node->right = createNewTNode(instrumentName, NULL, NULL);
//			}
//			else{
//				node = runnerNode;
//				runnerNode = runnerNode->left;
//				if (runnerNode == NULL)
//					node->left = createNewTNode(instrumentName, NULL, NULL);
//			}
//		}
//		numOfTNodes++;
//		instrumentName = changeRowFromFileToString(instrumentsFile, &theFileIsNotFinished);;
//	}
//	*size = numOfTNodes;
//	return instrumentTr;
//}
//
///* Searching for a value in a binary tree - returning the address of the node
//containing it or NULL */
//
//int findInsId(InstrumentTree tree, char* instrument)
//{
//	TreeNode* node = findHelper(tree.root, instrument);
//	if (node)
//		return node->insId;
//	else
//		return -1;
//}
//
//TreeNode* findHelper(TreeNode* root, char* instrument)
//{
//	TreeNode* res;
//	if (root == NULL)
//		return NULL;
//	else if (strcmp(root->instrument, instrument) == 0)
//		return root;
//	else
//	{
//		res = findHelper(root->left, instrument);
//		if (res == NULL) //Not found in left side, go to right side
//			return findHelper(root->right, instrument); //Return the result of the right side
//		else
//			return res;
//	}
//}
////gets a list and returns if it's empty or not
//bool isEmptyList(MPIList* lst)
//{
//	if (lst->head == NULL)
//		return true;
//	else
//		return false;
//}
////gets a list and makes it empty
//void makeEmptyList(MPIList* lst)
//{
//	lst->head = lst->tail = NULL;
//}
//
//void insertDataToEndList(MPIList* lst, MusicianPriceInstrument data)
//{
//	LNODE* newTail;
//	newTail = createNewListNode(data, NULL);
//	insertNodeToEndList(lst, newTail);
//}
//LNODE* createNewListNode(MusicianPriceInstrument data, LNODE* next)
//{
//	LNODE* res;
//	res = (LNODE*)malloc(sizeof(LNODE));
//	checkMemoryAllocation(res);
//	res->data = data;
//	res->next = next;
//	return res;
//}
//
//void insertNodeToEndList(MPIList* lst, LNODE* tail)
//{
//	if (isEmptyList(lst) == true)
//		lst->head = lst->tail = tail;
//	else
//	{
//		lst->tail->next = tail;
//		lst->tail = tail;
//	}
//	tail->next = NULL;
//}

////////////////////////////////////////////////////////////////////////////////////

//bool isEmptyCList(CIList* lst)
//{
//	if (lst->head == NULL)
//		return true;
//	else
//		return false;
//}
//void makeEmptyCList(CIList* lst)
//{
//	lst->head = lst->tail = NULL;
//}
//
//void insertDataToEndCList(CIList* lst, ConcertInstrument data)
//{
//	LNODECI* newTail;
//	newTail = createNewCListNode(data, NULL);
//	insertNodeToEndCIList(lst, newTail);
//}
//LNODECI* createNewCListNode(ConcertInstrument data, LNODECI* next)
//{
//	LNODECI* res;
//	res = (LNODECI*)malloc(sizeof(LNODECI));
//	checkMemoryAllocation(res);
//	res->data = data;
//	res->next = next;
//	return res;
//}
//
//void insertNodeToEndCIList(CIList* lst, LNODECI* tail)
//{
//	if (isEmptyCList(lst) == true)
//		lst->head = lst->tail = tail;
//	else
//	{
//		lst->tail->next = tail;
//		lst->tail = tail;
//	}
//	tail->next = NULL;
//}

////////////////////////////////////////////////////////////////////////////////////

////The function get a string and create a new tree node according to the data (the str) it gets and set an ID number.returns the node
//TreeNode* createNewTNode(char* data, TreeNode* left, TreeNode* right)
//{
//	TreeNode* res;
//	static int idCounter = 0;
//	res = (TreeNode*)malloc(sizeof(TreeNode));
//	checkMemoryAllocation(res);
//	res->instrument = data;
//	res->insId = idCounter;
//	res->left = left;
//	res->right = right;
//	idCounter++;
//	return res;
//}
////the function gets a file and a string.the function puts in the string a row from the file and return if it succeeded or not
//char* changeRowFromFileToString(FILE* fp, BOOL* theFileIsNotFinished)
//{
//	char ch;
//	int  phisySize = 2, logSize = 0;
//	char* str = (char*)malloc(phisySize * sizeof(char));
//	checkMemoryAllocation(str);
//	ch = fgetc(fp);//get a char from the file
//	while (ch != '\n' && ch != EOF)//while succeeded to get a char and it's not the end of the row
//	{
//		if (logSize == phisySize)//in case there isn't enough place-double the size of the str
//		{
//			phisySize = 2 * phisySize;
//			str = realloc(str, phisySize * sizeof(char));
//			checkMemoryReallocation(str);
//		}
//		str[logSize] = ch;
//		logSize++;
//		ch = fgetc(fp);//get a char from the file
//	}
//	str = realloc(str, (logSize + 1) * sizeof(char));//remove unecessary place in the memory
//	checkMemoryReallocation(str);
//	str[logSize] = '\0';
//	if (ch == EOF)//if failed to get a char
//		*theFileIsNotFinished = EOF;
//	else
//		*theFileIsNotFinished = SUCCEEDED;
//	return str;
//}
////check memory allocation
//void checkMemoryAllocation(void* res)
//{
//	if (res == NULL)
//	{
//		printf("Memory allocation faild!\n");
//		exit(1);
//	}
//}
//void checkMemoryReallocation(void* res)
//{
//	if (res == NULL)
//	{
//		printf("Memory reallocation faild!\n");
//		exit(1);
//	}
//}
//void checkOpeningFile(FILE* f)
//{
//	if (f == NULL)
//	{
//		printf("Failed opening the file. Exiting!\n");
//		exit(1);
//	}
//}
