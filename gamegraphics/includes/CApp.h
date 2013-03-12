#ifndef _CAPP_H_
    #define _CAPP_H_

#include <vector>
#include "SDL-1.2.15/include/SDL.h"
//#include "SDL-1.2.15/include/SDL_opengl.h"
#include <gl.h>
#include <glu.h>
#include <glut.h>
#include "CEvent.h"
#include "CSurface.h"
#include "graphicsinfo.h"
#include "CollidableObject.h"
#include "AABBClass.h"
#include "SphereClass.h"

#define XMAX 1000
#define XMIN -1000
#define YMAX 100
#define YMIN 0
#define ZMAX 1000
#define ZMIN -100

#define ZMAX2 -1000
#define ZMIN2 -1

#define MINYANG 25
#define MAXYANG 140

#define SCREENX 1024
#define SCREENY 768


class CApp : public CEvent {
    private:
        bool            Running;
 
        SDL_Surface*    Surf_Display;
 
        SDL_Surface*    Surf_Test;
        float 			LocX, LocY, LocZ;
        float				pLocX, pLocY, pLocZ;
        int 			latestID;
        std::vector<graphicsInfo> graphicsObjects;
 
    public:
        CApp();
 
        int OnExecute();
        void UpdateGraphicsObject(int id, Point newCenter);
     void   DeleteObject(int ID);
        int CalcVel(int dir, float force);
        graphicsInfo* getObject(int ID);
        void AddWalls();
        void drawCircle(float radius, int x, int y, int z);


        void setCamPos(int x, int y,int z);
        void setPlayerPos(float x, float y,float z);
        bool OnInit();
 
        void OnEvent(SDL_Event* Event);
 
        void OnLoop();
        void RenderIt(CollidableObject *obj);
        void UpdateWall(int l, int w, int wx,int wy, int wz);
        void UpdatePlayer();
        void OnRender();
        void OnRender(int x, int y);
        void OnClear();
        void InsertGraphicsObject(CollidableObject *obj);
        void OnCleanup();
        void Fire();

	void OnExit();
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
	void OnLButtonDown(int mX, int mY);
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);


};
#endif
