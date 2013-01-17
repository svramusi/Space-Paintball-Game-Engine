#include "utils/gun_utils.h"

int main(void)
{
    GunUtils *guns = new GunUtils("example.xml");
    guns->print_guns();
    delete guns;
}
