#ifndef __MATH_H__
#define __MATH_H__

#include <cmath>
#include <algorithm>

class vec2
{
    public:
        union { float x; float u; };
        union { float y; float v; };

    public:
        vec2() 
            : x(0), y(0) 
        {
        }
        vec2(float a, float b)
            : x(a), y(b)
        {
        }
        vec2(float f)
            : x(f), y(f)
        {
        }
        vec2(const vec2 &v)
            : x(v.x), y(v.y)
        {
        }
        vec2(const float * const v)
            : x(v[0]), y(v[1])
        {
        }
        void swap(vec2 &v)
        {
            std::swap(x, v.x); std::swap(y, v.y);
        }

        // ptr

        operator float *()
        {
            return &x;
        }
        operator const float *() const
        {
            return &x;
        }
        float operator[](const size_t i) const
        {
            return *(&x + i);
        }
        float &operator[](const size_t i)
        {
            return *(&x + i);
        }

        // assign

        vec2 &operator=(const vec2 &v)
        {
            x = v.x; y = v.y;
            return *this;
        }
        vec2 &operator=(const float f)
        {
            x = f; y = f;
            return *this;
        }

        // compare

        bool operator==(const vec2 &v) const
        {
            return x == v.x && y == v.y;
        }
        bool operator!=(const vec2 &v) const
        {
            return x != v.x || y != v.y;
        }

        // unary arithmetic

        const vec2 &operator+() const
        {
            return *this;
        }
        vec2 operator-() const
        {
            return vec2(-x, -y);
        }

        // vector arithmetic

#define VEC_OP(op) \
        vec2 operator op (const vec2 &v) const \
        { return vec2(x op v.x, y op v.y); } \
        vec2 &operator op##= (const vec2 &v) \
        { x op##= v.x; y op##= v.y; return *this; }

        VEC_OP(+) VEC_OP(-) VEC_OP(*) VEC_OP(/)

#undef VEC_OP

        // scalar arithmetic

#define SCAL_OP(op) \
        vec2 operator op (const float f) const \
        { return vec2(x op f, y op f); } \
        friend vec2 operator op (const float f, const vec2 &v) \
        { return vec2(f op v.x, f op v.y); } \
        vec2 &operator op##= (const float f) \
        { x op##= f; y op##= f; return *this; }

        SCAL_OP(+) SCAL_OP(-) SCAL_OP(*) SCAL_OP(/)

#undef SCAL_OP

        // geometry

        float len() const
        {
            return sqrt(x*x + y*y);
        }
        float sqLen() const
        {
            return x*x + y*y;
        }
        float dist(const vec2 &v) const
        {
            return (v - *this).len();
        }
        float sqDist(const vec2 &v) const
        {
            return (v - *this).sqLen();
        }

        float normalize() // returns length
        {
            float length = len();
            if (length != 0)
            {
                x /= length; y /= length;
            }
            return length;
        }
        vec2 normalized() // normalized copy
        {
            float length = len();
            if (length != 0)
                return *this / length;
        }

        float dot(const vec2 &v) const
        {
            return x*v.x + y*v.y;
        }
        float cross(const vec2 &v) const
        {
            return x*v.y - y*v.x;
        }

        vec2 lerp(const vec2 &v, float f) const // linear interpolate
        {
            return vec2(x + f*(v.x - x), y + f*(v.y - y));
        }

};

class vec3
{
    public:
        union { float x; float r; float u; };
        union { float y; float g; float v; };
        union { float z; float b; float w; };

    public:
        vec3() 
            : x(0), y(0), z(0)
        {
        }
        vec3(float a, float b, float c)
            : x(a), y(b), z(c)
        {
        }
        vec3(float f)
            : x(f), y(f), z(f)
        {
        }
        vec3(const vec3 &v)
            : x(v.x), y(v.y), z(v.z)
        {
        }
        vec3(const float * const v)
            : x(v[0]), y(v[1]), z(v[2])
        {
        }
        void swap(vec3 &v)
        {
            std::swap(x, v.x); std::swap(y, v.y); std::swap(z, v.z);
        }

        // ptr

        operator float *()
        {
            return &x;
        }
        operator const float *() const
        {
            return &x;
        }
        float operator[](const size_t i) const
        {
            return *(&x + i);
        }
        float &operator[](const size_t i)
        {
            return *(&x + i);
        }

        // assign

        vec3 &operator=(const vec3 &v)
        {
            x = v.x; y = v.y; z = v.z;
            return *this;
        }
        vec3 &operator=(const float f)
        {
            x = f; y = f; z = f;
            return *this;
        }

        // compare

        bool operator==(const vec3 &v) const
        {
            return x == v.x && y == v.y && z == v.z;
        }
        bool operator!=(const vec3 &v) const
        {
            return x != v.x || y != v.y || z != v.z;
        }

        // unary arithmetic

        const vec3 &operator+() const
        {
            return *this;
        }
        vec3 operator-() const
        {
            return vec3(-x, -y, -z);
        }

        // vector arithmetic

#define VEC_OP(op) \
        vec3 operator op (const vec3 &v) const \
        { return vec3(x op v.x, y op v.y, z op v.z); } \
        vec3 &operator op##= (const vec3 &v) \
        { x op##= v.x; y op##= v.y; z op##= v.z; return *this; }

        VEC_OP(+) VEC_OP(-) VEC_OP(*) VEC_OP(/)

#undef VEC_OP

        // scalar arithmetic

#define SCAL_OP(op) \
        vec3 operator op (const float f) const \
        { return vec3(x op f, y op f, z op f); } \
        friend vec3 operator op (const float f, const vec3 &v) \
        { return vec3(f op v.x, f op v.y, f op v.z); } \
        vec3 &operator op##= (const float f) \
        { x op##= f; y op##= f; z op##= f; return *this; }

        SCAL_OP(+) SCAL_OP(-) SCAL_OP(*) SCAL_OP(/)

#undef SCAL_OP

        // geometry

        float len() const
        {
            return sqrt(x*x + y*y + z*z);
        }
        float sqLen() const
        {
            return x*x + y*y + z*z;
        }
        float dist(const vec3 &v) const
        {
            return (v - *this).len();
        }
        float sqDist(const vec3 &v) const
        {
            return (v - *this).sqLen();
        }

        float normalize() // returns length
        {
            float length = len();
            if (length != 0)
            {
                x /= length; y /= length; z /= length;
            }
            return length;
        }
        vec3 normalized() // normalized copy
        {
            float length = len();
            if (length != 0)
                return *this / length;
        }

        float dot(const vec3 &v) const
        {
            return x*v.x + y*v.y + z*v.z;
        }
        vec3 cross(const vec3 &v) const
        {
            return vec3(y * v.z - z * v.y, z * v.x - x * v.z,
                    x * v.y - y * v.x);
        }

        vec3 lerp(const vec3 &v, float f) const // linear interpolate
        {
            return vec3(x + f*(v.x - x), y + f*(v.y - y), z  + f*(v.z - z));
        }
};

#endif
