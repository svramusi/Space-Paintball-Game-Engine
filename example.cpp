#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>

//We'll handle the errors
//#define RAPIDXML_NO_EXCEPTIONS

#include "thirdparty/rapidxml-1.13/rapidxml.hpp"
#include "utils/xml_utils.h"

using namespace rapidxml;
using namespace std;

void get_guns(const char* gun_file);
vector<xml_node<>*> get_child_nodes(const char* xml_file, const char* parent_node_name);

int main(void)
{
/*
    xml_document<> doc;
    xml_node<> *root_node;

    ifstream theFile("example.xml");

    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');
    doc.parse<0>(&buffer[0]);
    root_node = doc.first_node("guns");

    for(xml_node<> *gun_node = root_node->first_node("gun"); gun_node; gun_node = gun_node->next_sibling()) {
        printf("name %s - velocity %s", gun_node->first_attribute("name")->value(), gun_node->first_attribute("velocity")->value());
        cout << endl;
    }
*/
    get_guns("example.xml");
}

//In gun utils
void
get_guns(const char* gun_file)
{

    XmlUtils *xml_util = new XmlUtils(gun_file);
    vector<xml_node<>*> guns = xml_util->get_child_nodes("guns");

    for(vector<xml_node<>*>::iterator it=guns.begin(); it != guns.end(); ++it) {
        xml_node<> *gun_node = *it;
        printf("name %s - velocity %s", gun_node->first_attribute("name")->value(), gun_node->first_attribute("velocity")->value());
        cout << endl;
    }

    delete xml_util;
}

/*
//In xml utils
vector<xml_node<>*>
get_child_nodes(const char* xml_file, const char* parent_node_name)
{
    vector<xml_node<>*> ret_vector;

    xml_document<> doc;
    xml_node<> *root_node;

    ifstream theFile(xml_file);

    vector<char> buffer((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
    buffer.push_back('\0');

    doc.parse<0>(&buffer[0]);
    root_node = doc.first_node(parent_node_name);

    while(root_node->first_node()) {
        ret_vector.push_back(root_node->first_node());
        root_node->remove_first_node();
    }

    return ret_vector;
}
*/
