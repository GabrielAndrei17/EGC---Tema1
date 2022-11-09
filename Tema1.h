#pragma once

#include "components/simple_scene.h"

using namespace std;

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

        void DrawScene(glm::mat3 visMatrix);
        void printLifes();
        void printBullets();

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;


    protected:
        float cx, cy;
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float angularStep;
        float squareDistance = 100.f;
        float resolutionx, resolutiony;

        float tx1, ty1, tx3, ty3, angular, angularWing;

        int bullets, score, hit, hitted, escaped, lifes;
        float dX, dY;
        int dead;
        float time;
    };
}   // namespace m1