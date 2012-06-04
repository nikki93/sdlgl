#ifndef __RANDOMPARTICLES_H__
#define __RANDOMPARTICLES_H__

#include "Scene.h"
#include "Box.h"

#define UNIT_RAND() (((float) rand()) / RAND_MAX)

class RandomParticles : public Scene
{
    void start()
    {
        // make many particles :)
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

    void stop()
    {
        // no more particles :(
        Object::removeAll();
    }
};

#endif
