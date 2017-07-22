#include "../include/AutoExposure.h"

using namespace Exposure;
int main() {
  std::cout << "Automatic Exposure Correction" << std::endl;
  cv::Mat src_img = cv::imread("Firenze_UnderExposure.jpg");
  cv::imshow("Original Image",src_img);
  cv::waitKey(0);
  ExposureCorrector<SCurve> SCurveCorrector(src_img);
  cv::Mat des_img = SCurveCorrector.ApplyExposureCorrection(1,1);
  cv::imshow("Corrected Image", des_img);
  cv::waitKey(0);
  return 0;
}