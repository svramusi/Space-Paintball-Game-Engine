#include "CApp.h"
#include "AABBClass.h"
#include <math.h>
#include "CollidableObject.h"
#include "AABBClass.h"
#include "SphereClass.h"

#include <typeinfo>


#define red {0xff, 0x00, 0x00}
#define yellow {0xff, 0xff, 0x00}
#define magenta {0xff, 0, 0xff}
GLubyte texture[][3] = {
    red, yellow,
    yellow, red,
};

const float DEG2RAD = 3.14159/180;

void CApp::drawCircle(float radius, int x, int y, int z)
{
    glClear(GL_COLOR_BUFFER_BIT);

    double angle = 2*  3.14/100 ;

    glPolygonMode( GL_FRONT, GL_FILL );
    glColor3f(0.2, 0.5, 0.5 );
    glBegin(GL_POLYGON);

    double angle1=0.0;
    glVertex3d( x+radius * cos(0.0) ,y+radius * sin(0.0),z);

    for (int i=0 ; i< 100 ;i++)
    {
        glVertex3d(x+radius * cos(angle1), y+ radius *sin(angle1),z);
        angle1 += angle ;
    }

    glEnd();
    glFlush();
}
void CApp::RenderIt(CollidableObject *obj)
{
    int cx = obj->getCenter().x;
    int cy = obj->getCenter().y;
    int cz = obj->getCenter().z;

//this might need to be if(typeid(AABB) == typeid(*(obj)))
    if(typeid(AABB) == typeid(obj))
    {
        AABB *tempAABB = dynamic_cast<AABB*>(obj);
        int xr = tempAABB->getXRadius()/2;
        int yr = tempAABB->getYRadius()/2;

        glBegin(GL_QUADS);        // Draw The Cube Using quads

        //may need to figure colore dif for walls /player
        glColor3f(1.0f,0.0f,0.0f);    // Color Red
        glVertex3f( cx+xr, cy+yr, cz);    // Top Right Of The Quad (Front)
        glVertex3f(cx-xr, cy+yr, cz);    // Top Left Of The Quad (Front)
        glVertex3f(cx-xr,cy-yr, cz);    // Bottom Left Of The Quad (Front)
        glVertex3f(cx+xr,cy-yr,cz);    // Bottom Right Of The Quad (Front)

        glEnd();
    }
    else if(typeid(Sphere) == typeid(obj)) //same comment here as for if statement
    {
        Sphere *sphere = dynamic_cast<Sphere*>(obj);
        float radius = sphere->getRadius();
        drawCircle(radius,cx,cy,cz);
    }
}

