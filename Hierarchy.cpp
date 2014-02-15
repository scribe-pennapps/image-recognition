#ifndef _SCRIBE_HIERARCHY_CPP_
#define _SCRIBE_HIERARCHY_CPP_
#include "Hierarchy.h"


Hierarchy::Hierarchy(Contour con){
	self = con;
}

/* ------------------------------------------------------------------- */
Hierarchy::Hierarchy(Contour con, std::vector<Contour> oths){
	self = con;
	for (int i = 0; i < oths.size(); ++i)
		add_child(oths[i]);
}

/* ------------------------------------------------------------------- */
Hierarchy::~Hierarchy(){
	children.clear();
}

/* ------------------------------------------------------------------- */
void Hierarchy::add_child(Contour con){
	for (int i = 0; i < children.size(); ++i){
		if(children[i].contains(con)){
			children[i].add_child(con);
			return;
		}
	}
	Hierarchy h(con);
	children.push_back(h);
}

/* ------------------------------------------------------------------- */
bool Hierarchy::contains(Contour con){
	return self.contains(con);
}

/* ------------------------------------------------------------------- */
std::string Hierarchy::to_json(){
	return to_json(self);
}

std::string Hierarchy::to_json(Contour parent){
	std::ostringstream str;
	str << "{";
	double xpos, ypos, width, height;
	std::cout << "MAX X: " << self.get_max().x << std::endl;
	std::cout << "MIN X: " << self.get_min().x << std::endl;
	xpos  = self.get_min().x;
	ypos  = self.get_max().y;
	width = self.get_width();
	height = self.get_height();
	str << "\"xpos\": "   << xpos   << ", ";
	str << "\"ypos\": "   << ypos    << ", ";
	str << "\"width\": "  << width  << ", ";
	str << "\"height\": " << height << ", ";
	str << "[";
	for (int i = 0; i < children.size(); ++i)
		str << children[i].to_json();
	str << "]}";
	return str.str();
}

#endif
