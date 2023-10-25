#include "fileSys.h"
#include "DSPEssentials.h"
#include "string.h"

#define path  "sigs.txt"

int writeToFile(complex** sigs, int N, int amountOfSigs)
{
	FILE* pf;

	pf = fopen(path, "a");

}