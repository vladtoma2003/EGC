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
        explicit Body(float x, float y, float z)
        {
            this.x = x;
            this.y = y;
            this.z = z;
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
    
    class Tank : public gfxc::SimpleScene{
    
    private:
        const int speed = 10;
        int hp = 100;
        int damage = 10;
        float x = 0;
        float y = 0;
        float z = 0;
        // Mesh *body;
        Body *body;
        std::unordered_map<std::string, Mesh *> components;

        Body* createBody(float x, float y, float z);

    public:

        void createTank(Body *body);

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

        float getX() const
        {
            return x;
        }

        float getY() const
        {
            return y;
        }

        float getZ() const
        {
            return z;
        }

        std::unordered_map<std::string, Mesh*> getComponents() const
        {
            return components;
        }

        Mesh* getComponent(std::string name)
        {
            return components[name];
        };
    };

   
}