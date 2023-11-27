#pragma once
#include "components/simple_scene.h"
#include "lab_m1/Tema2/Vehicles/Body.h"

namespace implemented
{
    class CameraTema;
}

namespace m1
{
    class Cannon;
    class Turret;
    class Tracks;

    class Tank : public gfxc::SimpleScene{
    
    private:
        const int speed = 10;
        int hp = 100;
        int damage = 10;
        glm::vec3 tankPosition = glm::vec3(0.f, 0.f, 0.f);
        float scale = 0.25f;
        glm::vec3 size = glm::vec3(8*scale, 1*scale, 4*scale);
        float tankAngle = 0;
        glm::vec3 forwardTank     = glm::vec3(1, 0, 0);
        glm::vec3 rightTank       = glm::vec3(0, 0, 1);
        Body *body;
        Tracks **tracks;
        Turret *turret;
        Cannon *cannon;
        std::unordered_map<std::string, Mesh *> components;

        Body* createBody(float x, float y, float z);
        Tracks** createTracks(float x, float y, float z);
        Turret *createTurret(float x, float y, float z);
        Cannon *createCannon(float x, float y, float z);

    public:

        void renderTank(implemented::CameraTema *camera, glm::mat4 projectionMatrix, std::unordered_map<std::string, Shader *> shaders,float time);
        void createTank(float x, float y, float z);
        void moveTank(float distance) const;
        void updatePosition(float x, float y, float z);
        void rotateTank(float angle);

        // void Init();
        Tank();
        ~Tank();

        int getSpeed() const
        {
            return speed;
        }

        int getHP() const
        {
            return hp;
        }

        int getDamage() const
        {
            return damage;
        }

        glm::vec3 getPosition() const
        {
            return tankPosition;
        }

        glm::vec3 getTankForward() const
        {
            return forwardTank;
        }

        glm::vec3 getTankRight() const
        {
            return rightTank;
        }
        
        float getScale() const
        {
            return scale;
        }

        std::unordered_map<std::string, Mesh*> getComponents() const
        {
            return components;
        }

        Mesh* getComponent(std::string name)
        {
            return components[name];
        };

        Body *getBody() const
        {
            return body;
        }
        Tracks **getTracks() const
        {
            return tracks;
        }
        Turret *getTurret() const
        {
            return turret;
        }
        Cannon *getCannon() const
        {
            return cannon;
        }
        void setPosition(glm::vec3 position)
        {
            this->tankPosition = position;
        }
        float getAngle () const
        {
            return tankAngle;
        }
        void setAngle(float angle)
        {
            tankAngle = angle;
        }
    };

   
}
