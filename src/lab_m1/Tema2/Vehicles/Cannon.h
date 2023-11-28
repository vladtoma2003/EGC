#pragma once
#include "components/simple_scene.h"

namespace m1
{
    class Cannon : public gfxc::SimpleScene
    {
    private:
        glm::vec3 position;
        glm::vec3 size = glm::vec3(6, 0.4, 0.4);
        float AngleOY = 0;
        glm::vec3 distanceFromBody;
        glm::vec3 center;
        float cannonAngle = 0;
        float deltaX = 0;
        glm::vec3 forward;
    public:
        explicit Cannon(const float x, const float y, const float z, glm::vec3 distanceFromBody, glm::vec3 bodyPos, glm::vec3 forward)
        {
            position = glm::vec3(x, y, z);
            this->distanceFromBody = distanceFromBody;
            center = bodyPos;
            this->forward = forward;
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
        float getCannonAngle() const
        {
            return cannonAngle;
        }
        void moveCannon(glm::vec3 distance)
        {
            position += distance;
            center += distance;
        }
        void updateCannonPosition(float x, float y, float z)
        {
            position.x = x;
            position.y = y;
            position.z = z;
            center.x = position.x + distanceFromBody.x;
            center.y = position.y + distanceFromBody.y;
            center.z = position.z + distanceFromBody.z;
            cannonAngle = 0;
        }
        void rotateCannon(float angle)
        {
            cannonAngle += angle;
            forward = normalize(rotate(glm::mat4(1.f), angle, glm::vec3(0, 1, 0)) * glm::vec4(forward, 0));
        }
        float getDeltaX() const
        {
            return deltaX;
        }
        void setDeltaX(float value)
        {
            deltaX = value;
        }
        void incDeltaX(float value)
        {
            deltaX += value;
        }
        glm::vec3 getForward() const
        {
            return forward;
        }
    };
}