// #include "opencv2/highgui/highgui.hpp"
// #include "opencv2/imgproc/imgproc.hpp"
// #include <iostream>
// #include <stdio.h>
// #include <stdlib.h>

// using namespace cv;
// using namespace std;

// /// Global variables
// Mat src, src_gray;
// int thresh = 200;
// int max_thresh = 225;

// // char* source_window = "Source image";
// char* corners_window = "Corners detected";

// /// Function header
//   void cornerHarris_demo( int, void* );

// int main( int argc, char** argv )
// {
//   src = imread( argv[1], 1 );
//   cvtColor( src, src_gray, CV_BGR2GRAY );

//   cornerHarris_demo( 0, 0 );
//   waitKey(0);
//   return(0);
// }

// void draw_line( Mat img, Point start, Point end )
// {
//   int thickness = 2;
//   int lineType = 8;
//   line( img,
//   start,
//   end,
//   Scalar( 0, 0, 0 ),
//   thickness,
//   lineType );
// }


// /** @function cornerHarris_demo */
// void cornerHarris_demo( int, void* )
// {

//   Mat dst, dst_norm, dst_norm_scaled;
//   dst = Mat::zeros( src.size(), CV_32FC1 );

//   /// Detector parameters
//   int blockSize = 2;
//   int apertureSize = 3;
//   double k = 0.08;

//   /// Detecting corners
//   cornerHarris( src_gray, dst, blockSize, apertureSize, k, BORDER_DEFAULT );

//   /// Normalizing
//   normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
//   convertScaleAbs( dst_norm, dst_norm_scaled );



//   vector<Point> ps;



//   /// Drawing a circle around corners
//   for( int j = 0; j < dst_norm.rows ; j++ ){
//     for( int i = 0; i < dst_norm.cols; i++ ){
//     if( (int) dst_norm.at<float>(j,i) > thresh ){
//         // points.push_back
//         ps.push_back(Point(i,j));
//        circle( dst_norm_scaled, Point( i, j ), 5,  Scalar(0), 2, 8, 0 );
//       }
//     }
//   }

//   // for (int i = 0; i < ps.size(); ++i)
//   // {
//   //   for (int j = 0; j < ps.size(); ++j)
//   //   {
//   //     if(i != j){
//   //       draw_line(dst_norm_scaled, ps[i], ps[j]);
//   //     }
//   //   }
//   // }





//   /// Showing the result
//   namedWindow( corners_window, CV_WINDOW_AUTOSIZE );
//   imshow( corners_window, dst_norm_scaled );
// }


#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

/// Function header
void thresh_callback(int, void* );

/** @function main */
int main( int argc, char** argv )
{
  /// Load source image and convert it to gray
  src = imread( argv[1], 1 );

  /// Convert image to gray and blur it
  cvtColor( src, src_gray, CV_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  /// Create Window
  char* source_window = "Source";
  namedWindow( source_window, CV_WINDOW_AUTOSIZE );
  imshow( source_window, src );

  createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
  thresh_callback( 0, 0 );

  waitKey(0);
  return(0);
}


/** @function thresh_callback */
void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ ){
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
        // circle( drawing, Point( i * 20, 0 ), 100 / (i+1),  color, 2, 8, 0 );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
  }



  for(int i = 0; i < contours[0].size(); ++i){
    circle( drawing, contours[0][i], i,  Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) ), 2, 8, 0 );
  }


  /// Show in a window
  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );
  imshow( "Contours", drawing );
}