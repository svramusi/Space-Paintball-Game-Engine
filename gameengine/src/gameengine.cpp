//============================================================================
// Name        : gameengine.cpp
// Author      : Ramusivich, Taylor, Patel
// Version     :
// Copyright   : 2013 Drexel University
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include "gun_utils.h"

using namespace std;

int main() {
    cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	GunUtils *guns = new GunUtils("example.xml");
	guns->print_guns();
	delete guns;

    return 0;
}
