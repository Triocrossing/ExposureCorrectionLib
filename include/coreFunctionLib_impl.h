//
// Created by xwang on 7/25/17.
//

#ifndef AUTOEXPOSURE_COREFUNCTIONLIB_IMPL_H
#define AUTOEXPOSURE_COREFUNCTIONLIB_IMPL_H
#include <opencv2/core/mat.hpp>

template<typename pixelType>
cv::Mat Exposure::SCurveAdjustement(cv::Mat inputImg, int numChannels, float thetaShadow, float thetaHighlight)
{
  std::cout<<inputImg.type()<<std::endl;
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
      (*itOutput)[idx]= x+thetaShadow*delta_function(x)-thetaHighlight*delta_function(1-x);
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
#endif //AUTOEXPOSURE_COREFUNCTIONLIB_IMPL_H
