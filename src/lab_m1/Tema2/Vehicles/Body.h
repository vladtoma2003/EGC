#pragma once
#include "components/simple_scene.h"

namespace m1
{
    class Body : public gfxc::SimpleScene
    {
    private:
        float x;
        float y;
        float z;
        Mesh *body = new Mesh("body");
    public:
        explicit Body(const float x, const float y, const float z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }
        float getBodyX() const
        {
            return x;
        }
        float getBodyY() const
        {
            return y;
        }
        float getBodyZ() const
        {
            return z;
        }
    };
}