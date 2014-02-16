#ifndef _ELEMENT_CPP_
#define _ELEMENT_CPP_
#include "element.h"

// class Element {
//   public:
Element::Element(std::vector<std::vector<cv::Point> > cons, vector<cv::Vec4i> hierarchy){
	init(cons, hierarchy, 0);
}

/* -------------------------------------------------------------------------------- */
Element::Element(std::vector<std::vector<cv::Point> > cons, vector<cv::Vec4i> hierarchy, unsigned int ind){
	init(cons, hierarchy, ind);
}

/* -------------------------------------------------------------------------------- */
void Element::init(std::vector<std::vector<cv::Point> > cons, vector<cv::Vec4i> hierarchy, unsigned int ind){
	// init current elem
	cv::Rect rect = boundingRect(cons[ind]);
	x = rect.x;
	y = rect.y;
	w = rect.width;
	h = rect.height;

	// recurse downward, initializes other elems in tree
	// - next, prev, child, parent
	int child_ind = hierarchy[ind][2];
	while(hierarchy[child_ind][0] != -1){
		children.push_back(new Element(cons, hierarchy, hierarchy[child_ind][0]));
	}
}

/* -------------------------------------------------------------------------------- */
std::string Element::to_json(){
	
}

/* -------------------------------------------------------------------------------- */
Element::~Element(){
	children.clear();
}

/* -------------------------------------------------------------------------------- */
//     std::string type;
//     std::map<std::string,std::string> attrs;
//     std::vector<Element> children;
//     int x, y, w, h;
// };



#endif
