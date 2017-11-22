#include "../include/AutoExposure.h"

  using namespace Exposure;
  template<coreFuncType coreT>
cv::Mat UnitTest(cv::Mat src_img, float param1, float param2)
{
  std::cout << "Automatic Exposure Correction" << std::endl;
  cv::imshow("Original Image", src_img);
  //cv::waitKey(0);
  ExposureCorrector<coreT> Corrector(src_img);
  cv::Mat des_img = Corrector.ApplyExposureCorrection(param1,param2);
  cv::imshow("Corrected Image", des_img);
  cv::waitKey(0);
  cv::destroyAllWindows();
  return des_img;
}

int main()
{
  cv::Mat src_img = cv::imread("testIndoor.png", cv::IMREAD_GRAYSCALE);
  //cv::Mat src_img = cv::imread("Firenze_UnderExposure.jpg", cv::IMREAD_GRAYSCALE);
  //cv::Mat src_img = cv::imread("ImgBW.tiff");


  cv::Mat SCurve_res = UnitTest<SCurve>(src_img,0.9,0);
  //UnitTest<SCurve>(0,0.9);
  //UnitTest<SCurve>(0.4,0.4);
  cv::Mat LinearTrans_res = UnitTest<LinearTransform>(src_img,9,0);
  cv::Mat SAT_res1 = SAT_ContrastBandC1(src_img,cv::Point2f(0,1));
  cv::Mat SAT_res2 = SAT_ContrastBandC1(src_img,cv::Point2f(0,0.15));

  cv::imshow("Src", src_img);
  cv::imshow("SCurve_res", SCurve_res);
  cv::imshow("Linear_res", LinearTrans_res);
  cv::imshow("SAT_res1", SAT_res1);
  cv::imshow("SAT_res2", SAT_res2);
  cv::waitKey(0);
  return 0;
}