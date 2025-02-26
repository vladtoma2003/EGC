#pragma once

#include "components/simple_scene.h"


class Rhombus;

namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
     public:
        Tema1();
        ~Tema1();

        void Init() override;

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

        void RenderScene(float deltaTime);
        void buyRhombus(int x, int y, int buyX, int buyY);
        void RenderHoldingRhombus(int x, int y, int buyX, int buyY);
        void PlaceRhombus(int x, int y);
        void DestroyRhombus(int x, int y);
        void SpawnStars(float time);
        void CollectStars();
        void ShootStars(float deltaTime);
        void DestroyProjectiles();
        void SpawnEnemies(float deltaTime);
        void DestroyEnemies();
        bool checkEnemysRow(int row, int color, std::vector<std::tuple<float, float, int, int, float, bool, float>> enemies);
        void DetectCollision();
        void CheckGameOver();
        void moveStars(float deltaTime);

        
     protected:
        glm::mat3 modelMatrix;

        // constant sizes or positions
        const float life = 25;
        const float space = 25;
        const float squareSide = 125;
        const float outlinePosx = life + space;
        const float outlinePosy = 4*squareSide + 2*space;
        const float outlineSide = 140;
        const int initialResolutiony = 720;
        const float lifeX = outlinePosx + 4*outlineSide + 5*space;
        const float lifeY = outlinePosy + 0.25*squareSide/2;
        const float rhombusSide = 50;
        const float starSize = 50;
        const std::tuple <float, float> starPos = std::make_tuple(lifeX, lifeY - starSize/2);

        int allies[3][3] = {0};
        float noLives = 3;
        int score = 5;
        bool holdingMouse = false;
        int mouseX, mouseY;
        int buyX, buyY;
        bool holdingRhombus = false;
        int currentColor = 0; // 0 - Empty, 1 - Pink, 2 - Turquoise, 3 - Yellow, 4 - Purple
        int price = 0;
        float timeElapsed = 0;
        float randomEnemyTime = 0;
        int randomMod = 1;

        std::vector<std::tuple<float, float, int, int, float ,bool, float>> enemies; // x, y, color, hitpoints, size, destroy, rotation angle
        std::vector<std::tuple<float, float, int, float, bool>> projectiles; // x, y, color, angularStep, canHit
        std::vector<std::tuple<float, float, float, float, float>> stars; // final x, final y, initial x, initial y, rotation angle
        std::vector<std::tuple<int, float, bool, float>> board = { // color, size, destroy, time since last shoot
            std::make_tuple(0, 0, false, 0), std::make_tuple(0, 0, false, 0), std::make_tuple(0, 0, false, 0),
            std::make_tuple(0, 0, false, 0), std::make_tuple(0, 0, false, 0), std::make_tuple(0, 0, false, 0),
            std::make_tuple(0, 0, false, 0), std::make_tuple(0, 0, false, 0), std::make_tuple(0, 0, false, 0)
        };
        
    };
}   // namespace m1
