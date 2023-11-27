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
        glm::vec3 distanceFromBody;
        glm::vec3 center;
    public:
        explicit Cannon(const float x, const float y, const float z, glm::vec3 distanceFromBody, glm::vec3 bodyPos)
        {
            position = glm::vec3(x, y, z);
            this->distanceFromBody = distanceFromBody;
            center = bodyPos;
        }
        void setCannonPosition(float x, float y, float z)
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
            center.x += x;
            center.y += y;
            center.z += z;
        }
        void updateCannonPosition(float x, float y, float z)
        {
            position.x = x;
            position.y = y;
            position.z = z;
            center.x = position.x + distanceFromBody.x;
            center.y = position.y + distanceFromBody.y;
            center.z = position.z + distanceFromBody.z;
        }
        void rotateCannon(float angle)
        {
            position.x = position.x + distanceFromBody.x * cos(-angle);
            position.z = position.z + distanceFromBody.z * sin(-angle);
        }
    };
}