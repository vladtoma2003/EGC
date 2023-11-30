#pragma once

#include <vector>

#include "Building.h"
#include "camera.h"
#include "components/simple_scene.h"
#include "Vehicles/Tank.h"
#include "Meshes/Meshes.h"

#define MODELS_PATH "src/lab_m1/Tema2/Models/"

namespace m1
{
    class Tema2 : public gfxc::SimpleScene
    {
    public:
        Tema2();
        ~Tema2();

        void Init() override;

        // Mesh *CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices);

        private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;
        float time = 0;
        Tank *tank = new Tank();
        std::vector<Tank*> enemyTanks = std::vector<Tank*>();

        void createNTanks(int n);
        void tankCollision(Tank *tank1, Tank *tank2) const;
        static void searchForPlayer(Tank *tank, float deltaTime, glm::vec3 playerPosition);
        void checkCollisionWithProjectiles(Tank *tank, std::vector<Projectile *> projectiles);
        void initBuildings();
        void checkBuildingsCollision(Tank *tank);
        bool checkIfTankIsInsideBuilding(Tank *tank, Building *building);
        void spawnEnemyTank();
        bool atLeastOneTankDead();
        void checkCollisionProjectileBuilding(Projectile *projectile);
    

    protected:
        implemented::CameraTema *camera;
        glm::mat4 projectionMatrix;
        bool renderCameraTarget;
        std::vector<Building*> buildings = std::vector<Building*>();

        // TODO(student): If you need any other class variables, define them here.
        float orthoLeft = 0;
        float orthoRight = 1280;
        float orthoDown = 0;
        float orthoUp = 720;
        float fov = RADIANS(70);
        float aspectRatio;
        float zNear = 0.01f;
        float zFar = 200.0f;
        bool isPerspective = true;
        bool vClipping = false;
    };
    
}   // namespace m1
