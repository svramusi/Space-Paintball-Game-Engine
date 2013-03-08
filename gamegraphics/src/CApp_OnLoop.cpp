#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "CApp.h"


void CApp::OnLoop() {

	srand(time(0));

	  /* generate secret number between 1 and 10: */


	for (std::vector<graphicsInfo>::iterator it = graphicsObjects.begin(); it != graphicsObjects.end(); ++it)
	    	{
				UpdateGraphicsObject((*it).ID , rand() % 639 + 1, rand() % 480 + 1,rand()%400);
	    	}
}
