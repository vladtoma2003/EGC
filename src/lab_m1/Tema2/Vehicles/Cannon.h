#pragma once
#include "components/simple_scene.h"

namespace m1
{
    class Cannon : public gfxc::SimpleScene
    {
    private:
        glm::vec3 position;
        glm::vec3 size = glm::vec3(0.4, 0.4, 6);
        float AngleOY = 0;
    public:
        explicit Cannon(const float x, const float y, const float z)
        {
            position = glm::vec3(x, y, z);
        }
        glm::vec3 getCannonPosition() const
        {
            return position;
        }
        glm::vec3 getCannonSize() const
        {
            return size;
        }
        float getCannonAngleOY() const
        {
            return AngleOY;
        }
        void moveCannon(float x, float y, float z)
        {
            position.x += x;
            position.y += y;
            position.z += z;
        }
        void updateCannonPosition(float x, float y, float z)
        {
            position.x = x;
            position.y = y;
            position.z = z;
        }
    };
}