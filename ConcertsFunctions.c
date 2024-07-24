//shafir cohen 315995589
//amit kochavi 315409102

#include "ConcertsHeader.h"
#include "FreeHeader.h"
#include "CheckingHeader.h"


//The function gets concerts data and prints the possible concerts
void printConcerts(InstrumentTree tr, Musician*** MusiciansCollection, DinamicArrSizes* sizesArr, Musician* MusiciansGroup, int numOfMusicians)
{
	int i;
	bool readingConcertsIsFinished = false;
	while (readingConcertsIsFinished != true) {
		printConcert(tr, MusiciansCollection, sizesArr, &readingConcertsIsFinished);
		for (i = 0; i < numOfMusicians; i++)
			MusiciansGroup[i].available = false;
	}
}
////The function gets concert data and prints the concert if the concert is possible
void printConcert(InstrumentTree tr, Musician*** MusiciansCollection, DinamicArrSizes* sizesArr, bool* readingConcertsIsFinished)
{
	bool concertIsCanceled = false;
	Concert* concert = getConcertData(tr, &concertIsCanceled);
	LNODECI* curr = NULL;
	LNODE* runner = NULL;
	char* tmpStr, * concertData = NULL;
	unsigned short i;
	int j, counter;
	if (concert == NULL) {
		*readingConcertsIsFinished = true; return;
	}
	if (concertIsCanceled == true) {
		printCancelMessage(concert->name); return;
	}
	else
		curr = concert->instruments.head;
	while (curr != NULL)
	{
		i = curr->data.inst;
		if (curr->data.num <= sizesArr[i].logSize) {
			turnOnFlags(MusiciansCollection[i], i, sizesArr[i].logSize);
			qsort(MusiciansCollection[i], sizesArr[i].logSize, sizeof(Musician*), comparePrice); ////we need to check if we did this sort
			turnOffFlags(MusiciansCollection[i], sizesArr[i].logSize);
			tmpStr = printInstrumentConcert(tr, MusiciansCollection, sizesArr[i].logSize, concert, curr, i);
			if (tmpStr == NULL)
				return;
			if (concertData == NULL)
				concertData = tmpStr;
			else {
				concertData = realloc(concertData, (strlen(concertData) + strlen(tmpStr) + 1) * sizeof(char));
				checkMemoryReallocation(concertData);
				strcat(concertData, tmpStr);
			}
		}
		else {
			printCancelMessage(concert->name);	return;
		}
		curr = curr->next;
	}
	printConcertData(concert, concertData);
	free(concertData);
	freeCIList(&concert->instruments);
	free(concert);
}
////The function gets concert data and prints it
void printConcertData(Concert* concert, char* concertData)
{
	printf("%s %d %02d %d %.2f %s\n", concert->name, concert->date_of_concert.day, concert->date_of_concert.month, concert->date_of_concert.year, concert->date_of_concert.hour, concertData);
}
//The function print message about impossible concert 
void printCancelMessage(char* nameConcert) {
	printf("Could not find musicians for the concert %s\n", nameConcert);
}
//The function gets a musician and return his full name as str type  
char* getFullNameMus(Musician* musician)
{
	int i;
	char* name = (char*)malloc(sizeof(char));
	checkMemoryAllocation(name);
	name[0] = 0;
	for (i = 0; i < musician->numOfNames; i++)
	{
		name = realloc(name, (strlen(name) + strlen(musician->name[i]) + 3) * sizeof(char));
		checkMemoryReallocation(name);
		strcat(name, musician->name[i]);
		strcat(name, " ");
	}
	return name;
}
/////The function returns str of all the data of the instruments and the musician in the concert
char* printInstrumentConcert(InstrumentTree tr, Musician*** MusiciansCollection, int sizeArr, Concert* concert, LNODECI* curr, unsigned short i)
{
	int counter = 0, j, k;
	LNODE* runner;
	char* fullName, * instrumentName, * price, * str;
	str = (char*)malloc(sizeof(char));
	checkMemoryAllocation(str);
	int* indUnusedMusician = (int*)malloc((curr->data.num) * sizeof(int));
	checkMemoryAllocation(indUnusedMusician);
	str[0] = 0;
	if (curr->data.importance == NOT_IMPORTANT)
		j = 0;
	else//important
		j = sizeArr - 1;
	while (counter < curr->data.num) {//while the number of musicians who chosen is not enough
		if (MusiciansCollection[i][j]->available == false) {//if that musician was not already chosen 
		//update that now he is chosen and will not be available next time         
			indUnusedMusician[counter] = j;
			runner = MusiciansCollection[i][j]->instruments.head;//set it to be a pointer to the first instument in the musician (in place j)list
			while (runner->data.insId != i)//move the runner to the instrument we need
				runner = runner->next;
			instrumentName = findInstrumentName(tr, i);
			fullName = getFullNameMus(MusiciansCollection[i][j]);
			price = fromFloatToStr(runner->data.price);
			str = realloc(str, (strlen(str) + strlen(fullName) + strlen(instrumentName) + strlen(price) + 3) * sizeof(char)); /// price less
			checkMemoryReallocation(str);
			strcatData(str, fullName, instrumentName, price);
			counter++;//update the number of chosen musicians
		}//update the index j and print a message in needed:
		if (curr->data.importance == NOT_IMPORTANT) {
			j++;
			if (sizeArr - j  < curr->data.num - counter) {
				printCancelMessage(concert->name);
				free(indUnusedMusician);
				return NULL;
			}
		}
		else {
			j--;
			if (j + 1 < curr->data.num - counter) {
				printCancelMessage(concert->name);
				free(indUnusedMusician);
				return NULL;
			}
		}
	}
	for (k = 0; k < counter; k++)
		MusiciansCollection[i][indUnusedMusician[k]]->available = true;
	free(indUnusedMusician);
	return str;
}
//the function gets strs of fullname, instrumentName and price, and strcat them together
void strcatData(char* str, char* fullName, char* instrumentName, char* price)
{
	strcat(str, fullName);//save the concert name in the string
	free(fullName);
	strcat(str, instrumentName);//save the instrument name in the string
	strcat(str, " ");
	strcat(str, price);
	free(price);
	strcat(str, " ");
}
//the function gets a float num and returns this num as a str
char* fromFloatToStr(float num)
{
	int tmpNum = (int)num;
	int counterD = 0;
	int i, digit;
	while (tmpNum > 0) {
		tmpNum /= 10;
		counterD++;
	}
	tmpNum = (int)num;
	char* str = (char*)malloc((counterD + 4) * sizeof(char));
	checkMemoryAllocation(str);
	for (i = 0; i < counterD; i++)
	{
		digit = (tmpNum / (int)pow((double)10, (double)(counterD - i - 1))) % 10;
		str[i] = (char)('0' + digit);
	}
	str[i] = '.';
	str[i + 1] = (char)('0' + (int)((num - (float)tmpNum) * 10));
	str[i + 2] = (char)('0' + ((int)((num - (float)tmpNum) * 100) % 10));
	str[i + 3] = 0;
	return str;
}
//get 2 pointers to pointer to musicians and return if the price of using the instrument is the same,bigger/smaller than the other musician (as an int type)
//according to the instument its flag is on.
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
	if (curr1->data.price < curr2->data.price) return FIRST_SMALLER_THAN_SECOND;
	else if (curr1->data.price > curr2->data.price) return FIRST_BIGGER_THAN_SECOND;
	else return EVEN;
}
//change the flag in every instrument in the arr according to the id the function gets (from false to true)
void turnOnFlags(Musician** Musicians, unsigned short id, int sizeArr)
{
	int i;
	for (i = 0; i < sizeArr; i++)
		turnOnFlag(Musicians[i], id);
}
//"turnOnFlags"'s helper. change the flag in the instrument in the list according to the id the function gets (from false to true)
void turnOnFlag(Musician* Musician, unsigned short id)
{
	LNODE* curr = Musician->instruments.head;
	while (curr->data.insId != id)
		curr = curr->next;
	curr->data.flag = true;
}
//change the flag from "true" to "false" in every list of a musician from the musicians arr 
void turnOffFlags(Musician** Musicians, int sizeArr)
{
	int i;
	for (i = 0; i < sizeArr; i++)
		turnOffFlag(Musicians[i]);
}
//"turnOffFlags"'s helper. change the flag to "false" when it finds an instrument in the musician's list with a turned on flag ("true").(always one instrument)
void turnOffFlag(Musician* Musician)
{
	LNODE* curr = Musician->instruments.head;
	while (curr->data.flag == false)
		curr = curr->next;
	curr->data.flag = false;
}
//get an instrumentTree tree. build concert (struct) according to the data from the user and return it
Concert* getConcertData(InstrumentTree tr, bool* concertIsCanceled)
{
	bool lineIsFinished = false;
	Concert* concert = (Concert*)malloc(sizeof(Concert));
	checkMemoryAllocation(concert);
	ConcertInstrument data;
	concert->name = getWordFromUser(&lineIsFinished);
	if (lineIsFinished == true)
	{
		free(concert);
		return NULL;
	}
	concert->date_of_concert.day = atoi(getWordFromUser(&lineIsFinished));
	concert->date_of_concert.month = atoi(getWordFromUser(&lineIsFinished));
	concert->date_of_concert.year = atoi(getWordFromUser(&lineIsFinished));
	concert->date_of_concert.hour = (float)calculateHour(getWordFromUser(&lineIsFinished));
	makeEmptyCList(&(concert->instruments));
	while (lineIsFinished == false)//get data from the user about the instuments till he finishes giving more info about that concert
	{
		data.inst = findInsId(tr, getWordFromUser(&lineIsFinished));
		if (data.inst == -1)
			*concertIsCanceled = true;
		data.num = atoi(getWordFromUser(&lineIsFinished));
		data.importance = atoi(getWordFromUser(&lineIsFinished));
		insertDataToEndCList(&concert->instruments, data);
	}
	return concert;
}
//the function get a hour in a string type and returns in as a float type
float calculateHour(char* str)
{
	float hour, min;
	hour = (float)atoi(strtok(str, ":"));
	min = (float)atoi(strtok(NULL, "\0"));
	hour += (min / 60);
	return hour;
}
//the function scan one word from the user and returns it. if the user typed enter-lineIsFinished will be "true"
char* getWordFromUser(bool* lineIsFinished)
{
	int c;
	int logSize = 0, phiSize = 1;
	c = getchar();
	char* line = (char*)malloc(sizeof(char));
	checkMemoryAllocation(line);
	while (c != ' ' && c != '\n')
	{
		if (logSize == phiSize)//check if there is enough place
		{
			phiSize *= 2;
			line = realloc(line, phiSize * sizeof(char));
			checkMemoryReallocation(line);
		}
		line[logSize] = (char)c;
		logSize++;
		c = getchar();
	}
	line = realloc(line, (logSize + 1) * sizeof(char));
	checkMemoryReallocation(line);
	line[logSize] = 0;
	if (c == '\n')//if the user typed enter-lineIsFinished will be "true"
		*lineIsFinished = true;
	return line;
}
//gets a CIList and returns if it is empty or not
bool isEmptyCList(CIList* lst)
{
	if (lst->head == NULL)
		return true;
	else
		return false;
}
//gets a CIList and makes it empty
void makeEmptyCList(CIList* lst)
{
	lst->head = lst->tail = NULL;
}
//get a CIList and data(ConcertInstrument) and makes new node to the end list
void insertDataToEndCList(CIList* lst, ConcertInstrument data)
{
	LNODECI* newTail;
	newTail = createNewCListNode(data, NULL);
	insertNodeToEndCIList(lst, newTail);
}
//gets data(ConcertInstrument) and the ptr of the next (LNODECI*) and creates new CList node and returns it
LNODECI* createNewCListNode(ConcertInstrument data, LNODECI* next)
{
	LNODECI* res;
	res = (LNODECI*)malloc(sizeof(LNODECI));
	checkMemoryAllocation(res);
	res->data = data;
	res->next = next;
	return res;
}
//get a CIList and the ptr of the tail and inserts the node to the end list
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