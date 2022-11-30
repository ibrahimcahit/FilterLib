
/*
 * Title: Filter.h
 * 
 * Date: 30/11/2022
 * 
 * Author: Ibrahim Cahit Ozdemir
 *
 * GitHub: ibrahimcahit
 */

#ifndef FILTER_H
#define FILTER_H

#include <math.h>

#define FILTER_MAX_ORDER 4

typedef struct 
{
    float wc, T;

    int order;
    float num[FILTER_MAX_ORDER + 1];
    float den[FILTER_MAX_ORDER + 1];

    float u[FILTER_MAX_ORDER + 1];
    float y[FILTER_MAX_ORDER + 1];
} Filter_t;

void prewarp(Filter_t *DataStruct, float fc, float fs);
float getwc(Filter_t *DataStruct);
float getT(Filter_t *DataStruct);

void reset(Filter_t *DataStruct);
float update(Filter_t *DataStruct, float val);

#endif
