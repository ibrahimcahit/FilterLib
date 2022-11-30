/*
 * Title: HighpassFilter.c
 * 
 * Date: 30/11/2022
 * 
 * Author: Ibrahim Cahit Ozdemir
 *
 * GitHub: ibrahimcahit
 */

#include "HighpassFilter.h"

void HighpassFilter(Filter_t *DataStruct, int n, float fc, float fs) {

  // Set filter order and check bounds
  order = n;
  
  if (order > 2) // Only up to second order at the moment...
    order = 2;
  else if (order < 1)
    order = 1;

  // Pre-warp cut-off frequency (Tustin)
  prewarp(DataStruct, fc, fs);

  // Reset filter inputs and outputs
  reset(DataStruct);

  // Set filter numerator and denominator coefficients
  float wcT   = DataStruct->wc * DataStruct->T;
  float wcTsq = wcT * wcT;
  
  switch (order) {

    case 1:

      DataStruct->num[0] =  2;
      DataStruct->num[1] = -2;

      DataStruct->den[0] =  2 + wcT;
      DataStruct->den[1] = -2 + wcT;
      break;

    case 2:     

      DataStruct->num[0] =  4;
      DataStruct->num[1] = -8;
      DataStruct->num[2] =  4;

      DataStruct->den[0] =  4 + 4 * wcT +     wcTsq;
      DataStruct->den[1] = -8 +           2 * wcTsq;
      DataStruct->den[2] =  4 - 4 * wcT +     wcTsq;
      break;

  }
  
}
