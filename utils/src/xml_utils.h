#include <fstream>
#include <vector>

#include "rapidxml.hpp"

using namespace rapidxml;
using namespace std;

class XmlUtils {
public:
    XmlUtils(const char* xml_file);
    vector<xml_node<>*> get_child_nodes(const char* parent_node_name);

private:
    xml_document<> doc;
};
