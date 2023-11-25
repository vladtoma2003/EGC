#pragma once
#include "components/simple_scene.h"

namespace m1
{
    class Body : public gfxc::SimpleScene
    {
    private:
        glm::vec3 position;
        glm::vec3 size = glm::vec3(4, 1, 8);
    public:
        explicit Body(const float x, const float y, const float z)
        {
            position = glm::vec3(x, y, z);
        }
        glm::vec3 getBodyPosition() const
        {
            return position;
        }
        glm::vec3 getBodySize() const
        {
            return size;
        }
        void moveBody(float x, float y, float z)
        {
            position.x += x;
            position.y += y;
            position.z += z;
        }
        void updateBodyPosition(float x, float y, float z)
        {
            position.x = x;
            position.y = y;
            position.z = z;
        }
    };
}