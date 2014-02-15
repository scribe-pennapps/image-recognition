#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "Contour.h"
#include "Hierarchy.h"

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);


void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  // Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  // Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  // Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ ){
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        // circle( drawing, Point( i * 20, 0 ), 100 / (i+1),  color, 2, 8, 0 );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
  }


  std::vector<Contour> ctrs;
  for(int i = 1; i < contours.size() && i < 6; ++i){
    ctrs.push_back(Contour(contours[i]));
    // contours[0][i], i,  Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) ), 2, 8, 0 );
  }


  Hierarchy *hier = new Hierarchy(Contour(contours[0]), ctrs);
  std::cout << hier->to_json() << std::endl;

  for (int i = 0; i < ctrs.size(); ++i)
    ctrs[i].draw(drawing);


  // Show in a window
  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow("Contours", drawing);
}



int main( int argc, char** argv )
{
  // Load source image and convert it to gray
  src = imread(argv[1], 1);

  // Convert image to gray and blur it
  cvtColor( src, src_gray, CV_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  // Create Window
  std::string window = "Source";
  namedWindow(window, CV_WINDOW_AUTOSIZE );
  imshow(window, src );

  createTrackbar("Canny thresh:", "Source", &thresh, max_thresh, thresh_callback);
  thresh_callback(0, 0);
  waitKey(0);
  return(0);
}