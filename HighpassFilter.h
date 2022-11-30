/*
 * Title: HighpassFilter.h
 * 
 * Date: 30/11/2022
 * 
 * Author: Ibrahim Cahit Ozdemir
 *
 * GitHub: ibrahimcahit
 */

#ifndef HIGHPASS_FILTER_H
#define HIGHPASS_FILTER_H

#include "Filter.h"

void HighpassFilter(Filter_t *DataStruct, int n, float fc, float fs);
  
#endif