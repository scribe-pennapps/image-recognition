#ifndef _ELEMENT_H_
#define _ELEMENT_H_

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <map>
#include <string>
#include <vector>

class Element {
  public:
  	Element(std::vector<std::vector<cv::Point> >, vector<cv::Vec4i>);
  	~Element();
  	std::string to_json();
  private:
  	Element(std::vector<std::vector<cv::Point> >, vector<cv::Vec4i>, unsigned int);
  	void init(std::vector<std::vector<cv::Point> >, vector<cv::Vec4i>, unsigned int);
    std::string type;
    std::map<std::string,std::string> attrs;
    std::vector<Element *> children;
    int x, y, w, h;
};



#endif
