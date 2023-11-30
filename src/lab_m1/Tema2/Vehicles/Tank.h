#pragma once
#include "Projectile.h"
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
        float speed = 5.0f;
        int hp = 100;
        int damage = 10;
        glm::vec3 tankPosition = glm::vec3(0, 0, 0);
        float scale = 0.25f;
        float tankAngle = 0;
        glm::vec3 forwardTank = glm::vec3(1, 0, 0);
        glm::vec3 rightTank = glm::vec3(0, 0, 1);
        const float cooldown = 1.5f;
        float shootTime = 0;
        glm::vec3 color = glm::vec3(15.f/255, 39.f/255, 10.f/255);
        bool canShoot = true;
        float moveTime = 0;
        float moveTotal = 0;
        int decision = 0;
        
        Body *body;
        Tracks **tracks;
        Turret *turret;
        Cannon *cannon;
        std::unordered_map<std::string, Mesh *> components;
        std::vector<Projectile *> projectiles = std::vector<Projectile *>();

        Body* createBody(float x, float y, float z);
        Tracks** createTracks(float x, float y, float z);
        Turret *createTurret(float x, float y, float z);
        Cannon *createCannon(float x, float y, float z);

    public:
        
        Projectile *createProjectile(float x, float y, float z, glm::vec3 forward, float angle);
        void renderTank(implemented::CameraTema *camera, glm::mat4 projectionMatrix, std::unordered_map<std::string, Shader *> shaders,float time);
        void createTank(float x, float y, float z, glm::vec3 color);
        void moveTank(float distance);
        void moveTank(glm::vec3 distance);
        void updatePosition(float x, float y, float z);
        void rotateTank(float angle);
        void shoot();
        void removeProjectiles();
        void rotateTurretTowardsPlayer(glm::vec3 playerPosition);
        void checkCollisionWithTank(Tank *tank);
        void reload(float deltaTime);

        // void Init();
        Tank(float x, float y, float z, glm::vec3 color);
        ~Tank();
        Tank();

        float getSpeed() const
        {
            return speed;
        }

        int getHP() const
        {
            return hp;
        }

        void setHP(int hp)
        {
            this->hp -= hp;
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
        std::vector<Projectile*> getProjectiles() const
        {
            return projectiles;
        }
        void setSpeed(float speed)
        {
            this->speed = speed;
        }
        float getCooldown() const
        {
            return cooldown;
        }
        float getTime() const
        {
            return shootTime;
        }
        void setTime(float time)
        {
            this->shootTime += time;
        }
        void setMoveTime(float time)
        {
            this->moveTime += time;
        }
        void resetMoveTime()
        {
            this->moveTime = 0;
        }
        float getMoveTime() const
        {
            return moveTime;
        }
        void setMoveTotal(float time)
        {
            this->moveTotal = time;
        }
        float getMoveTotal() const
        {
            return moveTotal;
        }
        void setDecision(int decision)
        {
            this->decision = decision;
        }
        int getDecision() const
        {
            return decision;
        }
    };

   
}
