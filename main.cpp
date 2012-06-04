#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <cstdio>
#include <cstdlib>

#include "Object.h"
#include "Scene.h"

#include "RandomParticles.h"

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

    glLoadIdentity();
    gluOrtho2D(0, w, 0, h);
}

// --- start ----------------------------------------------------------------

static void startScenes()
{
    // add scenes
    Scene::add(new RandomParticles());
    Scene::add(new RandomParticles());

    // let's go!
    Scene::begin();
}

// --- loop -----------------------------------------------------------------

static void handleEvents()
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
                        Scene::shutdown();

                    case SDLK_n:
                        Scene::next();
                    case SDLK_p:
                        Scene::previous();
                }
                break;

            case SDL_QUIT:
                Scene::shutdown();
        }
    }
}

// return false if shutdown
static bool update()
{
    // frame timing
    static int lastFrame = 0;
    int currFrame = SDL_GetTicks();
    float elapsed = (currFrame - lastFrame) * 0.001;
    lastFrame = currFrame;
    //printf("%f\n", elapsed);

    // update everything
    if (!Scene::updateCurrent(elapsed))
        return false;
    Object::updateAll(elapsed);

    // handle requests (destroy, next level etc.)
    Object::handleRequests();
    Scene::handleRequests();

    return true;
}

static void draw()
{
    // clear
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // draw everything
    Scene::drawCurrent();
    Object::drawAll();

    // see
    SDL_GL_SwapBuffers();
}

static void loop()
{
    while (true)
    {
        handleEvents();
        if (!update())
            break;
        draw();
    }
}

// --- stop -----------------------------------------------------------------

static void stop()
{
    Scene::stopCurrent();
    Scene::cleanup();

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

    // make the initial scene
    startScenes();

    // loop
    loop();

    // end
    stop();

    return 0;
}

