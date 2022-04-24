#include "GenericFunctionsDef.h"


void check_allocation(void* arr)
{
	if (arr == NULL)
	{
		printf("ERORR! ALLOCATION FAILED!!\n");
		exit(1);
	}
}


void checkFile(FILE* f)
{
	if (f == NULL)
	{
		printf("Opening file failed!\n");
		exit(-1);
	}
}