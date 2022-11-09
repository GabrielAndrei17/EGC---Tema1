#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2D.h"




using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::Tema1()
{
}


Tema1::~Tema1()
{
}

int ColisionRectangleCircle(float xP1, float yP1, float xP2, float yP2, float R, float xC, float yC) {
    float x = max(xP1, min(xP2, xC));
    float y = max(yP1, min(yP2, yC));

    double distance = sqrt((x - xC) * (x - xC) + (y - yC) * (y - yC));

    if (R >= distance) {
        return 1;
    }

    return 0;

}

void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);
    bullets = 3;
    lifes = 3;
    score = 0;
    hit = 0;
    hitted = 0;
    escaped = 0;
    dead = 1;
    time = 0;
    
    //Center of the bird
    cx = corner.x + 40.0 / 2;
    cy = corner.y + 75.0 / 2;

    // Initialize tx and ty (the translation steps)
    tx1 = -100;
    ty1 = -500;

    // Initialize angularStep
    angular = 0;
    angularWing = 0;

    resolutionx = 1280 ;
    resolutiony = 720 ;

    Mesh* grass = object2D::CreateRectangle("grass", corner, 100, resolutionx, glm::vec3(0, 1, 0), true);
    AddMeshToList(grass);

    corner = glm::vec3(0, 0, 0);
    Mesh* head = object2D::CreateCircle("Head", corner, glm::vec3(0.18, 0.4, 0.18), true);
    AddMeshToList(head);

    Mesh* Cioc = object2D::CreateTriangle("cioc", corner, 45, glm::vec3(1, 1, 0), true);
    AddMeshToList(Cioc);

    Mesh* eye = object2D::CreateCircle("eye", corner, glm::vec3(0, 0, 0), true);
    AddMeshToList(eye);

    Mesh* Body = object2D::CreateRectangle("Body", corner, 75, 40, glm::vec3(0.66, 0.164, 0.16), true);
    AddMeshToList(Body);

    Mesh* Wing = object2D::CreateRectangle("Wing", corner, 45, 20, glm::vec3(0.64, 0.164, 0.16), true);
    AddMeshToList(Wing);

    Mesh* Bull = object2D::CreateRectangle("Bull", corner, 45, 20, glm::vec3(0, 1, 0), true);
    AddMeshToList(Bull);

    Mesh* life = object2D::CreateCircle("Life", corner, glm::vec3(1, 0, 0), true);
    AddMeshToList(life);

    Mesh* scoreBord = object2D::CreateRectangle("scoreBord", corner, 40, 300, glm::vec3(0, 0.1, 1), false);
    AddMeshToList(scoreBord);

    Mesh* score = object2D::CreateRectangle("score", corner, 40, 30, glm::vec3(0, 0.1, 1), true);
    AddMeshToList(score);
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0.8, 1, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}
void Tema1::printBullets() {

    if (bullets >= 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1100, 650);
        RenderMesh2D(meshes["Bull"], shaders["VertexColor"], modelMatrix);

    }
    if (bullets >= 2) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1150, 650);
        RenderMesh2D(meshes["Bull"], shaders["VertexColor"], modelMatrix);

    }
    if (bullets == 3) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1200, 650);
        RenderMesh2D(meshes["Bull"], shaders["VertexColor"], modelMatrix);

    }
}

void Tema1::printLifes() {
    if (lifes == 0) {
        cout << "GAME OVER\nscore = " << score;
        exit(1);
    }
    if (lifes >= 1) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1110, 630);
        modelMatrix *= transform2D::Scale(10, 10);
        RenderMesh2D(meshes["Life"], shaders["VertexColor"], modelMatrix);

    }
    if (lifes >= 2) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1160, 630);
        modelMatrix *= transform2D::Scale(10, 10);
        RenderMesh2D(meshes["Life"], shaders["VertexColor"], modelMatrix);

    }
    if (lifes == 3) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= transform2D::Translate(1210, 630);
        modelMatrix *= transform2D::Scale(10, 10);
        RenderMesh2D(meshes["Life"], shaders["VertexColor"], modelMatrix);

    }
}


