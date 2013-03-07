#include "CApp.h"
 
void CApp::OnRender() {
    /*CSurface::OnDraw(Surf_Display, Surf_Test, LocX, LocY);
    //CSurface::OnDraw(Surf_Display, Surf_Test, 100, 100, 0, 0, 50, 50);
   //displays only part
    SDL_Flip(Surf_Display);*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glBegin(GL_QUADS);
        glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
        glColor3f(1, 1, 0); glVertex3f(100, 0, 0);
        glColor3f(1, 0, 1); glVertex3f(100, 100, 0);
        glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
        glColor3f(1, 0, 0); glVertex3f(LocX, LocY, 0);
        glColor3f(1, 1, 0); glVertex3f(100+LocX, LocY, 0);
        glColor3f(1, 0, 1); glVertex3f(100+LocX, 100+LocY, 0);
        glColor3f(1, 1, 1); glVertex3f(LocX, 100+LocY, 0);
    glEnd();

    SDL_GL_SwapBuffers();
}
void CApp::OnRender(int x, int y) {
    CSurface::OnDraw(Surf_Display, Surf_Test, x, y);
    //CSurface::OnDraw(Surf_Display, Surf_Test, 100, 100, 0, 0, 50, 50);
   //displays only part
    SDL_Flip(Surf_Display);
}

void CApp::OnClear(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
