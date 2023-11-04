#pragma once

#include "components/simple_scene.h"


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

        void RenderScene();
        void CreateMeshes();
        void buyRhombus(int score);
        
     protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        // constant sizes or positions
        const float life = 25;
        const float space = 25;
        const float squareSide = 125;
        const float outlinePosx = life + space;
        const float outlinePosy = 4*squareSide + 2*space;
        const float outlineSide = 140;
        const float lifeX = outlinePosx + 4*outlineSide + 5*space;
        const float lifeY = outlinePosy + 0.25*squareSide/2;
        const float rhombusSide = 50;
        const float starSize = 50;
        const std::tuple <float, float> starPos = std::make_tuple(lifeX, lifeY - starSize/2);

        int allies[3][3] = {0};
        float noLives = 3;
        int score = 50;
        bool holdingMouse = false;
        int mouseX, mouseY;
        int buyX, buyY;
        
    };
}   // namespace m1
