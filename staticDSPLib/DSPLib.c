#define _CRT_SECURE_NO_WARNINGS
#include "DSPEssentials.h"
#include "DSPLib.h"

DSPsysStatus DFTCalc(complex y[], complex x[], int N, int isInverse)
{
	complex twiddle, invFactor;
	int k, n;
	float angle;

	if (!(SUCCESS == initOutputArray(y, x, N, NOT_FOR_FFT)))
	{
		return INIT_ARRAY_FAILED;
	}

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
	return SUCCESS;
}
DSPsysStatus radix2FFT(complex y[], complex x[], int N, int isInverse)
{
	int stages, pointsPerSubDFT, butterfliesPerSubDFT, curStage, j, i,k,amountOfSubDFTs,a,twiddleIdx;
	complex *WLUT;
	complex tmp;

	if (!(isPowerOfTwo(N)))
	{
		return RADIX2_LENGTH_NOT_SUPPORTED;
	}

	WLUT = NULL;

	if (!(SUCCESS == initOutputArray(y, x, N, FOR_FFT)))
	{
		return INIT_ARRAY_FAILED;
	}//  copy input array to output array and apply bit reversal  if it is for fft

	stages = log2(N);
	amountOfSubDFTs = N >> 1;

	WLUT = malloc(sizeof(complex) * N);
	if (WLUT == NULL)
	{
		return ALLOCATION_FAILED;
	}
	else if (!(SUCCESS == twiddleFactorLUT(WLUT, N)))
	{
		return TWIDDLE_FACTOR_LUT_FAILED;
	}

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
	return SUCCESS;
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
DSPsysStatus twiddleFactorLUT(complex* WLUT, int N)
{
	int wlutSize, i;
	float baseAngle, angle, thresh,tmp;

	WLUT[0].real = 1;
	WLUT[0].img = 0;

	thresh = 0.5*pow(10, -5);
	wlutSize = N;
	baseAngle = (2 * PI) / N;

	for (i = 1; i < wlutSize; i++)
	{
		angle = -(baseAngle * i);
		tmp = cos(angle);
		WLUT[i].real = ((tmp < thresh)&&(-tmp < thresh)) ? 0 : tmp;
		tmp = sin(angle);
		WLUT[i].img = ((tmp < thresh)&&(-tmp < thresh)) ? 0 : tmp;
	}
	return SUCCESS;
}
DSPsysStatus initOutputArray(complex y[], complex x[], int N, int forFFT)
{
	if (forFFT)
	{
		memcpy(y, x, N * sizeof(complex));
		bitReversal(y, N);
	}
	else
	{
		memset(y, 0, N * sizeof(complex)); // init output array
	}
	if ((y == NULL) || (x == NULL))
	{
		return INIT_ARRAY_FAILED;
	}
	return SUCCESS; 
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
DSPsysStatus dft(complex y[], complex x[], int N) //this is what user actually calls
{
	if (!(SUCCESS == DFTCalc(y, x, N, NOT_INVERSE)))
	{
		// error handeling
	}
	else
	{
		return SUCCESS;
	}
}
DSPsysStatus idft(complex y[], complex x[], int N) // this is what user actually calls
{
	if (!(SUCCESS == DFTCalc(y, x, N, INVERSE)))
	{
		// error handeling
	}
	else
	{
		return SUCCESS;
	}
}
DSPsysStatus fft(complex y[], complex x[], int N)
{
	DSPsysStatus status;
	status = radix2FFT(y, x, N, NOT_INVERSE);
	if (status != SUCCESS)
	{
		// error handle
	}
	else
	{
		return SUCCESS;
	}
}
DSPsysStatus ifft(complex y[], complex x[], int N)
{
	DSPsysStatus status;

	status = radix2FFT(y, x, N, INVERSE);
	if (status != SUCCESS)
	{
		// error handle
	}
	else
	{
		return SUCCESS;
	}
}