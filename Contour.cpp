#ifndef _SCRIBE_CONTOUR_CPP_
#define _SCRIBE_CONTOUR_CPP_
#include "Contour.h"


#define UNKNOWN -1
#define RECTANGLE 0
#define CIRCLE 1


Contour::Contour(std::vector<cv::Point> input){
	for(int i = 0; i < input.size(); ++i){
		cv::Point p(input[i].x, input[i].y);
		points.push_back(p);
	}
	min.x = 10000;
	min.y = 10000;
	max.x = -10000;
	max.y = -10000;
	cv::RNG rng(12345);
	color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
	gather_dimensions();
	determine_shape();
}

/* ---------------------------------------------------------------- */
Contour::~Contour(){
	points.clear();
}

/* ---------------------------------------------------------------- */
cv::Point Contour::get_min(){
	return min;
}

/* ---------------------------------------------------------------- */
cv::Point Contour::get_max(){
	return max;
}

/* ---------------------------------------------------------------- */
unsigned int Contour::get_shape(){
	return shape;
}

/* ---------------------------------------------------------------- */
bool Contour::contains(Contour *other){
	cv::Point omin = other->get_min();
	cv::Point omax = other->get_max();
	if(shape == RECTANGLE && other->get_shape() == RECTANGLE){
		return min.x <= omin.x  &&
			   min.y <= omin.y  &&
			   max.x >= omax.x  &&
			   max.y >= omax.y;
	} else {
		return false; // circles for later...
	}
}

/* ---------------------------------------------------------------- */

void Contour::gather_dimensions(){
	for (int i = 0; i < points.size(); ++i)
	{
		min.x = min.x < points[i].x?  min.x : points[i].x;
		min.y = min.y < points[i].y?  min.y : points[i].y;
		max.x = max.x > points[i].x?  max.x : points[i].x;
		max.y = max.y > points[i].y?  max.y : points[i].y;
	}
}

/* ---------------------------------------------------------------- */
void Contour::determine_shape(){
	
}

/* ---------------------------------------------------------------- */
void Contour::draw(cv::Mat mat){
	std::vector<std::vector<cv::Point> > vec;
	std::vector<cv::Vec4i> vec2;
	vec.push_back(points);
	drawContours( mat, vec, 0, color, 2, 8, vec2, 0, cv::Point());
}


#endif