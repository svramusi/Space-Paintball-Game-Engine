#ifndef GUN_UTILS_H
#define GUN_UTILS_H

#include "xml_utils.h"

class GunUtils {
public:
    GunUtils(const char* gun_info_xml);
    ~GunUtils();
    void print_guns();

private:
    typedef struct {
        char* name;
        unsigned long velocity;
    } gun_info_t;

    gun_info_t* guns;
    int num_guns;

};
#endif
