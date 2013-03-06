#include "CApp.h"

bool CApp::OnInit() {
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        return false;
    }
 
    if((Surf_Display = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF)) == NULL) {
        return false;
    }
 
    if((Surf_Test = CSurface::OnLoad("ball.bmp")) == NULL) {
        return false;
    } //load custom image
 
    return true;
}

/*http://www.sdltutorials.com/sdl-tutorial-basics
 * The first thing we need to do is start up SDL itself, so we can access its functions. We are telling SDL to Initialize everything it has; there are other parameters you can pass, but understanding them at this point is not important. The next function we use is SDL_SetVideoMode. This bad boy is what creates our window, and our surface. It takes 4 parameters: The width of the window, the height of the window, the bit resolution of the window (recommended to be 16 or 32), and then display flags. There are quite a few display flags, but the ones shown above are fine for now. The first flag tells SDL to use hardware memory for storing our images and such, and the second flag tells SDL to use double buffering (which is important if you don't want flickering on your screen). Another flag that may interest you now is SDL_FULLSCREEN, which makes the window go fullscreen. */
