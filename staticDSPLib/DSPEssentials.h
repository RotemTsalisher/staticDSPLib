#define _CRT_SECURE_NO_WARNINGS
#define _COMPLEX_DEFINED        // to redefine "complex" struct given in "math.h" lib
#pragma once

#include "stdio.h"
#include "stdlib.h"
#include "math.h"

#define IMAGINARY_UNIT   0x69
#define PI               3.14159


typedef struct compelx
{
	float real;
	float img;

}complex;





