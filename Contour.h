#ifndef _SCRIBE_CONTOUR_H_
#define _SCRIBE_CONTOUR_H_
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>

#define UNKNOWN -1
#define RECTANGLE 0
#define CIRCLE 1

class Contour {
public:
	Contour(std::vector<cv::Point>);
	~Contour();
	cv::Point get_min();
	cv::Point get_max();
	unsigned int get_shape();
	bool contains(Contour *other);
private:
	void gather_dimensions();
	void determine_shape();
	std::vector<cv::Point> points;
	cv::Point max, min;
	unsigned int shape;
};

#endif