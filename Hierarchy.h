#ifndef _SCRIBE_HIERARCHY_H_
#define _SCRIBE_HIERARCHY_H_
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "Contour.h"

class Hierarchy {
public:
	Hierarchy(std::vector<std::vector<cv::Point> >);
	~Hierarchy();
	std::string to_json();
private:
	void add_child(std::vector<cv::Point> v;);
	std::vector<Hierarchy> children;
	Contour *self;
};

#endif