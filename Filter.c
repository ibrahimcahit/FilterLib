#include "Filter.h"

void prewarp(Filter_t *DataStruct, float fc, float fs) 
{

  // Check bounds on fs, prevent divide by zero or negative fs
  if (fs < 0)
    fs = 1.0;

  // Check that fc <= fs / 2 (Nyquist)
  if (fc > fs / 2.0)
    fc = fs / 2.0;
  else if (fc < 0.0)
    fc = 0.0;

  DataStruct->T = 1 / fs;
  DataStruct->wc = (2 / DataStruct->T) * tan(M_PI * fc / fs);
  
}

float getwc(Filter_t *DataStruct) {

  return DataStruct->wc;
  
}

float getT(Filter_t *DataStruct) {

  return DataStruct->T;
  
}

void reset(Filter_t *DataStruct) {

  for (int i = 0; i <= DataStruct->order; i++) {
    DataStruct->u[i] = 0.0;
    DataStruct->y[i] = 0.0;
  }
  
}

float update(Filter_t *DataStruct, float val) {

  int i;

  // Shift samples
  for (i = DataStruct->order; i > 0; i--) {
    DataStruct->u[i] = DataStruct->u[i - 1];
    DataStruct->y[i] = DataStruct->y[i - 1];
  }

  // Set new input
  DataStruct->u[0] = val;

  // Calculate new output
  DataStruct->y[0] = 0.0;

  for (i = 0; i <= DataStruct->order; i++) {
    DataStruct->y[0] += DataStruct->num[i] * DataStruct->u[i];

    if (i > 0)
      DataStruct->y[0] -= DataStruct->den[i] * DataStruct->y[i];
    
  }

  DataStruct->y[0] /= DataStruct->den[0];

  return DataStruct->y[0];

}
