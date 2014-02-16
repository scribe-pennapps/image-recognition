#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <stdio.h>
#include "element.h"

using namespace cv;

const int thresh = 100;
const int max_thresh = 200;
RNG rng(12345);

void load_contours(Mat src) {
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<vector<Point> > filtered_contours;
  vector<Vec4i> hierarchy;

  Canny(src, canny_output, thresh, max_thresh, 3);

  findContours(canny_output, contours, hierarchy, CV_RETR_TREE, 
      CV_CHAIN_APPROX_SIMPLE);

  for(int i = 0; i < contours.size(); i++) {
    double area = contourArea(contours[i]);
    double len  = arcLength(contours[i], false);

    if(area > 500  &&  len/area < .13) {
      Rect rect = boundingRect(contours[i]);
      bool already_exists = false;
      for(int j = 0; j < filtered_contours.size(); j++) {
        Rect rect2 = boundingRect(filtered_contours[j]);
        if(rect.x == rect2.x && rect.y == rect2.y) {
          already_exists = true;
        }
      }

      if(!already_exists) {
        filtered_contours.push_back(contours[i]);
      }
    }
  }

  Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3);
  for(int i = 0; i < filtered_contours.size(); i++) {
    Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0, 255), 
        rng.uniform(0, 255));
    drawContours(drawing, filtered_contours, i, color, 2, 8, hierarchy, 0,
        Point());
  }

  namedWindow("Contours", CV_WINDOW_AUTOSIZE);
  imshow("Contours", drawing);

  Element *elem = new Element(filtered_contours);
  std::cout << elem->to_json() << std::endl;
}

int main(int argc, char** argv) {
  Mat src = imread(argv[1], 1);
  Mat src_gray;

  double alpha;
  int beta;

  cvtColor(src, src_gray, CV_BGR2GRAY);
  blur(src_gray, src_gray, Size(3,3));

  Mat element(5, 5, CV_8U, Scalar(1));
  erode(src_gray, src_gray, element);

  std::string window = "Source";
  namedWindow(window, CV_WINDOW_AUTOSIZE);
  imshow(window, src_gray);

  load_contours(src_gray);
  waitKey(0);

  return 0;
}
