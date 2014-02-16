#ifndef _ELEMENT_CPP_
#define _ELEMENT_CPP_
#include "element.h"

Element::Element(std::vector<cv::Point> contour){
	cv::Rect rect = boundingRect(contour);
	x = rect.x;
	y = rect.y;
	w = rect.width;
	h = rect.height;
}

Element::Element(std::vector<std::vector<cv::Point> > contours){
	cv::Rect rect = boundingRect(contours[0]);
	x = rect.x;
	y = rect.y;
	w = rect.width;
	h = rect.height;
	for(int i = 1; i < contours.size(); ++i){
		if(contours[i].size() > 0)
			add_element(contours[i]);
	}
}

Element::~Element(){
	children.clear();
}

std::string Element::to_json(){
	return to_json(this);
}

std::string Element::to_json(Element *par){
	std::ostringstream str;
	str << "{";
	double xpos, ypos, width, height;
	xpos  =  (double) ((double) x - par->x) / par->w;
	ypos  =  (double) ((double) y - par->y) / par->h;
	width  = (double) w / par->w;
	height = (double) h / par->h;
	str << "\"xpos\": "   << xpos   << ", ";
	str << "\"ypos\": "   << ypos   << ", ";
	str << "\"width\": "  << width  << ", ";
	str << "\"height\": " << height << ", ";
	str << "\"children\": [";
	for (int i = 0; i < children.size(); ++i){
		str << children[i]->to_json(this);
		if(i != children.size() -1)
			str << ", ";
	}
	str << "]}";
	return str.str();
}


void Element::add_element(std::vector<cv::Point> contour){
	cv::Rect rect = boundingRect(contour);
	for (int i = 0; i < children.size(); ++i)
	{
		if(rect.x > children[i]->x  &&
		   rect.y > children[i]->y  &&
		   rect.width  < children[i]->w  &&
		   rect.height < children[i]->h){

			children[i]->add_element(contour);
			return;
		}
	}
	children.push_back(new Element(contour));
}
// std::string type;
// std::map<std::string,std::string> attrs;
// std::vector<Element *> children;
// int x, y, w, h;



#endif
