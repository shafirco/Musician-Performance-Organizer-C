//shafir cohen 315995589
//amit kochavi 315409102

#include "CheckingHeader.h"

//check memory allocation
void checkMemoryAllocation(void* res)
{
	if (res == NULL)
	{
		printf("Memory allocation faild!\n");
		exit(1);
	}

}
//check memory reallocation
void checkMemoryReallocation(void* res)
{
	if (res == NULL)
	{
		printf("Memory reallocation faild!\n");
		exit(1);
	}
}
//check if the file opened successfully
void checkOpeningFile(FILE* f)
{
	if (f == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		exit(1);
	}
}
