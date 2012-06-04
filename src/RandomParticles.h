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
        int n = 20000;

        const float v_x = 400;
        const float hV_x = 0.5 * v_x;
        const float v_y = 120;
        const float hV_y = 0.5 * v_y;

        while (n--)
        {
            Object::add(new Box(1024*UNIT_RAND(), 768*UNIT_RAND(), // pos
                        v_x*UNIT_RAND() - hV_x, v_y*UNIT_RAND() - hV_y, // vel
                        1*UNIT_RAND() + 0.5, // size
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
