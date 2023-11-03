#define _CRT_SECURE_NO_WARNINGS
#define _COMPLEX_DEFINED        // to redefine "complex" struct given in "math.h" lib
#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define IMAGINARY_UNIT               0x69
#define PI                           3.14159
#define TWIDDLE_ZERO                 (complex){1,0}

#define SQUARE(a)                    a*a
#define MAG(a,b)                     sqrt((SQUARE(a) + SQUARE(b)))
#define PHASE(a,b)		             atan(b/a)*(180/PI) 

#define FOR_FFT                      0x01
#define NOT_FOR_FFT                  0x00

#define INVERSE                      0x01
#define NOT_INVERSE                  0x00


typedef struct compelx
{
	float real;
	float img;

}complex;

typedef enum DSPsysStatus {

	
	SUCCESS                       =  1,
	RADIX2_LENGTH_NOT_SUPPORTED   = -1,
	TWIDDLE_FACTOR_LUT_FAILED     = -2,
	MULT_LENGTHES_NOT_EQUAL       = -3,
	INIT_ARRAY_FAILED             = -4,
	ALLOCATION_FAILED             = -5,

	EMPTY_SEQUENCE                = -9,

}DSPsysStatus;

complex cmplxMult(complex z, complex w);

complex cmplxAdd(complex z, complex w);

inline float magnitude(complex num);

inline float phase(complex num);

float* phaseArray(complex* arr, int size);

float* magArray(complex* arr, int size);

int isPowerOfTwo(int N);

int complexComp(complex a, complex b);

DSPsysStatus eleWiseArrayMult(complex y[], complex z[], int M, complex w[], int N);






