//
// Created by xwang on 7/25/17.
//

#ifndef AUTOEXPOSURE_COREFUNCTIONLIB_H
#define AUTOEXPOSURE_COREFUNCTIONLIB_H

#include <opencv2/opencv.hpp>
#include <math.h>

//#define DELTA_FUNC_K1 5
#define DELTA_FUNC_K1 5
#define DELTA_FUNC_K2 14
#define DELTA_FUNC_K3 1.6

namespace Exposure
{
  // delta_func used in SCurveAdjustment
  float delta_function(float x);

  template<typename pixelType>
  cv::Mat SCurveAdjustement(cv::Mat inputImg, int numChannels, float thetaShadow, float thetaHighlight);

  template<typename pixelType>
  cv::Mat LinearTransformAdjustment(cv::Mat inputImg, int numChannels, float gain, float brightness);

  /** Interfaces **/
  /*********************************************************/
  cv::Mat SCurveAdjustementC1(cv::Mat inputImg, float thetaShadow, float thetaHighlight);

  cv::Mat SCurveAdjustementC3(cv::Mat inputImg, float thetaShadow, float thetaHighlight);

  cv::Mat LinearTransformAdjustmentC1(cv::Mat inputImg, float gain, float brightness);

  cv::Mat LinearTransformAdjustmentC3(cv::Mat inputImg, float gain, float brightness);

}

#include "exposureCoreFunc_impl.hxx"
#endif //AUTOEXPOSURE_COREFUNCTIONLIB_H
