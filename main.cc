#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>

using namespace cv;

const int thresh = 100;
RNG rng(12345);

void load_contours(Mat src) {
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  Canny(src, canny_output, thresh, thresh, 3);

  findContours(canny_output, contours, hierarchy, CV_RETR_TREE, 
      CV_CHAIN_APPROX_SIMPLE);

  Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
  for(int i; i < contours.size(); i++) {
    Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), 
        rng.uniform(0, 255));
    if(contourArea(contours[i]) > 500) {
      drawContours(drawing, contours, i, color, 2, 8, hierarchy, 0, Point());
    }
  }

  namedWindow("Contours", CV_WINDOW_AUTOSIZE);
  imshow("Contours", drawing);
}

int main(int argc, char** argv) {
  Mat src = imread(argv[1], 1);
  Mat src_gray;

  double alpha;
  int beta;

  cvtColor(src, src_gray, CV_BGR2GRAY);
  blur(src_gray, src_gray, Size(3,3));

  std::string window = "Source";
  namedWindow(window, CV_WINDOW_AUTOSIZE);
  imshow(window, src_gray);

  load_contours(src);
  waitKey(0);

  return 0;
}
