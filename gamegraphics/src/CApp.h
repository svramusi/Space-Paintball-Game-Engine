#ifndef _CAPP_H_
    #define _CAPP_H_

#include "SDL-1.2.15/include/SDL.h"
#include "CEvent.h"
#include "CSurface.h"

class CApp : public CEvent {
    private:
        bool            Running;
 
        SDL_Surface*    Surf_Display;
 
        SDL_Surface*    Surf_Test;
        int 			LocX, LocY;
 
    public:
        CApp();
 
        int OnExecute();
 
    public:
        void setPos(int x, int y);
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
