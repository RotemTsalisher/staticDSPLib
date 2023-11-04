#pragma once
#include "string.h"


/* GOALS:
* - DFT                                         ->> DONE!
* - FFT                                         ->> DONE!
* - MAGNITUDE OF AN ARRAY                       ->> DONE!
* - PHASE OF AN ARRAY                           ->> DONE!
* - OVERLAP ADD
* - OVERLAP SAVE
* - FAST CONV
* - LASTLY: WRITE ANNOTATIONS FOR ALL FUNCTIONS */

/* -------------------- DFTByDef --------------------
 * DFTByDef will apply the DFT computations by definition
 * will define the twiddle factor: WN = exp(-j*(2*pi)/N)
 * also. by Euler WN = cos(2*pi/N) -j*sin(2*pi/N)
 * each itteration over n\k will rotate the exponent, resulting in a new angle
 * for each k, will compute the sum of all complex multiplications between 
 * twiddle factor raised to n power (multiply the base angle), and input samples.
 * -------------------- -------- -------------------- */
DSPsysStatus DFTCalc(complex* y,complex x[], int N, int isInverse);
/* -------------------- radix2FFT -------------------
 * 
 * 
 * 
 * 
 * 
 * 
 * -------------------- -------- -------------------- */
DSPsysStatus radix2FFT(complex y[], complex x[], int N, int isInverse);

DSPsysStatus dft(complex y[], complex x[], int N); // dft allocates a ptr, calls a method to compute and return a status

DSPsysStatus idft(complex y[], complex x[], int N); // same as dft

DSPsysStatus twiddleFactorLUT(complex* WLUT, int );

void bitReversal(complex* y, int N);

DSPsysStatus initOutputArray(complex y[], complex x[], int N, int bitRevNeeded);

DSPsysStatus fft(complex y[], complex x[], int N); // fft allocates a ptr, call a method function to compute and return status

DSPsysStatus ifft(complex y[], complex x[], int N); // same as fft






