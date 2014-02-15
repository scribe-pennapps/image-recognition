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
	xpos  =  (double) ((double) self.get_min().x - parent.get_min().x) / parent.get_width();
	ypos  =  (double) ((double) self.get_min().y - parent.get_min().y) / parent.get_height();
	width  = (double) self.get_width() / parent.get_width();
	height = (double) self.get_height() / parent.get_height();
	str << "\"xpos\": "   << xpos   << ", ";
	str << "\"ypos\": "   << ypos   << ", ";
	str << "\"width\": "  << width  << ", ";
	str << "\"height\": " << height << ", ";
	str << "\"children\": [";
	for (int i = 0; i < children.size(); ++i){
		str << children[i].to_json(self);
		if(i != children.size() -1)
			str << ", ";
	}
	str << "]}";
	return str.str();
}

#endif
