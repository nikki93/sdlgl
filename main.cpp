#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cstdio>
#include <cstdlib>

#include "Object.h"
#include "Box.h"

// --- loop -----------------------------------------------------------------

// return false if exit
static bool handleEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) // for each event
    {
        switch(event.type) 
        {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                        return false;
                }
                break;

            case SDL_QUIT:
                return false;
        }
    }

    return true;
}

static void update()
{
    // frame timing
    static int lastFrame = 0;
    int currFrame = SDL_GetTicks();
    float elapsed = (currFrame - lastFrame) * 0.001;
    lastFrame = currFrame;

    // wanna see how fast this is
    //printf("%f\n", elapsed);

    // update objects
    Object::updateAll(elapsed);
}

static void draw()
{
    // clear first
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw objects
    Object::drawAll();

    // let's see!
    SDL_GL_SwapBuffers();
}

static void loop()
{
    while (handleEvents())
    {
        update();
        draw();
    }
}

// --- init -----------------------------------------------------------------

// return true if succeeded
static bool initSDL(int w, int h)
{
    // init video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) 
    {
        fprintf(stderr, "Video initialization failed: %s\n", SDL_GetError());
        return false;
    }

    // get bpp
    const SDL_VideoInfo *info = SDL_GetVideoInfo();
    if (!info) 
    {
        fprintf(stderr, "Video query failed: %s\n", SDL_GetError());
        return false;
    }
    int bpp = info->vfmt->BitsPerPixel;

    // set some GL attributes
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    // set video mode
    int flags = SDL_OPENGL;
    if(!SDL_SetVideoMode(w, h, bpp, flags))
    {
        fprintf(stderr, "Video mode set failed: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

static void initGL(int w, int h)
{
    glShadeModel(GL_SMOOTH);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);
    glEnable(GL_CULL_FACE);
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);

    glClearColor(0, 0, 0, 0); // black background

    // put (0, 0) topleft, y downward [gluOrtho2D(0, w, h, 0) didn't work]
    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
}

// --- scene ----------------------------------------------------------------

#define UNIT_RAND() (((float) rand()) / RAND_MAX)

// make the scene
static void start()
{
    int n = 200;
    const float v = 800;
    const float hV = 0.5 * v;
    while (n--)
    {
        Object::add(new Box(1024*UNIT_RAND(), 768*UNIT_RAND(), // pos
                    v*UNIT_RAND() - hV, v*UNIT_RAND() - hV, // vel
                    4*UNIT_RAND() + 2, // size
                    UNIT_RAND(), UNIT_RAND(), UNIT_RAND() // color
                    ));
    }
}

// --- stop -----------------------------------------------------------------

static void stop()
{
    SDL_Quit();
}

// --- main -----------------------------------------------------------------

int main( int argc, char* argv[] )
{
    const int w = 1024, h = 768;

    // init stuff
    if (!initSDL(w, h))
        return 1;
    initGL(w, h);

    // make the scene
    start();

    // loop
    loop();

    // end
    stop();

    return 0;
}

