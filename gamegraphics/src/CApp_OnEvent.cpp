
#include "CApp.h"
#include "CEvent.h"

void CApp::OnEvent(SDL_Event* Event) {
    CEvent::OnEvent(Event);
}

void CApp::OnMouseMove(int mX, int mY, int relX, int relY, bool Left,bool Right,bool Middle) {

	if(!Left){
		setCamPos (relX, relY,0); //look left, look up

	}
	if(Left){
		setPlayerPos (relX, 0,relY); //left right straff, and forward back
	}

}

void CApp::OnLButtonDown(int mX, int mY)
{

	OnClear();
}

void CApp::OnKeyDown(SDLKey sym, SDLMod mod, Uint16 unicode) {
	switch(sym) {
	        case SDLK_UP: {
	        	setPos(LocX,--LocY,0);
	        break;
	        }
	        case SDLK_DOWN: {
	        	setPos(LocX,++LocY,0);
	        	        break;
	        }
	        case SDLK_LEFT: {
	        	setPos(--LocX,LocY,0);
	        	        break;
	        }
	        case SDLK_RIGHT: {
	        	setPos(++LocX,LocY,0);
	        	        break;
	        }
	        default: {
	        break;
	        }
	}
}
