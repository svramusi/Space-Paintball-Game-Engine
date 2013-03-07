#include "CApp.h"
#include <stdio.h>


CApp::CApp() {

    Surf_Test = NULL;
    Surf_Display = NULL;
    latestID = 0;
    Running = true;
}
void CApp::setPos(int xP, int yP) //Player Position
{
	LocX= xP;
	LocY = yP;

}

int CApp::OnExecute() {
	printf("Starting/n");
    if(OnInit() == false) {
        return -1;
    }

    SDL_Event Event;

    while(Running) {
    	printf("WHILE RUNNING /N");
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

    return theApp.OnExecute();
}
