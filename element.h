#ifndef _ELEMENT_H_
#define _ELEMENT_H_
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <map>
#include <string>
#include <sstream>
#include <vector>

class Element {
  public:
    Element();
    Element(std::vector<cv::Point>);
    Element(std::vector<std::vector<cv::Point> >);
  	~Element();
    std::string to_json();
  private:
    std::string to_json(Element *par);
    void add_element(std::vector<cv::Point>);
    std::string type;
    std::map<std::string,std::string> attrs;
    std::vector<Element *> children;
    int x, y, w, h;
};

#endif
