#include "CApp.h"
#include <stdio.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */


CApp::CApp() {

    Surf_Test = NULL;
    Surf_Display = NULL;
    latestID = 0;
    Running = true;
    LocX = 0;
    LocY= 0;
    LocZ= 0;

    pLocX = 0;
    pLocY= 90;
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


//THIS MAY NEED WORK
int CApp::CalcVel(int dir, float force)
{
    return 0;
}

void CApp::AddWalls()
{
    srand(time(0));
    int xl = rand()%(XMAX-XMIN)+XMIN;
    int yl = rand()%(YMAX-YMIN)+YMIN;
    int zl = rand()%(ZMAX-ZMIN)+ZMIN;

    for(int x= 0; x <10; x++)
    {
        UpdateWall(rand() % 10,rand() % 10,xl,yl,zl);
    }

}

void CApp::Fire()
{
    //100 m/s
    //.5 g
    //Need a call in client
    /*position = px,y,z
    vector = cx,y,z
    rest filled in on client*/
    //Radius, Position X,Y,Z, Angle X,Y,Z, mass, movable , no angular velocity

    //Client.addObject(5,pLocX, pLocY, pLocZ, 0, 100,0,.5, true,0,0,0);

}

void CApp::UpdateWall(int l, int w, int wx,int wy, int wz)
{//assume 70 kg person
    //height,width Position X,Y,Z, Angle X,Y,Z, mass, movable , no angular velocity
    //Client.addObject(l,w,wy, wy, wz, 0, 0,0,70, false,0,0,0);
}

void CApp::UpdatePlayer()
{//assume 70 kg person
    //height,width Position X,Y,Z, Angle X,Y,Z, mass, movable , no angular velocity
//  Client.addObject(200,100,pLocX, pLocY, pLocZ, 0, 0,0,70, false,0,0,0);
}

void CApp::setCamPos(int xP, int yP, int yZ) //Cam Position
{//not sure but its backwards
    LocX+=  yP * .1;
    if(LocX > 360) LocX -= 360.0;

    LocY +=xP * .1;
    if(LocY > 360) LocY -= 360.0;
    //LocZ +=yZ; //Z is left button
}


void CApp::setPlayerPos(float xP, float yP, float yZ) //PLayer Position
{
    printf("x%d  y%d\n", xP, yZ);
    pLocX += (xP);

    if(pLocX > XMAX)
        pLocX = XMAX-2;

    if(pLocX < XMIN)
        pLocX = XMIN+2;

    /* May be needed y always independant
    LocX+=  xP;
    LocX %= 360; */

    pLocZ +=(yZ ); //Z is left button
    if(pLocZ < ZMAX){
        pLocZ = ZMAX;
        LocZ = ZMAX;  //adjust Z location with player
    }

    if(LocZ > ZMIN){
        pLocZ = ZMIN;
        LocZ = ZMIN;
    }

    UpdatePlayer();
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

void CApp::InsertGraphicsObject(CollidableObject *obj){
    graphicsInfo newItem;

    newItem.ID = latestID;
    latestID++;

    newItem.obj = obj;

    graphicsObjects.push_back(newItem);
}

void CApp::UpdateGraphicsObject(int id, Point newCenter){
    graphicsInfo *newItem = getObject(id);
    newItem->obj->setCenter(newCenter);
}

void CApp::DeleteObject(int ID)
{
    int cnt =0;
    for (std::vector<graphicsInfo>::iterator it = graphicsObjects.begin(); it != graphicsObjects.end(); ++it)
    {
         cnt++;
         if((*it).ID == ID)
            graphicsObjects.erase(it); //will this kill the iterator?
    }
}

int main(int argc, char* argv[]) {
    CApp theApp;
    return theApp.OnExecute();
}