void CApp::OnRender() {
    /*CSurface::OnDraw(Surf_Display, Surf_Test, LocX, LocY);
    //CSurface::OnDraw(Surf_Display, Surf_Test, 100, 100, 0, 0, 50, 50);
    //displays only part
    SDL_Flip(Surf_Display);*/

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float Rotate=0.0f; // A rotation value to be used to spin our polygon

    glClearColor(0,0,0,0);

    //glLoadIdentity();


/*
    xtrans = -xpos;
    ztrans = -zpos;
    ytrans = -walkbias-0.25f;
    sceneroty = 360.0f - yrot;


    glRotatef(lookupdown, 1.0f, 0, 0);
    glRotatef(sceneroty, 0, 1.0f, 0);

    glTranslatef(xtrans, ytrans, ztrans);
*/



    glTranslatef(pLocX, -1, -1);

    glRotatef(LocX, 1.0, 0.0, 0.0);
    glRotatef(LocY, 0.0, 1.0, 0.0); // rotation about Y axis




    // rotation about Z axis
    // glRotatef(0,0.0,0.0,1.0);


       /* glEnable(GL_TEXTURE_2D);
          glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
          glTexImage2D(GL_TEXTURE_2D,
                       0,                    // level 0
                       3,                    // use only R, G, and B components
                       2, 2,                 // texture has 2x2 texels
                       0,                    // no border
                       GL_RGB,               // texels are in RGB format
                       GL_UNSIGNED_BYTE,     // color components are unsigned bytes
                       texture);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
          glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
*/


        //drawCircle(20,0,0,0);





glBegin(GL_QUADS);
// Floor *-/
glVertex3f(-1,-1,-1);
glVertex3f(1,-1,-1);
glVertex3f(1,-1,1);
glVertex3f(-1,-1,1);
// Ceiling *-/
glVertex3f(-1,1,-1);
glVertex3f(1,1,-1);
glVertex3f(1,1,1);
glVertex3f(-1,1,1);
// Walls *-/

glVertex3f(-1,-1,1);
glVertex3f(1,-1,1);
glVertex3f(1,1,1);
glVertex3f(-1,1,1);


/*
glVertex3f(-1,-1,-1);
glVertex3f(1,-1,-1);
glVertex3f(1,1,-1);
glVertex3f(-1,1,-1);

glVertex3f(1,1,1);
glVertex3f(1,-1,1);
glVertex3f(1,-1,-1);
glVertex3f(1,1,-1);

glVertex3f(-1,1,1);
glVertex3f(-1,-1,1);
glVertex3f(-1,-1,-1);
glVertex3f(-1,1,-1);
*/


glEnd(); 





        glBegin(GL_QUADS);
        //glNormal3f( 0.0f, 0.0f, 1.0f);


/*
        //DRAW THE CEILING
        glColor3f(0.0f,1.0f,0.0f);    // Color Green
        glVertex3f(XMIN, YMAX, ZMIN);    // Top Right Of The Quad (Top)
        glVertex3f(XMAX, YMAX, ZMIN);    // Top Left Of The Quad (Top)
        glVertex3f(XMAX, YMAX, ZMAX);    // Bottom Left Of The Quad (Top)
        glVertex3f(XMIN, YMAX, ZMAX);    // Bottom Right Of The Quad (Top)

        //DRAW THE FLOOR
        //glColor3f(1, 0, 0);
        glVertex3f(XMIN, YMIN, ZMIN);    // Top Right Of The Quad (Bottom)
        glVertex3f(XMAX, YMIN, ZMIN);    // Top Left Of The Quad (Bottom)
        glVertex3f(XMAX, YMIN, ZMAX);    // Bottom Left Of The Quad (Bottom)
        glVertex3f(XMIN, YMIN, ZMAX);    // Bottom Right Of The Quad (Bottom)
*/


        //Should be the wall we look at at the start

        glColor3f(1.0f, 0.0f, 0.0f);    // Color Red
        glVertex3f(-10, -10, 10);    // Top Right Of The Quad (Front)
        glVertex3f(10, -10, 10);    // Top Left Of The Quad (Front)
        glVertex3f(10, 10, 10);    // Bottom Left Of The Quad (Front)
        glVertex3f(-10, 10, 10);    // Bottom Right Of The Quad (Front)


/*
        //both walls?
        glColor3f(1.0f,1.0f,0.0f);    // Color Yellow
        glVertex3f( XMAX,YMIN,ZMIN);    // Top Right Of The Quad (Back)
        glVertex3f(XMIN,YMIN,ZMIN);    // Top Left Of The Quad (Back)
        glVertex3f(XMIN, YMAX,ZMIN);    // Bottom Left Of The Quad (Back)
        glVertex3f(XMAX, YMAX,ZMIN);    // Bottom Right Of The Quad (Back)
*/



/*
        //Nothing?
        glColor3f(0.0f,0.0f,1.0f);    // Color Blue
        glVertex3f(XMIN, YMAX, ZMAX);    // Top Right Of The Quad (Left)
        glVertex3f(XMIN, YMAX,ZMIN);    // Top Left Of The Quad (Left)
        glVertex3f(XMIN,YMIN,ZMIN);    // Bottom Left Of The Quad (Left)
        glVertex3f(XMIN,YMIN, ZMAX);    // Bottom Right Of The Quad (Left)
*/


/*

        //Nothing?
        glColor3f(1.0f,0.0f,1.0f);    // Color Violet
        glVertex3f( XMAX, YMAX,ZMIN);    // Top Right Of The Quad (Right)
        glVertex3f( XMAX, YMAX, ZMAX);    // Top Left Of The Quad (Right)
        glVertex3f( XMAX,YMIN, ZMAX);    // Bottom Left Of The Quad (Right)
        glVertex3f( XMAX,YMIN,ZMIN);    // Bottom Right Of The Quad (Right)
*/



        //render game objects
        for (std::vector<graphicsInfo>::iterator it = graphicsObjects.begin(); it != graphicsObjects.end(); ++it)
        {
            glBegin(GL_QUADS); //2D RENDERING

            glColor3f(1, 0, 0);
            glVertex3f((*it).x, (*it).y, (*it).z); //left

            glColor3f(1, 1, 0);
            glVertex3f(100+(*it).x, (*it).y, (*it).z); //right

            glColor3f(1, 0, 1);
            glVertex3f(100+(*it).x, 100+(*it).y, (*it).z);

            glColor3f(1, 1, 1);
            glVertex3f((*it).x, 100+(*it).y, (*it).z);

            glEnd();
        }

        glEnd();            // End Drawing The Cube
        glFlush();



    /*  glBegin(GL_QUADS);  //RENDER LEFT WALL
                                        glColor3f( 0.5f, 0.35f, 0.05f); glVertex3f(XMIN,YMIN, ZMIN);
                                        glColor3f (0.5f, 0.35f, 0.05f); glVertex3f(XMIN,YMIN,ZMAX);
                                        glColor3f (0.5f, 0.35f, 0.05f); glVertex3f(XMIN,YMAX,ZMIN);
                                        glColor3f (0.5f, 0.35f, 0.05f); glVertex3f(XMIN,YMAX,ZMAX);
        glEnd(); //RENDER LEFT WALL*/
      /*      glTranslatef(0,0,-1);
        glBegin(GL_QUADS);  //RENDER Floor WALL
                                                glColor3f(1,0,0); glVertex3f(XMIN,0, ZMIN);
                                                glColor3f (1,1,0); glVertex3f(XMAX,0,ZMIN);
                                                glColor3f (1,0,1); glVertex3f(XMAX,0,ZMAX);
                                                glColor3f (1,1,1); glVertex3f(XMIN,0,ZMAX);
                glEnd(); //RENDER Floor WALL*/

                     /*      glTranslatef(0,0,-50);
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
