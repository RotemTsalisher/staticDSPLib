#define _CRT_SECURE_NO_WARNINGS
#include "DSPEssentials.h"
#include "stdio.h"
#include "stdlib.h"
#include "DSPLib.h"

void main()
{
	int N = 4;
	complex x[4];
	complex* y; 
	x[0].real = 1;
	x[0].img = 0;
	x[1].real = 1;
	x[1].img = 0;
	x[2].real = 1;
	x[2].img = 0;
	x[3].real = 0;
	x[3].img = 0;

	for (int i = 0; i < 4; i++)
	{
		printf("[");
		printf("[ % .2f + j * %.2f] ",x[i].real, x[i].img);
	}
	printf("]\n");

	y = DFTByDef(&x, N);
	for (int i = 0; i < 4; i++)
	{
		printf("[");
		printf("[ % .2f + j * %.2f] ", y[i].real, y[i].img);
	}
	printf("]\n");
}