//
// Created by xwang on 7/25/17.
//

#ifndef AUTOEXPOSURE_COREFUNCTIONLIB_IMPL_H
#define AUTOEXPOSURE_COREFUNCTIONLIB_IMPL_H
#include <opencv2/core/mat.hpp>
//#include "coreFunctionLib.h"
inline float Exposure::delta_function(float x)
{
  // k1xexp(-k2x^k3)
  return DELTA_FUNC_K1*x*exp(-DELTA_FUNC_K2*pow(x,DELTA_FUNC_K3));
}

inline cv::Point2f Exposure::contrastBand2GainBrightness(cv::Point2f cb)
{
  cv::Point2f gainBrightnessPoint;
  float a = cb.x;
  float b = cb.y;

  gainBrightnessPoint.x = 1/(b-a);
  gainBrightnessPoint.y = -a/(b-a);

  return gainBrightnessPoint;
}

template<typename pixelType>
cv::Mat Exposure::SCurveAdjustement(cv::Mat inputImg, int numChannels, float thetaShadow, float thetaHighlight)
{
  //std::cout<<inputImg.type()<<std::endl;
  cv::Mat inputFloatImg, outputFloatImg;

  switch(numChannels)
  {
    case 1:
      inputImg.convertTo(inputFloatImg, CV_32FC1, 1/255.0);
      break;

    case 3:
      inputImg.convertTo(inputFloatImg, CV_32FC3, 1/255.0);
      break;

    default:
      std::cout<<"Invalidate Canal Number!"<<std::endl;
      return cv::Mat();
  }

  inputFloatImg.copyTo(outputFloatImg);

  cv::MatConstIterator_<pixelType> itInput = inputFloatImg.begin<pixelType>();

  cv::MatConstIterator_<pixelType> itInput_end = inputFloatImg.end<pixelType>();

  cv::MatIterator_<pixelType> itOutput = outputFloatImg.begin<pixelType>();

  cv::MatIterator_<pixelType> itOutput_end = outputFloatImg.end<pixelType>();

  for(;(itInput!=itInput_end)||(itOutput!=itOutput_end); itInput++, itOutput++)
    for(int idx=0; idx<numChannels; idx++)
    {
      // Pixelized core function
      float x = (*itInput)[idx];
      (*itOutput)[idx] =cv::min(x+thetaShadow*delta_function(x)-thetaHighlight*delta_function(1-x),1.0f);
    }

  cv::Mat outputImg;
  switch(numChannels)
  {
    case 1:
      outputFloatImg.convertTo(outputImg, CV_8UC1, 255);
      break;

    case 3:
      outputFloatImg.convertTo(outputImg, CV_8UC3, 255);
      break;
  }

  return outputImg;
}

template<typename pixelType>
cv::Mat Exposure::LinearTransformAdjustment(cv::Mat inputImg, int numChannels, float gain, float brightness){
  //std::cout<<inputImg.type()<<std::endl;
  cv::Mat inputFloatImg, outputFloatImg;

  switch(numChannels)
  {
    case 1:
      inputImg.convertTo(inputFloatImg, CV_32FC1, 1/255.0);
      break;

    case 3:
      inputImg.convertTo(inputFloatImg, CV_32FC3, 1/255.0);
      break;

    default:
      std::cout<<"Invalidate Canal Number!"<<std::endl;
      return cv::Mat();
  }

  inputFloatImg.copyTo(outputFloatImg);

  cv::MatConstIterator_<pixelType> itInput = inputFloatImg.begin<pixelType>();

  cv::MatConstIterator_<pixelType> itInput_end = inputFloatImg.end<pixelType>();

  cv::MatIterator_<pixelType> itOutput = outputFloatImg.begin<pixelType>();

  cv::MatIterator_<pixelType> itOutput_end = outputFloatImg.end<pixelType>();

  for(;(itInput!=itInput_end)||(itOutput!=itOutput_end); itInput++, itOutput++)
    for(int idx=0; idx<numChannels; idx++)
    {
      // Pixelized core function
      float x = (*itInput)[idx];

      // Saturate cast to 1.0f
      if(gain>=0)
        (*itOutput)[idx]=cv::min((gain*x+brightness),1.0f);
      else
        (*itOutput)[idx]=cv::max((x+(1-x)*gain+brightness),0.0f);
    }

  cv::Mat outputImg;
  switch(numChannels)
  {
    case 1:
      outputFloatImg.convertTo(outputImg, CV_8UC1, 255);
      break;

    case 3:
      outputFloatImg.convertTo(outputImg, CV_8UC3, 255);
      break;
  }

  return outputImg;
}
  inline cv::Mat Exposure::SCurveAdjustementC1(cv::Mat inputImg, float thetaShadow, float thetaHighlight)
  {
    return SCurveAdjustement<cv::Vec<float, 1> >(inputImg, 1, thetaShadow, thetaHighlight);
  }

  inline cv::Mat Exposure::SCurveAdjustementC3(cv::Mat inputImg, float thetaShadow, float thetaHighlight)
  {
    return SCurveAdjustement<cv::Vec<float, 3> >(inputImg, 3, thetaShadow, thetaHighlight);
  }

  inline cv::Mat Exposure::LinearTransformAdjustmentC1(cv::Mat inputImg, float gain, float brightness)
  {
    return LinearTransformAdjustment<cv::Vec<float, 1> >(inputImg, 1, gain, brightness);
  }

  inline cv::Mat Exposure::LinearTransformAdjustmentC3(cv::Mat inputImg, float gain, float brightness)
  {
    return LinearTransformAdjustment<cv::Vec<float, 3> >(inputImg, 3, gain, brightness);
  }

  inline cv::Mat Exposure::SAT_ContrastBandC1(cv::Mat inputImg, cv::Point2f contrastBand)
  {
    cv::Point2f gbPt = Exposure::contrastBand2GainBrightness(contrastBand);
    return LinearTransformAdjustment<cv::Vec<float, 1> >(inputImg, 1, gbPt.x, gbPt.y);
  }

  inline cv::Mat Exposure::SAT_ContrastBandC3(cv::Mat inputImg, cv::Point2f contrastBand)
  {
    cv::Point2f gbPt = contrastBand2GainBrightness(contrastBand);
    return LinearTransformAdjustment<cv::Vec<float, 3> >(inputImg, 3, gbPt.x, gbPt.y);
  }

  inline cv::Mat Exposure::SAT_ContrastBandC1_Gf(cv::Mat inputImg, cv::Point2f contrastBand)
  {
    cv::Mat EqInput,EqGradientX,EqGradientY,EqGradient;
    cv::equalizeHist(inputImg,EqInput);
    cv::spatialGradient(EqInput,EqGradientX,EqGradientY);
    cv::convertScaleAbs(EqGradientX, EqGradientX);
    cv::convertScaleAbs(EqGradientY, EqGradientY);
    cv::addWeighted(EqGradientX, 0.5, EqGradientY, 0.5, 0, EqGradient);

    cv::ximgproc::guidedFilter(EqGradient,inputImg,inputImg,1,1);

    cv::Point2f gbPt = Exposure::contrastBand2GainBrightness(contrastBand);
    return LinearTransformAdjustment<cv::Vec<float, 1> >(inputImg, 1, gbPt.x, gbPt.y);
  }

#endif //AUTOEXPOSURE_COREFUNCTIONLIB_IMPL_H
