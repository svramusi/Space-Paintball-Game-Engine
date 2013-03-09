#include "CApp.h"
#include <stdio.h>


CApp::CApp() {

    Surf_Test = NULL;
    Surf_Display = NULL;
    latestID = 0;
    Running = true;
    LocX = 20;
    LocY= 90;
    LocZ= 0;

    pLocX = 0;
    pLocY= 0;
    pLocZ= 0;
}
/*CApp::CApp(int playerX, int playerZ) {

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
}*/

void CApp::Fire()
{
	//Need a call in client
	/*position = px,y,z
	vector = cx,y,z
	rest filled in on client*/

}

void CApp::setCamPos(int xP, int yP, int yZ) //Cam Position
{
	LocX+=  xP*.1;
	if(LocX > 360)
		LocX -= 360.0;
	LocY +=yP*.1;
	if(LocY > 360)
			LocY -= 360.0;
	//LocZ +=yZ; //Z is left button
}

void CApp::setPlayerPos(float xP, float yP, float yZ) //PLayer Position
{

	pLocX+=  (xP*.02);
	if(pLocX > XMAX)
			pLocX = XMAX;
	if(pLocX < XMIN)
				pLocX = XMIN;

	/* May be needed y always independant

	LocX+=  xP;
	LocX %= 360; */

	pLocZ +=(yZ *.02); //Z is left button
	if(pLocZ > ZMAX){
				pLocZ = ZMAX;
				LocZ = ZMAX;  //adjust Z location with player
	}
		if(LocZ < ZMIN){
				pLocZ = ZMIN;
				LocZ = ZMIN;
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
