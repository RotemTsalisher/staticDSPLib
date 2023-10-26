#define _CRT_SECURE_NO_WARNINGS
#include "DSPEssentials.h"
#include "DSPLib.h"

complex* DFTByDef(complex x[], int N)
{
	complex twiddle;
	complex* y;
	int k, n;
	float angle;

	y = (complex*)malloc(N * sizeof(complex)); // allocate mem for N point DFT
	memset(y, 0, N * sizeof(complex)); // init output array
	memset(&twiddle, 0, sizeof(complex)); // init twiddle factor

	for (k = 0; k < N; k++) // apply DFT formula by definition
	{
		for (n = 0; n < N; n++)
		{
			if ((n == 0) || (k == 0))
			{
				// no need for func calls cos / sin because twiddle factor will be 1;
				y[k].real += x[n].real;
				y[k].img += x[n].img;
			}
			else
			{
				//calc twiddle factoe and apply formula;
				angle = ((2 * PI) * (k * n)) / N;
				twiddle.real = cos(angle);
				twiddle.img = -sin(angle);

				//complex multiplication of twiddle and input sample:
				y[k].real += twiddle.real * x[n].real - twiddle.img * x[n].img;
				y[k].img += twiddle.real * x[n].img + twiddle.img * x[n].real;
			}

		}
	}
	return y;
}
complex* radix2FFT(complex x[], int N)
{
	int stages, pointsPerStage, curStage, butterfliesPerStage,i;
	complex *y, *WLUT;

	stages = log2(N);
	y = bitReversal(y, N);
}
complex* bitReversal(complex* y, int N)
{

}
complex* twiddleFactorLUT(int N, int stages)
{
	int wlutSize, i;
	float baseAngle, angle;
	complex* WLUT;

	wlutSize = stages + 1;
	baseAngle = (2 * PI) / N;
	WLUT = malloc(sizeof(complex) * wlutSize);

	WLUT[i].real = 1;
	WLUT[i].img = 0;

	for (i = 1; i < wlutSize; i++)
	{
		angle = baseAngle * i;
		WLUT[i].real = cos(angle);
		WLUT[i].img = sin(angle);
	}
	return WLUT;
}