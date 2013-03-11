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

#define SCREENW 640
#define SCREENL 480
#define SCREEND 1000

class CApp : public CEvent {
    private:
        bool            Running;
 
        SDL_Surface*    Surf_Display;
 
        SDL_Surface*    Surf_Test;
        int 			LocX, LocY, LocZ;
        int				pLocX, pLocY, pLocZ;
        int 			latestID;
        std::vector<graphicsInfo> graphicsObjects;
 
    public:
        CApp();
 
        int OnExecute();
        void UpdateGraphicsObject(int id, int x, int y, int z);
        void InsertGraphicsObject(int x, int y, int z, char* file);
        graphicsInfo* getObject(int ID);



        void setCamPos(int x, int y,int z);
        void setPlayerPos(int x, int y,int z);
        bool OnInit();
 
        void OnEvent(SDL_Event* Event);
 
        void OnLoop();
 
        void OnRender();
        void OnRender(int x, int y);
        void OnClear();

        void OnCleanup();

	void OnExit();
	void OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle);
	void OnLButtonDown(int mX, int mY);
	void OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode);


};
#endif
