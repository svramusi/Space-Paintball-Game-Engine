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

	  //Handles Camera movement
	  //gluLookAt((double)pLocX,(double)pLocY,(double)pLocZ,(double)LocX,(double)LocY,(double)LocZ,0.0,1.0,0.0);

	  //FLOOR

	//  glTranslatef(0, 0, -3);
	 /* glRotatef(5, 1, 0, 0);
	  glRotatef(90, 0, 1, 0);
	  glColor3f(1.0, 1.0, 1.0);
	  glBegin(GL_LINES);
	  for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
	    glVertex3f(i, 0, 2.5); glVertex3f(i, 0, -2.5);
	    glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);

	    glVertex3f(2.5, 0, -i); glVertex3f(-2.5, 0, -i);
	    glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);

	  } //Floor
	  glEnd();

	  glFlush();*/



	  	 // glLoadIdentity();
	  //wall

	 	//  glTranslatef(0, 0, -3);
	 	 // glRotatef(110, 1, 0, 0);
	 	 // glRotatef(90, 0, 1, 0);
	 	//  glRotatef(90, 0, 0, 1);
	 	/*  glColor3f(0.0, 1.0, 1.0);
	 	  glBegin(GL_LINES);
	 	  for (GLfloat i = -2.5; i <= 2.5; i += 0.25) {
	 	    glVertex3f(i, 0, 2.5); glVertex3f(i, 0, -2.5);
	 	    glVertex3f(2.5, 0, i); glVertex3f(-2.5, 0, i);

	 	  } //Floor
	 	  glEnd();

	 	  glFlush();*/

	   glLoadIdentity();
	   glTranslatef(pLocX, -1, -20-pLocZ);
	    glRotatef(20,1.0,0.0,0.0);
	    // rotation about Y axis
	    glRotatef(90,0.0,1.0,0.0);
	    // rotation about Z axis
	    glRotatef(0,0.0,0.0,1.0);
	  glBegin(GL_QUADS);        // Draw The Cube Using quads
	    glColor3f(0.0f,1.0f,0.0f);    // Color Blue
	    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Top)
	    glVertex3f(-1.0f, 1.0f,-1.0f);    // Top Left Of The Quad (Top)
	    glVertex3f(-1.0f, 1.0f, 1.0f);    // Bottom Left Of The Quad (Top)
	    glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Top)

	    glColor3f(0.0f,1.0f,0.0f);    // Color Blue
	    	    glVertex3f( -1.0f,-1.0f, 1.0f);    // Top Right Of The Quad (Bottom)
	    	    glVertex3f( 1.0f,-1.0f, 1.0f);    // Top Left Of The Quad (Bottom)
	    	    glVertex3f(-1.0f, 1.0f, -1.0f);    // Bottom Left Of The Quad (Bottom)
	    	    glVertex3f( 1.0f, 1.0f, 1.0f);    // Bottom Right Of The Quad (Bottom)

	    glColor3f(1.0f,0.0f,0.0f);    // Color Red
	    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Right Of The Quad (Front)
	    glVertex3f(-1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Front)
	    glVertex3f(-1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Front)
	    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Right Of The Quad (Front)
	    glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
	    glVertex3f( 1.0f,-1.0f,-1.0f);    // Top Right Of The Quad (Back)
	    glVertex3f(-1.0f,-1.0f,-1.0f);    // Top Left Of The Quad (Back)
	    glVertex3f(-1.0f, 1.0f,-1.0f);    // Bottom Left Of The Quad (Back)
	    glVertex3f( 1.0f, 1.0f,-1.0f);    // Bottom Right Of The Quad (Back)

	    glColor3f(1.0f,0.0f,1.0f);    // Color Violet
	    glVertex3f( 1.0f, 1.0f,-1.0f);    // Top Right Of The Quad (Right)
	    glVertex3f( 1.0f, 1.0f, 1.0f);    // Top Left Of The Quad (Right)
	    glVertex3f( 1.0f,-1.0f, 1.0f);    // Bottom Left Of The Quad (Right)
	    glVertex3f( 1.0f,-1.0f,-1.0f);    // Bottom Right Of The Quad (Right)
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
