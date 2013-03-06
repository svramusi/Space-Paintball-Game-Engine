#ifndef _CAPP_H_
    #define _CAPP_H_

#include "SDL-1.2.15/include/SDL.h"

class CApp {
    private:
        bool            Running;

        SDL_Surface*    Surf_Display;
        SDL_Surface*    Surf_Test;

    public:
        CApp();

        int OnExecute();

    public:
        bool OnInit();

        void OnEvent(SDL_Event* Event);
	
	void OnExit();

        void OnLoop();

        void OnRender();

        void OnCleanup();
};

#endif
