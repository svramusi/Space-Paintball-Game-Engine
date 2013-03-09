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

#define XMAX 1000
#define XMIN -1000
#define YMAX 1000
#define YMIN -1000
#define ZMAX 1000
#define ZMIN 1


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
        void UpdateGraphicsObject(int id, int x, int y, int z);
        void InsertGraphicsObject(int x, int y, int z, char* file);
        graphicsInfo* getObject(int ID);



        void setCamPos(int x, int y,int z);
        void setPlayerPos(float x, float y,float z);
        bool OnInit();
 
        void OnEvent(SDL_Event* Event);
 
        void OnLoop();
 
        void OnRender();
        void OnRender(int x, int y);
        void OnClear();

        void OnCleanup();
        void Fire();

	void OnExit();
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
	void OnLButtonDown(int mX, int mY);
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);


};
#endif
