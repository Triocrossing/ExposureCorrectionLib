//
// Created by xwang on 7/22/17.
//
#include "../include/AutoExposure.h"

// Ctor
Exposure::ExposureCorrectorBase::ExposureCorrectorBase(cv::Mat _src_img) : src_img(_src_img) {}

// Default Ctor
Exposure::ExposureCorrectorBase::ExposureCorrectorBase() {}

cv::Mat Exposure::ExposureCorrector<Exposure::SCurve>::ApplyExposureCorrection(float thetaShadow, float thetaHighlight)
{
  return src_img;
}

Exposure::ExposureCorrector<Exposure::SCurve>::ExposureCorrector(cv::Mat _src_img) : ExposureCorrectorBase(_src_img) {}



