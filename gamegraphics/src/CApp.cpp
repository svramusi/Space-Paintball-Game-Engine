#include "CApp.h"
#include <stdio.h>


CApp::CApp() {

    Surf_Test = NULL;
    Surf_Display = NULL;
    latestID = 0;
    Running = true;
    LocX = 0;
    LocY= 0;
    LocZ= 0;

    pLocX = 0;
    pLocY= 0;
    pLocZ= 0;
}
CApp::CApp(int playerX, int playerZ) {

    Surf_Test = NULL;
    Surf_Display = NULL;
    latestID = 0;
    Running = true;
    LocX = 0;
    LocY= 0;
    LocZ= playerZ;

    pLocX = playerX;
    pLocY= 0;
    pLocZ= playerZ;
}

void CApp::Fire()
{
	//Need a call in client
	/*position = px,y,z
	vector = cx,y,z
	rest filled in on client*/

}

void CApp::setCamPos(int xP, int yP, int yZ) //Cam Position
{
	LocX+=  xP;
	LocX %= 360;
	LocY +=yP;
	LocY %= 360;
	//LocZ +=yZ; //Z is left button
}

void CApp::setPlayerPos(int xP, int yP, int yZ) //PLayer Position
{
	int xrange = SCREENW/2;
	int zrange = SCREEND;
	pLocX+=  xP;
	if(pLocX > xrange)
			pLocX = xrange;
	if(pLocX < -xrange)
				pLocX = -xrange;

	/* May be needed y always independant

	LocX+=  xP;
	LocX %= 360; */

	pLocZ +=yZ; //Z is left button
	if(pLocZ > zrange){
				pLocX = zrange;
				LocX = zrange;  //adjust Z location with player
	}
		if(LocZ < 1){
				pLocZ = 1;
				LocX = 1;
		}

		//CALL Update player Position
}

int CApp::OnExecute() {
	//printf("Starting/n");
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
    	//printf("WHILE RUNNING /N");
        while(SDL_PollEvent(&Event)) {
            OnEvent(&Event);
        }

        OnLoop();
        OnRender();
    }

    OnCleanup();

    return 0;
}


void CApp::OnExit() {
    Running = false;
}

graphicsInfo* CApp::getObject(int ID)
{
	for (std::vector<graphicsInfo>::iterator it = graphicsObjects.begin(); it != graphicsObjects.end(); ++it)
	{
		if((*it).ID == ID)
			return &(*it);
	}
	return NULL;
}

void CApp::InsertGraphicsObject(int x, int y, int z, char* file){
		graphicsInfo newItem;

	    newItem.ID = latestID;
	    newItem.x= x;
	    newItem.y= y;
	    newItem.z = z;
	    newItem.File = file;

	    graphicsObjects.push_back(newItem);
	    latestID++;
}

void CApp::UpdateGraphicsObject(int id, int x, int y, int z){
		graphicsInfo *newItem = getObject(id);
	    newItem->x= x;
	    newItem->y= y;
	    newItem->z = z;

}

int main(int argc, char* argv[]) {
    CApp theApp;
    theApp.InsertGraphicsObject(1,1,1,"");
    theApp.InsertGraphicsObject(10,10,10,"");
    theApp.InsertGraphicsObject(100,100,100,"");
    theApp.InsertGraphicsObject(500,500,1,"");
    return theApp.OnExecute();
}
