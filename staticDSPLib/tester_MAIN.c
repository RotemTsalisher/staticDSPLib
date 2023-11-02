#define _CRT_SECURE_NO_WARNINGS
#include "DSPEssentials.h"
#include "stdio.h"
#include "stdlib.h"
#include "DSPLib.h"

void main()
{
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

	y = fft(&x, N);
	i_y = ifft(&y, N);

}