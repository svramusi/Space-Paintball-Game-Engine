#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>

#include "gun_utils.h"

GunUtils::GunUtils(const char* gun_info_xml)
{
    XmlUtils *xml_util = new XmlUtils(gun_info_xml);
    vector<xml_node<>*> vector_guns = xml_util->get_child_nodes("guns");

    num_guns = vector_guns.size();
    guns = (gun_info_t*)malloc(sizeof(gun_info_t) * num_guns);

    int count = 0;
    for(vector<xml_node<>*>::iterator it=vector_guns.begin(); it != vector_guns.end(); ++it) {
        xml_node<> *gun_node = *it;
        guns[count].name = gun_node->first_attribute("name")->value();
        guns[count].velocity = strtoul(gun_node->first_attribute("velocity")->value(), NULL, 10);
        count++;
    }

    delete xml_util;
}

GunUtils::~GunUtils()
{
    if(guns)
        delete guns;
}

void
GunUtils::print_guns()
{
    for(int i=0; i<num_guns; i++) {
        printf("name %s - velocity %lu\n", guns[i].name, guns[i].velocity);
    }
}