void Tema1::Update(float deltaTimeSeconds)
{
    // TODO(student): Update steps for translation, rotation and scale,
    // in order to create animations. Use the class variables in the
    // class header, and if you need more of them to complete the task,
    // add them over there!
    time += deltaTimeSeconds;
    printLifes();
    printBullets();
    

    if (hit == 1) {

        if (ColisionRectangleCircle(tx1, ty1, tx3, ty3, 20.0, dX, dY)) {
            score++;
            hitted = 1;
            angular = 2 * M_PI_2;
            bullets = 3;
        }
        else {
            bullets--;
        }
        time = 0;
        hit = 0;
    }

    if (time > 5 && (hitted == 1 || escaped == 1)) {
        dead = 1;
        hitted = escaped = 0;
    }

    if (dead == 0) {

        //move bird
        float multiplier = 1.0 + 2*(score / 50);

        float distanceCos = 300 * multiplier * deltaTimeSeconds * cos(angular - M_PI_2);
        float distanceSin = 300 * multiplier * deltaTimeSeconds * sin(angular - M_PI_2);

        if ((tx3 - distanceCos >= 0 && tx3 - distanceCos < resolutionx && ty3 - distanceSin >= 100 && ty3 - distanceSin < resolutiony) || (hitted == 1 || escaped == 1))
        {
            tx1 -= distanceCos;
            ty1 -= distanceSin;
            tx3 -= distanceCos;
            ty3 -= distanceSin;

        }
        else {

            if (tx3 - distanceCos < 0)
                angular += 2 * (4 * M_PI_2 - angular);

            if (tx3 - distanceCos > resolutionx)
                angular += 2 * (2 * M_PI_2 - angular);

            if (ty3 - distanceSin < 100)
                angular += 2 * (3 * M_PI_2 - angular);

            if (ty3 - distanceSin > resolutiony)
                angular += 2 * (M_PI_2 - angular);
        }
    }
    else {
        //spawn bird
        if (time > 5) {

            ty1 = 100.0;
            tx1 = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (resolutionx - 200.0)));
            tx3 = tx1 + 40.0;
            ty3 = ty1 + 80.0;

            angular = -M_PI_2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / M_PI_2));

            dead = 0;
            time = 0;
        }

    }

    if (time > 10 || bullets == 0) {
        escaped = 1;
        angular = 0;
        time = 0;
        lifes--;
        bullets = 3;
    }

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(0, 0);
    RenderMesh2D(meshes["grass"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(50, 650);
    RenderMesh2D(meshes["scoreBord"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(53, 650);
    modelMatrix *= transform2D::Scale(score % 11, 1);
    RenderMesh2D(meshes["score"], shaders["VertexColor"], modelMatrix);

    //Duck Draw

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tx1, ty1);
    modelMatrix *= transform2D::Translate(cx, cy);
    modelMatrix *= transform2D::Rotate(angular);
    modelMatrix *= transform2D::Translate(-cx, -cy);
    RenderMesh2D(meshes["Body"], shaders["VertexColor"], modelMatrix);

    modelMatrix = transform2D::Translate(tx1 + 20, ty1 + 95);
    float diffx = cx - 20, diffy = cy - 95;
    modelMatrix *= transform2D::Translate(diffx, diffy);
    modelMatrix *= transform2D::Rotate(angular);
    modelMatrix *= transform2D::Translate(-diffx, -diffy);
    modelMatrix *= transform2D::Scale(8.8, 8.8);
    RenderMesh2D(meshes["eye"], shaders["VertexColor"], modelMatrix);

    modelMatrix = transform2D::Translate(tx1 + 20, ty1 + 95);
    diffx = cx - 20;  diffy = cy - 95;
    modelMatrix *= transform2D::Translate(diffx, diffy);
    modelMatrix *= transform2D::Rotate(angular);
    modelMatrix *= transform2D::Translate(-diffx, -diffy);
    modelMatrix *= transform2D::Scale(20, 20);
    RenderMesh2D(meshes["Head"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tx1 + 10, ty1 + 110);
    diffx = cx - 10;diffy = cy - 110;
    modelMatrix *= transform2D::Translate(diffx, diffy);
    modelMatrix *= transform2D::Rotate(angular);
    modelMatrix *= transform2D::Translate(-diffx, -diffy);
    modelMatrix *= transform2D::Scale(0.3, 1);
    modelMatrix *= transform2D::Rotate(-0.3);
    RenderMesh2D(meshes["cioc"], shaders["VertexColor"], modelMatrix);

    if (angularWing < 1 && hitted == 0)
        angularWing += deltaTimeSeconds * 3;
    else
        angularWing = 0;

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tx1 - 20, ty1 + 10);
    diffx = cx + 20; diffy = cy - 10;
    modelMatrix *= transform2D::Translate(diffx, diffy);
    modelMatrix *= transform2D::Rotate(angular);
    modelMatrix *= transform2D::Translate(-diffx, -diffy);
    modelMatrix *= transform2D::Translate(20, 45);
    modelMatrix *= transform2D::Rotate(-angularWing);
    modelMatrix *= transform2D::Translate(-20, -45);
    RenderMesh2D(meshes["Wing"], shaders["VertexColor"], modelMatrix);

    modelMatrix = glm::mat3(1);
    modelMatrix *= transform2D::Translate(tx1 + 40, ty1 + 10);
    diffx = cx - 40; diffy = cy - 10;
    modelMatrix *= transform2D::Translate(diffx, diffy);
    modelMatrix *= transform2D::Rotate(angular);
    modelMatrix *= transform2D::Translate(-diffx, -diffy);
    modelMatrix *= transform2D::Translate(0, 45);
    modelMatrix *= transform2D::Rotate(+angularWing);
    modelMatrix *= transform2D::Translate(0, -45);
    RenderMesh2D(meshes["Wing"], shaders["VertexColor"], modelMatrix);


}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (hit != 1 && hitted != 1 && escaped != 1) {

        glm::ivec2 resolution = window->GetResolution();
        dX = mouseX * resolutionx / resolution.x;
        dY = (resolution.y - mouseY) * resolutiony / resolution.y;
        hit = 1;

    }


}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}