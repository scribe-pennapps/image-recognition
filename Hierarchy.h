#ifndef _SCRIBE_HIERARCHY_H_
#define _SCRIBE_HIERARCHY_H_
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include "Contour.h"
#include <sstream>


class Hierarchy {
public:
	Hierarchy(Contour);
	Hierarchy(Contour, std::vector<Contour>);
	~Hierarchy();
	std::string to_json();
	bool contains(Contour con);
private:
	std::string to_json(Contour parent);
	void add_child(Contour);
	std::vector<Hierarchy> children;
	Contour self;
};

#endif