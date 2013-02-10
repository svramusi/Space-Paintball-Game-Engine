#include "xml_utils.h"

XmlUtils::XmlUtils(const char* xml_file)
{
    ifstream xmlFile(xml_file);
    vector<char> buffer((istreambuf_iterator<char>(xmlFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    doc.parse<0>(&buffer[0]);
}

vector<xml_node<>*>
XmlUtils::get_child_nodes(const char* parent_node_name)
{
    vector<xml_node<>*> ret_vector;
    xml_node<> *root_node;

    root_node = doc.first_node(parent_node_name);

    while(root_node->first_node()) {
        ret_vector.push_back(root_node->first_node());
        root_node->remove_first_node();
    }

    return ret_vector;
}
