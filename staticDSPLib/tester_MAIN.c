#define _CRT_SECURE_NO_WARNINGS
#include "DSPEssentials.h"
#include "stdio.h"
#include "stdlib.h"
#include "DSPLib.h"

void main()
{
	DSPsysStatus mainStatus;
	const int N = 8;
	complex x[8] = { {5,0}, {-3,0}, {-2,0}, {1,0}, {-6,0}, {1,0}, {7,0}, {-4,0} };
	complex y[8];
	complex i_y[8]; // inverse y is a test array to see if i_y == x (for ifft,idft funcs);
	float y_mag[8];
	float y_phase[8];
	//complex* y, *i_y; 

	mainStatus = dft(&y, &x, N);
	printf("ARRAY AFTER FFT:\n[");
	for (int k = 0; k < N; k++)
	{
		printf("%.2f + j%.2f, ", y[k].real, y[k].img);
	}
	printf("]\n");

	mainStatus = ifft(&i_y, &y, N);
	printf("ARRAY AFTER iFFT:\n[");
	for (int k = 0; k < N; k++)
	{
		printf("%.2f + j%.2f, ", i_y[k].real, i_y[k].img);
	}
	printf("]\n");

	//mainStatus = ifft(&i_y, &y, N);

}