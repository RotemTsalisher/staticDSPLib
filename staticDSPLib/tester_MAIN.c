#define _CRT_SECURE_NO_WARNINGS
#include "DSPEssentials.h"
#include "stdio.h"
#include "stdlib.h"
#include "DSPLib.h"

void main()
{
	DSPsysStatus mainStatus;
	int N = 4;
	complex x[4];
	complex y[4];
	complex i_y[4];
	complex z,w,s;
	float* y_mag, *y_phase;
	//complex* y, *i_y; 
	
	x[0].real = 1;
	x[0].img = 0;
	x[1].real = 1;
	x[1].img = 0;
	x[2].real = 1;
	x[2].img = 0;
	x[3].real = 0;
	x[3].img = 0;

	mainStatus = dft(&y, &x, N);
	printf("ARRAY AFTER FFT:\n[");
	for (int k = 0; k < N; k++)
	{
		printf("%.2f + j%.2f, ", y[k].real, y[k].img);
	}
	printf("]\n");

	mainStatus = idft(&i_y, &y, N);
	printf("ARRAY AFTER iFFT:\n[");
	for (int k = 0; k < N; k++)
	{
		printf("%.2f + j%.2f, ", i_y[k].real, i_y[k].img);
	}
	printf("]\n");

	//mainStatus = ifft(&i_y, &y, N);

}