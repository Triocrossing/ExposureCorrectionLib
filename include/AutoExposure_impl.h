#ifndef AUTOEXPOSURE_AUTOEXPOSURE_IMPL_H
#define AUTOEXPOSURE_AUTOEXPOSURE_IMPL_H

#include "AutoExposure.h"
namespace Exposure
{
ExposureCorrectorBase::ExposureCorrectorBase()
{}

ExposureCorrectorBase::ExposureCorrectorBase(cv::Mat _src_img) : src_img(_src_img)
{}

ExposureCorrector<SCurve>::ExposureCorrector(cv::Mat _src_img) : ExposureCorrectorBase(
    _src_img)
{}

cv::Mat ExposureCorrector<SCurve>::ApplyExposureCorrection(float thetaShadow, float thetaHighlight)
{
  switch (src_img.channels())
  {
    case 1:
      return SCurveAdjustement<cv::Vec<float, 1>>(src_img, 1, thetaShadow, thetaHighlight);

    case 3:
      return SCurveAdjustement<cv::Vec<float, 3>>(src_img, 3, thetaShadow, thetaHighlight);

    default:
      std::cout << "Insupport channel num" << std::endl;
  }
}
//namespace Exposure
}

#endif
