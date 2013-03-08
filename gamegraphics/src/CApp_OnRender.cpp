#include "CApp.h"
 
void CApp::OnRender() {
    /*CSurface::OnDraw(Surf_Display, Surf_Test, LocX, LocY);
    //CSurface::OnDraw(Surf_Display, Surf_Test, 100, 100, 0, 0, 50, 50);
   //displays only part
    SDL_Flip(Surf_Display);*/
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
	float Rotate=0.0f; // A rotation value to be used to spin our polygon

	  glClearColor(0,0,0,0);

	  // Setup our screen
	 /* glViewport(0,0,800,600);
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  gluPerspective(45.0f,800.0f/600.0f,1.0f,500.0f);
	  glMatrixMode(GL_MODELVIEW);*/

	  // This loop will run until Esc is pressed

	   //   if(Keys[VK_ESCAPE]) // Esc Key


	     //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	     //glLoadIdentity(); // Reset current matrix (Modelview)


	 // glTranslatef(0,0,-500);
	//  glColor4f(1.0,1.0,1.0,1.0);

	 /* glBegin(GL_QUADS);
	  glVertex3f(0,  0,0);
	  glVertex3f(10, 0,0);
	  glVertex3f(10,10,0);
	  glVertex3f(0, 10,0);
	  glEnd();*/

  /* glBegin(GL_QUADS);
        glColor3f(1, 0, 0); glVertex3f(0, 0, 0);
        glColor3f(1, 1, 0); glVertex3f(100, 0,0);
        glColor3f(1, 1, 1); glVertex3f(100, 100, 0);
        glColor3f(1, 1, 1); glVertex3f(0, 100, 0);
        glEnd();
        glBegin(GL_QUADS);
        glColor3f(1, 0, 0); glVertex3f(LocX, LocY, 0);
        glColor3f(1, 1, 0); glVertex3f(100+LocX, LocY, 0);
        glColor3f(1, 0, 1); glVertex3f(100+LocX, 100+LocY, 0);
        glColor3f(1, 1, 1); glVertex3f(LocX, 100+LocY, 0);
    glEnd();*/



    for (std::vector<graphicsInfo>::iterator it = graphicsObjects.begin(); it != graphicsObjects.end(); ++it)
    	{
    		glBegin(GL_QUADS); //2D RENDERING
    				glColor3f(1, 0, 0); glVertex3f((*it).x, (*it).y, (*it).z);
    		        glColor3f(1, 1, 0); glVertex3f(100+(*it).x, (*it).y, (*it).z);
    		        glColor3f(1, 0, 1); glVertex3f(100+(*it).x, 100+(*it).y, (*it).z);
    		        glColor3f(1, 1, 1); glVertex3f((*it).x, 100+(*it).y, (*it).z);
    		glEnd();
    				//glTranslatef((*it).x,(*it).y,-(*it).z);
    				/*glTranslatef(-260,-100,-500);
    				//x goes from -110 to 110 (-10)
    				glBegin(GL_QUADS); //3D RENDERING
    	    				glColor3f(1, 0, 0); glVertex3f(0,0, 0);
    	    		        glColor3f(1, 1, 0); glVertex3f(10,0, 0);
    	    		        glColor3f(1, 0, 1); glVertex3f(10,10, 0);
    	    		        glColor3f(1, 1, 1); glVertex3f(0,10, 0);
    	    		glEnd();*/
    	}



        SDL_GL_SwapBuffers();
}
/*void CApp::OnRender(int x, int y) {
    CSurface::OnDraw(Surf_Display, Surf_Test, x, y);
    //CSurface::OnDraw(Surf_Display, Surf_Test, 100, 100, 0, 0, 50, 50);
   //displays only part
    SDL_Flip(Surf_Display);
}*/

void CApp::OnClear(){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
}
