#include <iostream>
#include "gun_utils.h"

using namespace std;

int main2(void)
{
    GunUtils *guns = new GunUtils("example.xml");
    guns->print_guns();
    delete guns;

    cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

    return 1;
}
