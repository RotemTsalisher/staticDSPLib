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
			twiddleIdx = 0;
			for (i = j; i < (j + butterfliesPerSubDFT); i++) // calc butterflies for each sub DFT
			{
				if (curStage == 2)
				{
					a = a; //debugging
				}
				k = i + butterfliesPerSubDFT;
				tmp = y[i];
				y[i] = cmplxAdd(y[i], cmplxMult(y[k], WLUT[twiddleIdx]));
				twiddleIdx = (twiddleIdx + amountOfSubDFTs) % N;

				y[k] = cmplxAdd(tmp, cmplxMult(y[k], WLUT[twiddleIdx]));
				twiddleIdx = (twiddleIdx + amountOfSubDFTs) % N;
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
		angle = baseAngle * i;
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
complex cmplxMult(complex z, complex w)
{
	complex res;
	float a, b, c, d;

	a = z.real;
	b = z.img;
	c = w.real;
	d = w.img;

	res.real = ((a == 0 || c == 0)&&(b == 0 || d == 0)) ? 0 : (a * c - b * d);
	res.img = ((b == 0 || c == 0)&&(a == 0 || d == 0)) ? 0 : (b * c + a * d);

	return res;
}

complex cmplxAdd(complex z, complex w)
{
	complex res;
	float a, b, c, d;

	a = z.real;
	b = z.img;
	c = w.real;
	d = w.img;

	res.real = a + c;
	res.img = b + d;

	return res;
}