#ifndef _SCRIBE_CONTOUR_H_
#define _SCRIBE_CONTOUR_H_
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <vector>

#define UNKNOWN -1
#define RECTANGLE 0
#define CIRCLE 1

class Contour {
public:
	Contour();
	Contour(std::vector<cv::Point>);
	~Contour();
	cv::Point get_min();
	cv::Point get_max();
	unsigned int get_width();
	unsigned int get_height();
	unsigned int get_shape();
	bool contains(Contour other);
	void draw(cv::Mat);
private:
	void gather_dimensions();
	void determine_shape();
	std::vector<cv::Point> points;
	cv::Point max, min;
	unsigned int shape;
	cv::Scalar color;
};

#endif