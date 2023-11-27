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
        float trackAngle;
    public:
        explicit Tracks(const float x, const float y, const float z, glm::vec3 distanceFromBody, glm::vec3 bodyPos, float angle)
        {
            position = glm::vec3(x, y, z);
            this->distanceFromBody = distanceFromBody;
            center = bodyPos;
            trackAngle = angle;
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
        float getTrackAngle() const
        {
            return trackAngle;
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
            center.x = position.x + distanceFromBody.x;
            center.y = position.y + distanceFromBody.y;
            center.z = position.z + distanceFromBody.z;
        }

        void rotateTrack(Tank *tank, float angle)
        {
            trackAngle += angle;
        }
        
        void rotateTracks(float angle)
        {
            trackAngle += angle;
            position.x = center.x + distanceFromBody.z * sin(trackAngle);
            position.z = center.z + distanceFromBody.z * cos(trackAngle);
        }
    };
}