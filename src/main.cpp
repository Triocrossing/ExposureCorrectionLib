#include "../include/AutoExposure.h"

using namespace Exposure;
template<coreFuncType coreT>
int UnitTest(float param1, float param2) {
  std::cout << "Automatic Exposure Correction" << std::endl;
  cv::Mat src_img = cv::imread("Firenze_UnderExposure.jpg");
  //cv::Mat src_img = cv::imread("ImgBW.tiff");
  cv::imshow("Original Image", src_img);
  cv::waitKey(0);
  ExposureCorrector<coreT> Corrector(src_img);
  cv::Mat des_img = Corrector.ApplyExposureCorrection(param1,param2);
  cv::imshow("Corrected Image", des_img);
  cv::waitKey(0);
  cv::destroyAllWindows();
  return 0;
}

int main()
{
  UnitTest<SCurve>(1.5,0);
  UnitTest<LinearTransform>(5,0);
  return 0;
}