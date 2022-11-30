/*
 * Title: ButterworthLPF.h
 * 
 * Date: 30/11/2022
 * 
 * Author: Ibrahim Cahit Ozdemir
 *
 * GitHub: ibrahimcahit
 */

#ifndef BUTTERWORTHLPF_H
#define BUTTERWORTHLPF_H

#include "Filter.h"

void ButterworthLPF(Filter_t *DataStruct, int n, float fc, float fs);

#endif