#ifndef __BOX_H__
#define __BOX_H__

#include "Math.h"
#include "Object.h"

#include <cmath>

#define UNIT_RAND() (((float) rand()) / RAND_MAX)

class Box : public Object
{
    protected:
        vec2 _pos, _vel;
        float _halfsize;
        vec3 _col;

    public:
        // mess :/
        Box(vec2 pos, vec2 vel, float size, vec3 col)
            : _pos(pos), _vel(vel),
              _halfsize(0.5 * size),
              _col(col)
        {
        }

        virtual void update(float elapsed) 
        {
            // bounce
            if (_pos.x < 0)
            {
                _pos.x = 0;
                _vel.x = fabs(_vel.x);
            }
            else if (_pos.x > 1024)
            {
                _pos.x = 1024;
                _vel.x = -fabs(_vel.x);
            }
            if (_pos.y < 0)
            {
                _pos.y = 0;
                _vel.y = (UNIT_RAND() * 0.2 + 0.9) * fabs(_vel.y);
            }

            // move
            _vel.y -= 1000 * elapsed;
            _pos += _vel * elapsed;
        }

        virtual void draw()
        {
            vec3 col(
                    1.5 * _col.r * fabs(_pos.y - 384.0)/384.0,
                    1.5 * _col.g * fabs(_pos.y - 768.0)/768.0,
                    1.5 * _col.b * fabs(_pos.y)/768.0
                    );
            glColor3fv(col);
            glRectfv(_pos - _halfsize, _pos + _halfsize);
        }
};

#endif
