#pragma once
#include <iostream>

#include "components/simple_scene.h"

namespace m1
{
    class Body : public gfxc::SimpleScene
    {
    private:
        glm::vec3 position;
        glm::vec3 size = glm::vec3(8, 1, 4);
        float bodyAngle = 0;
        glm::vec2 deformationDirection;
    public:
        explicit Body(const float x, const float y, const float z)
        {
            position = glm::vec3(x, y, z);
            deformationDirection = glm::vec2(rand() % 2 == 0 ? -1 : 1, rand() % 2 == 0 ? -1 : 1);
        }
        glm::vec3 getBodyPosition() const
        {
            return position;
        }
        glm::vec3 getBodySize() const
        {
            return size;
        }
        void moveBody(glm::vec3 distance)
        {
            position += distance;
        }
        void updateBodyPosition(float x, float y, float z)
        {
            position.x = x;
            position.y = y;
            position.z = z;
            bodyAngle = 0;
        }
        void rotateBody(float angle)
        {
            bodyAngle += angle;
        }
        glm::vec2 getDeformationDirection() const
        {
            return deformationDirection;
        }
    };
}