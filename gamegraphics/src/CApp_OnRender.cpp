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



	   glLoadIdentity();
	   glTranslatef(pLocX, -1, -20-pLocZ);
	    glRotatef(LocX,1.0,0.0,0.0);
	    // rotation about Y axis
	    glRotatef(LocY,0.0,1.0,0.0);
	    // rotation about Z axis
	   // glRotatef(0,0.0,0.0,1.0);


	    glBegin(GL_QUADS);        // Draw The Cube Using quads
	      glColor3f(0.0f,1.0f,0.0f);    // Color Blue
	      glVertex3f( XMAX, YMAX,ZMIN);    // Top Right Of The Quad (Top)
	      glVertex3f(XMIN, YMAX,ZMIN);    // Top Left Of The Quad (Top)
	      glVertex3f(XMIN, YMAX, ZMAX);    // Bottom Left Of The Quad (Top)
	      glVertex3f( XMAX, YMAX, ZMAX);    // Bottom Right Of The Quad (Top)

	      glColor3f(1, 0, 0);glVertex3f( XMAX,YMIN, ZMAX);    // Top Right Of The Quad (Bottom)
	      glColor3f(1, 1, 0);glVertex3f(XMIN,YMIN, ZMAX);    // Top Left Of The Quad (Bottom)
	      glColor3f(1, 0, 1);glVertex3f(XMIN,YMIN,ZMIN);    // Bottom Left Of The Quad (Bottom)
	      glColor3f(1, 1, 1);glVertex3f( XMAX,YMIN,ZMIN);    // Bottom Right Of The Quad (Bottom)
	      glColor3f(1.0f,0.0f,0.0f);    // Color Red
	      glVertex3f( XMAX, YMAX, ZMAX);    // Top Right Of The Quad (Front)
	      glVertex3f(XMIN, YMAX, ZMAX);    // Top Left Of The Quad (Front)
	      glVertex3f(XMIN,YMIN, ZMAX);    // Bottom Left Of The Quad (Front)
	      glVertex3f(XMAX,YMIN,ZMAX);    // Bottom Right Of The Quad (Front)
	      glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
	      glVertex3f( XMAX,YMIN,ZMIN);    // Top Right Of The Quad (Back)
	      glVertex3f(XMIN,YMIN,ZMIN);    // Top Left Of The Quad (Back)
	      glVertex3f(XMIN, YMAX,ZMIN);    // Bottom Left Of The Quad (Back)
	      glVertex3f(XMAX, YMAX,ZMIN);    // Bottom Right Of The Quad (Back)
	      glColor3f(0.0f,0.0f,1.0f);    // Color Blue
	      glVertex3f(XMIN, YMAX, ZMAX);    // Top Right Of The Quad (Left)
	      glVertex3f(XMIN, YMAX,ZMIN);    // Top Left Of The Quad (Left)
	      glVertex3f(XMIN,YMIN,ZMIN);    // Bottom Left Of The Quad (Left)
	      glVertex3f(XMIN,YMIN, ZMAX);    // Bottom Right Of The Quad (Left)
	      glColor3f(1.0f,0.0f,1.0f);    // Color Violet
	      glVertex3f( XMAX, YMAX,ZMIN);    // Top Right Of The Quad (Right)
	      glVertex3f( XMAX, YMAX, ZMAX);    // Top Left Of The Quad (Right)
	      glVertex3f( XMAX,YMIN, ZMAX);    // Bottom Left Of The Quad (Right)
	      glVertex3f( XMAX,YMIN,ZMIN);    // Bottom Right Of The Quad (Right)
	    glEnd();            // End Drawing The Cube

	glFlush();



	/*  glBegin(GL_QUADS);  //RENDER LEFT WALL
			      	    				glColor3f( 0.5f, 0.35f, 0.05f); glVertex3f(XMIN,YMIN, ZMIN);
			      	    		        glColor3f (0.5f, 0.35f, 0.05f); glVertex3f(XMIN,YMIN,ZMAX);
			      	    		        glColor3f (0.5f, 0.35f, 0.05f); glVertex3f(XMIN,YMAX,ZMIN);
			      	    		        glColor3f (0.5f, 0.35f, 0.05f); glVertex3f(XMIN,YMAX,ZMAX);
		glEnd(); //RENDER LEFT WALL*/
	  /*	  glTranslatef(0,0,-1);
		glBegin(GL_QUADS);  //RENDER Floor WALL
					      	    				glColor3f(1,0,0); glVertex3f(XMIN,0, ZMIN);
					      	    		        glColor3f (1,1,0); glVertex3f(XMAX,0,ZMIN);
					      	    		        glColor3f (1,0,1); glVertex3f(XMAX,0,ZMAX);
					      	    		        glColor3f (1,1,1); glVertex3f(XMIN,0,ZMAX);
				glEnd(); //RENDER Floor WALL*/

	  	  	  	  	 /* 	 glTranslatef(0,0,-50);
	      				//glTranslatef(-260,-100,-500);
	      				//x goes from -110 to 110 (-10)
	      				glBegin(GL_QUADS); //3D RENDERING
	      	    				glColor3f(1, 0, 0); glVertex3f(0,0, 0);
	      	    		        glColor3f(1, 1, 0); glVertex3f(10,0, 0);
	      	    		        glColor3f(1, 0, 1); glVertex3f(10,10, 0);
	      	    		        glColor3f(1, 1, 1); glVertex3f(0,10, 0);
	      	    		glEnd();*/
   /* for (std::vector<graphicsInfo>::iterator it = graphicsObjects.begin(); it != graphicsObjects.end(); ++it)
    	{
    		glBegin(GL_QUADS); //2D RENDERING
    				glColor3f(1, 0, 0); glVertex3f((*it).x, (*it).y, (*it).z);
    		        glColor3f(1, 1, 0); glVertex3f(100+(*it).x, (*it).y, (*it).z);
    		        glColor3f(1, 0, 1); glVertex3f(100+(*it).x, 100+(*it).y, (*it).z);
    		        glColor3f(1, 1, 1); glVertex3f((*it).x, 100+(*it).y, (*it).z);
    		glEnd();
    				glTranslatef((*it).x,(*it).y,-(*it).z);
    				//glTranslatef(-260,-100,-500);
    				//x goes from -110 to 110 (-10)
    				glBegin(GL_QUADS); //3D RENDERING
    	    				glColor3f(1, 0, 0); glVertex3f(0,0, 0);
    	    		        glColor3f(1, 1, 0); glVertex3f(10,0, 0);
    	    		        glColor3f(1, 0, 1); glVertex3f(10,10, 0);
    	    		        glColor3f(1, 1, 1); glVertex3f(0,10, 0);
    	    		glEnd();
    	}*/



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
