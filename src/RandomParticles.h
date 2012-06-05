#ifndef __RANDOMPARTICLES_H__
#define __RANDOMPARTICLES_H__

#include "Math.h"
#include "Scene.h"
#include "Box.h"

#define UNIT_RAND() (((float) rand()) / RAND_MAX)

class RandomParticles : public Scene
{
    void start()
    {
        // make many particles :)
        int n = 50000;

        const float v_x = 400;
        const float hV_x = 0.5 * v_x;
        const float v_y = 120;
        const float hV_y = 0.5 * v_y;

        while (n--)
        {
            vec2 pos(1024*UNIT_RAND(), 768*UNIT_RAND());
            vec2 vel(v_x*UNIT_RAND() - hV_x, v_y*UNIT_RAND() - hV_y);
            float size = 1*UNIT_RAND() + 0.5;
            vec3 col(UNIT_RAND(), UNIT_RAND(), UNIT_RAND());

            Object::add(new Box(pos, vel, size, col));
        }
    }

    void stop()
    {
        // no more particles :(
        Object::removeAll();
    }
};

#endif
