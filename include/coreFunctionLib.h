//
// Created by xwang on 7/25/17.
//

#ifndef AUTOEXPOSURE_COREFUNCTIONLIB_H
#define AUTOEXPOSURE_COREFUNCTIONLIB_H

#include <opencv2/opencv.hpp>
#include <math.h>

#define DELTA_FUNC_K1 5
#define DELTA_FUNC_K2 14
#define DELTA_FUNC_K3 1.6

namespace Exposure
{
  float delta_function(float x);
  template<typename pixelType>
  cv::Mat SCurveAdjustement(cv::Mat inputImg, int numChannels, float thetaShadow, float thetaHighlight);

}
#endif //AUTOEXPOSURE_COREFUNCTIONLIB_H