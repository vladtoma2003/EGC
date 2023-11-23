#pragma once
#include "components/simple_scene.h"
#include "lab_m1/Tema2/Vehicles/Body.h"
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
        float x = 0;
        float y = 0;
        float z = 0;
        float scale = 0.5f;
        float sizeX = 8*scale;
        float sizeY = 1*scale;
        float sizeZ = 4*scale;
        // Mesh *body;
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

        void createTank(float x, float y, float z);

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
    };

   
}