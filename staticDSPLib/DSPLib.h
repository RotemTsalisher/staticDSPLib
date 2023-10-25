#pragma once

/* -------------------- DFTByDef --------------------
 * DFTByDef will apply the DFT computations by definition
 * will define the twiddle factor: WN = exp(-j*(2*pi)/N)
 * also. by Euler WN = cos(2*pi/N) -j*sin(2*pi/N)
 * each itteration over n\k will rotate the exponent, resulting in a new angle
 * for each k, will compute the sum of all complex multiplications between 
 * twiddle factor raised to n power (multiply the base angle), and input samples.
 * -------------------- -------- -------------------- */
complex* DFTByDef(complex x[], int N);