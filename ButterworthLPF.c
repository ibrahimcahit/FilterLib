/*
 * Title: ButterworthLPF.c
 * 
 * Date: 30/11/2022
 * 
 * Author: Ibrahim Cahit Ozdemir
 *
 * GitHub: ibrahimcahit
 */

#include "ButterworthLPF.h"

void ButterworthLPF(Filter_t *DataStruct, int n, float fc, float fs) {

  // Set filter order and check bounds
  DataStruct->order = n;
  
  if (DataStruct->order > 4) // Only up to fourth order at the moment...
	  DataStruct->order = 4;
  else if (DataStruct->order < 1)
	  DataStruct->order = 1;

  // Pre-warp cut-off frequency (Tustin)
  prewarp(DataStruct, fc, fs);

  // Reset filter inputs and outputs
  reset(DataStruct);

  // Set filter numerator and denominator coefficients
  float wcT   = DataStruct->wc * DataStruct->T;
  float wcTsq = wcT * wcT;
  float wcTcu = wcT * wcTsq;
  float wcTfo = wcTsq * wcTsq;

  float alpha = 2.6132;
  float beta  = 3.41430612;
  
  switch (DataStruct->order) {

    case 1:

      DataStruct->num[0] = wcT;
      DataStruct->num[1] = wcT;

      DataStruct->den[0] =  2 + wcT;
      DataStruct->den[1] = -2 + wcT;
      break;

    case 2:     

      DataStruct->num[0] =     wcTsq;
      DataStruct->num[1] = 2 * wcTsq;
      DataStruct->num[2] =     wcTsq;

      DataStruct->den[0] =  4 + 2.8284 * wcT + wcTsq;
      DataStruct->den[1] = -8 +            2 * wcTsq;
      DataStruct->den[2] =  4 - 2.8284 * wcT + wcTsq;
      break;

    case 3:

      DataStruct->num[0] =     wcTcu;
      DataStruct->num[1] = 3 * wcTcu;
      DataStruct->num[2] = 3 * wcTcu;
      DataStruct->num[3] =     wcTcu;

      DataStruct->den[0] =    8 + 8 * wcT + 4 * wcTsq +     wcTcu;
      DataStruct->den[1] = -24  - 8 * wcT + 4 * wcTsq + 3 * wcTcu;
      DataStruct->den[2] =  24 -  8 * wcT - 4 * wcTsq + 3 * wcTcu;
      DataStruct->den[3] =   -8 + 8 * wcT - 4 * wcTsq +     wcTcu;
      break;

    case 4:

      DataStruct->num[0] =     wcTfo;
      DataStruct->num[1] = 4 * wcTfo;
      DataStruct->num[2] = 6 * wcTfo;
      DataStruct->num[3] = 4 * wcTfo;
      DataStruct->num[4] =     wcTfo;

      DataStruct->den[0] =  16 +  8 * alpha * wcT + 4 * beta * wcTsq + 2 * alpha * wcTcu +     wcTfo;
      DataStruct->den[1] = -64 - 16 * alpha * wcT                    + 4 * alpha * wcTcu + 4 * wcTfo;
      DataStruct->den[2] =  96                    - 8 * beta * wcTsq                     + 6 * wcTfo;
      DataStruct->den[3] = -64 + 16 * alpha * wcT                    - 4 * alpha * wcTcu + 4 * wcTfo;
      DataStruct->den[4] =  16 -  8 * alpha * wcT + 4 * beta * wcTsq - 2 * alpha * wcTcu +     wcTfo;      
      break;

  }
  
}
