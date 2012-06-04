#ifndef __BOX_H__
#define __BOX_H__

#include "Object.h"

#include <cmath>

#define UNIT_RAND() (((float) rand()) / RAND_MAX)

class Box : public Object
{
    protected:
        float _x, _y; // center of box
        float _vx, _vy;
        float _halfsize;
        float _colR, _colG, _colB;

    public:
        // mess :/
        Box(float x, float y, 
                float vx, float vy,
                float size,
                float colR, float colG, float colB)
            : _x(x), _y(y),
              _vx(vx), _vy(vy),
              _halfsize(0.5 * size),
              _colR(colR), _colG(colG), _colB(colB)
        {
        }

        virtual void update(float elapsed) 
        {
            // bounce
            if (_x < 0)
            {
                _x = 0;
                _vx = fabs(_vx);
            }
            else if (_x > 1024)
            {
                _x = 1024;
                _vx = -fabs(_vx);
            }
            if (_y < 0)
            {
                _y = 0;
                _vy = (UNIT_RAND() * 0.2 + 0.9) * fabs(_vy);
            }
            /*
            else if (_y > 768)
            {
                _y = 768;
                _vy = -(UNIT_RAND() * 0.2 + 0.9) * fabs(_vy);
            }
            */

            // move
            _vy -= 1000 * elapsed; // gravity

            _x += _vx * elapsed;
            _y += _vy * elapsed;

        }

        virtual void draw()
        {
            float colR = _colR * fabs(_y - 384.0)/384.0 + 0.2;
            float colG = _colG * fabs(_y - 768.0)/768.0 + 0.2;
            float colB = _colB * fabs(_y)/768.0 + 0.2;

            glColor3f(colR, colG, colB);

            glRectf(_x - _halfsize, _y - _halfsize, 
                    _x + _halfsize, _y + _halfsize);
        }
};

#endif
