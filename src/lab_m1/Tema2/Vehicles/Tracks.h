#pragma once
#include "components/simple_scene.h"

namespace m1
{
    class Tracks : public gfxc::SimpleScene
    {
    private:
        glm::vec3 position;
        glm::vec3 size = glm::vec3(1, 1, 8);
        glm::vec3 distanceFromBody;
        glm::vec3 center;
        float angle;
    public:
        explicit Tracks(const float x, const float y, const float z, glm::vec3 distanceFromBody, glm::vec3 bodyPos, float angle)
        {
            position = glm::vec3(x, y, z);
            this->distanceFromBody = distanceFromBody;
            center = bodyPos;
            this->angle = angle;
        }
        void setTracksPosition(float x, float y, float z)
        {
            position = glm::vec3(x, y, z);
        }
        glm::vec3 getTracksPosition() const
        {
            return position;
        }
        glm::vec3 getTracksSize() const
        {
            return size;
        }
        void moveTracks(float x, float y, float z)
        {
            position.x += x;
            position.y += y;
            position.z += z;
            center.x += x;
            center.y += y;
            center.z += z;
        }
        void updateTracksPosition(float x, float y, float z)
        {
            position.x = x;
            position.y = y;
            position.z = z;
            center.x = x;
            center.y = y;
            center.z = z;
        }
        void rotateTracks(float angle)
        {
            this->angle += angle;
            position.x = center.x + distanceFromBody.x * cos(this->angle);
            position.z = center.z + distanceFromBody.z * sin(this->angle);
        }
    };
}