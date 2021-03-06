//
// Created by xwang on 7/21/17.
//

#ifndef AUTOEXPOSURE_AUTOEXPOSURE_H
#define AUTOEXPOSURE_AUTOEXPOSURE_H

#include <opencv2/opencv.hpp>
#include <iostream>
#include "exposureCoreFunc.h"
namespace Exposure
{
// The type used in Core Function to indicate different strategies
enum coreFuncType {HistoEq, LinearTransform, SCurve};

// Common Part of Different Types
class ExposureCorrectorBase
{

public:
  // Default Ctor
  ExposureCorrectorBase();
  // Usual Ctor
  ExposureCorrectorBase(cv::Mat _src_img);

protected:
  // Source Image Copy
  cv::Mat src_img;
  // Destination Image Copy
  cv::Mat des_img;
};

template <coreFuncType coreT>
class ExposureCorrector : public ExposureCorrectorBase
{};

template <>
class ExposureCorrector<SCurve> : public ExposureCorrectorBase
{
public:
  ExposureCorrector(cv::Mat _src_img);
  cv::Mat ApplyExposureCorrection(float thetaShadow, float thetaHighlight);
};

template <>
class ExposureCorrector<LinearTransform> : public ExposureCorrectorBase
{
public:
  ExposureCorrector(cv::Mat _src_img);
  cv::Mat ApplyExposureCorrection(float gain, float brightness);
};
// namespace Exposure
}

#endif //AUTOEXPOSURE_AUTOEXPOSURE_H
#include "AutoExposure_impl.hxx"
