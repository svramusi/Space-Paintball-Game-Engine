#include "CApp.h"
 
void CApp::OnRender() {
    CSurface::OnDraw(Surf_Display, Surf_Test, LocX, LocY);
    //CSurface::OnDraw(Surf_Display, Surf_Test, 100, 100, 0, 0, 50, 50);
   //displays only part
    SDL_Flip(Surf_Display);
}
void CApp::OnRender(int x, int y) {
    CSurface::OnDraw(Surf_Display, Surf_Test, x, y);
    //CSurface::OnDraw(Surf_Display, Surf_Test, 100, 100, 0, 0, 50, 50);
   //displays only part
    SDL_Flip(Surf_Display);
}

void CApp::OnClear(){

	SDL_FillRect(Surf_Display, NULL, SDL_MapRGB(Surf_Test->format, 0, 0, 0));
}
