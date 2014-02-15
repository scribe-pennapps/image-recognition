#include <map>
#include <string>

class Element {
  public:
    std::string type;
    std::map<std::string,std::string> attrs;
    std::vector<Element> children;
    int x;
    int y;
    int width;
    int height;
};
