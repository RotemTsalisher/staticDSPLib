#define _CRT_SECURE_NO_WARNINGS
#define _COMPLEX_DEFINED        // to redefine "complex" struct given in "math.h" lib
#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define IMAGINARY_UNIT   0x69
#define PI               3.14159

#define SQUARE(a)        a*a
#define MAG(a,b)         sqrt((SQUARE(a) + SQUARE(b)))
#define PHASE(a,b)		 atan(b/a)*(180/PI)


typedef struct compelx
{
	float real;
	float img;

}complex;

complex cmplxMult(complex z, complex w);

complex cmplxAdd(complex z, complex w);

inline float magnitude(complex num);

inline float phase(complex num);

float* phaseArray(complex* arr, int size);

float* magArray(complex* arr, int size);





