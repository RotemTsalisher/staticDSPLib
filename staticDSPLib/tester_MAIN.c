#define _CRT_SECURE_NO_WARNINGS
#include "DSPEssentials.h"
#include "stdio.h"
#include "stdlib.h"
#include "DSPLib.h"

void main()
{
	int N = 16;
	complex x[16];
	complex z,w,s;
	float* y_mag, *y_phase;
	complex* y, *i_y; 
	
	x[0].real = 7;
	x[0].img = 0;
	x[1].real = 9;
	x[1].img = 0;
	x[2].real = -8;
	x[2].img = 0;
	x[3].real = 9;
	x[3].img = 0;

	x[4].real = 3;
	x[4].img = 0;
	x[5].real = -5;
	x[5].img = 0;
	x[6].real = -30;
	x[6].img = 0;
	x[7].real = 1;
	x[7].img = 0; 

	x[8].real = 10;
	x[8].img = 0;
	x[9].real = 10;
	x[9].img = 0;
	x[10].real = -7;
	x[10].img = 0;
	x[11].real = 10;
	x[11].img = 0;


	x[12].real = 10;
	x[12].img = 0;
	x[13].real = 0;
	x[13].img = 0;
	x[14].real = 6;
	x[14].img = 0;
	x[15].real = -8;
	x[15].img = 0;
	y = NULL;

	/*
	for (int i = 0; i < N; i++)
	{
		printf("[");
		printf("[ % .2f + j %.2f] ",x[i].real, x[i].img);
	}
	printf("]\n");

	y = fft(&x, 15);
	if (COMPLEXCOMP(*y,RADIX2_LENGTH_NOT_SUPPORTED))
	{
		printf("length of fft not supported\n");
	}
	else
	{
		printf("----FFT:----\n");
		for (int i = 0; i < N; i++)
		{
			printf("[");
			printf("[ % .2f + j %.2f] ", y[i].real, y[i].img);
		}
		printf("]\n");
	}
	if (complexComp(*y,TEST_ERROR))
	{
		printf("also test null \n");
	} */
	/*i_y = idft(y, N);
	printf("----iDFT:----\n");

	for (int i = 0; i < N; i++)
	{
		printf("[");
		printf("[ % .2f + j %.2f] ", i_y[i].real, i_y[i].img);
	}
	printf("]\n"); */
	
	/**printf("MAGNITUDE: \n");
	for (int i = 0; i < N; i++)
	{
		printf("[");
		printf("[ % .2f] ", y[i]);
	}
	printf("]\n");  */
}