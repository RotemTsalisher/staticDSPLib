#define _CRT_SECURE_NO_WARNINGS
#include "DSPEssentials.h"
#include "DSPLib.h"

complex* DFTCalc(complex x[], int N, int isInverse)
{
	complex twiddle, invFactor;
	complex* y;
	int k, n;
	float angle;

	y = (complex*)malloc(N * sizeof(complex)); // allocate mem for N point DFT
	memset(y, 0, N * sizeof(complex)); // init output array
	memset(&twiddle, 0, sizeof(complex)); // init twiddle factor

	invFactor.real = (float)1 / N;
	invFactor.img = 0;

	for (k = 0; k < N; k++) // apply DFT formula by definition
	{
		for (n = 0; n < N; n++)
		{
			if ((n == 0) || (k == 0))
			{
				//twiddle will be equal to 1;
				twiddle.real = 1;
				twiddle.img = 0;
			}
			else
			{
				//calc twiddle factoe and apply formula;
				angle = ((2 * PI) * (k * n)) / N;
				twiddle.real = cos(angle);
				twiddle.img = (isInverse) ? sin(angle) : -sin(angle);
			}
			//complex multiplication of twiddle and input sample:
			y[k] = (isInverse) ? cmplxAdd(y[k], cmplxMult(cmplxMult(x[n], twiddle), invFactor)) : cmplxAdd(y[k], cmplxMult(x[n], twiddle));
		}
	}
	return y;
}
complex* radix2FFT(complex x[], int N, int isInverse)
{
	int stages, pointsPerSubDFT, butterfliesPerSubDFT, curStage, j, i,k,amountOfSubDFTs,a,twiddleIdx;
	complex *y, *WLUT;
	complex tmp;
	
	y = NULL;
	WLUT = NULL;

	y = initOutputArray(y, x, N); //  copy input array to output array and apply bit reversal 
	stages = log2(N);
	amountOfSubDFTs = N >> 1;
	WLUT = twiddleFactorLUT(WLUT, N);

	for (curStage = 1; curStage <= stages; curStage++)
	{
		pointsPerSubDFT = 1 << curStage;
		butterfliesPerSubDFT = pointsPerSubDFT >> 1;
		a = 0; // twiddle idx multiplier
		for (j = 0; j < N; j += pointsPerSubDFT) // go over sub DFT units
		{
			for (i = j; i < (j + butterfliesPerSubDFT); i++) // calc butterflies for each sub DFT
			{
				twiddleIdx = (i * amountOfSubDFTs) % N;
				k = i + butterfliesPerSubDFT;
				tmp = y[i];
				y[i] = cmplxAdd(y[i], cmplxMult(y[k], WLUT[twiddleIdx]));

				twiddleIdx = (k * amountOfSubDFTs) % N;
				y[k] = cmplxAdd(tmp, cmplxMult(y[k], WLUT[twiddleIdx]));
			}
		}
		amountOfSubDFTs = amountOfSubDFTs >> 1;
	}
	return y;
}
void bitReversal(complex* y, int N)
{
	int i, j, k;
	complex tmp;

	j = 0;
	i = 1;
	k = N / 2;

	for (; i < N - 1; i++)
	{
		k = N / 2;
		while (k <= j)
		{
			j -= k;
			k = k>> 1;
		}
		j += k;
		if (i < j)
		{
			tmp = y[i];
			y[i] = y[j];
			y[j] = tmp;
		}
	}
}
complex* twiddleFactorLUT(complex* WLUT, int N)
{
	int wlutSize, i;
	float baseAngle, angle, thresh,tmp;

	thresh = 0.5*pow(10, -5);
	wlutSize = N;
	baseAngle = (2 * PI) / N;
	WLUT = malloc(sizeof(complex) * wlutSize);

	WLUT[0].real = 1;
	WLUT[0].img = 0;

	for (i = 1; i < wlutSize; i++)
	{
		angle = -(baseAngle * i);
		tmp = cos(angle);
		WLUT[i].real = ((tmp < thresh)&&(-tmp < thresh)) ? 0 : tmp;
		tmp = sin(angle);
		WLUT[i].img = ((tmp < thresh)&&(-tmp < thresh)) ? 0 : tmp;
	}
	return WLUT;
}
complex* initOutputArray(complex* y,complex* x, int N)
{
	y = malloc(sizeof(complex) * N);
	memcpy(y, x, N * sizeof(complex));
	bitReversal(y, N);
	return y; ;
}
complex* fastConv(complex* x,int N, complex* h, int M, char method[])
{
	complex* out,*xf,*hf;
	int i, L;

	L = M + N - 1;
	out = malloc(sizeof(complex) * L);
	xf = malloc(sizeof(complex) * N);
	hf = malloc(sizeof(complex) * M);


	//xf = radix2FFT(x,N);
	//hf = radix2FFT(h, M);
	// implement element wise multiplication and ifft
}
complex* dft(complex x[], int N) //this is what user actually calls
{
	return DFTCalc(x, N, 0);
}
complex* idft(complex x[], int N) // this is what user actually calls
{
	return DFTCalc(x, N, 1);
}
complex* fft(complex x[], int N)
{
	if (isPowerOfTwo(N))
	{
		return radix2FFT(x, N, 0);
	}
	else
	{
		return LENGTH_NOT_SUPPORTED;
	}
}
complex* ifft(complex x[], int N)
{

}
