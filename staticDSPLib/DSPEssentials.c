#pragma once

#include "DSPEssentials.h"

float* magArray(complex* arr, int size)
{
	float* out;
	int i;
	out = malloc(sizeof(float) * size);

	for (i = 0; i < size; i++)
	{
		out[i] = magnitude(arr[i]);
	}

	return out;
}
float* phaseArray(complex* arr, int size)
{
	float* out;
	int i;
	out = malloc(sizeof(float) * size);

	for (i = 0; i < size; i++)
	{
		out[i] = phase(arr[i]);
	}

	return out;
}
complex cmplxMult(complex z, complex w)
{
	complex res;
	float a, b, c, d;

	a = z.real;
	b = z.img;
	c = w.real;
	d = w.img;

	res.real = ((a == 0 || c == 0) && (b == 0 || d == 0)) ? 0 : (a * c - b * d);
	res.img = ((b == 0 || c == 0) && (a == 0 || d == 0)) ? 0 : (b * c + a * d);

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
inline float magnitude(complex num)
{
	return MAG(num.real, num.img);
}
inline float phase(complex num)
{
	if (num.real == 0 && num.img == 0)
	{
		return 0;
	}
	else if (num.real == 0)
	{
		return (num.img) < 0 ? -90 : 90;
	}
	return PHASE(num.real, num.img);
}