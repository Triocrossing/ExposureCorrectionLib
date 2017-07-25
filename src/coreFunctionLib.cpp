//
// Created by xwang on 7/25/17.
//
#include "../include/coreFunctionLib.h"

float ::Exposure::delta_function(float x)
{
  // k1xexp(-k2x^k3)
  return DELTA_FUNC_K1*x*exp(-DELTA_FUNC_K2*pow(x,DELTA_FUNC_K3));
}

