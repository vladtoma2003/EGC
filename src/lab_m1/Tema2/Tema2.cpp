#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

#include "Vehicles/Cannon.h"
#include "Vehicles/Tracks.h"
#include "Vehicles/Turret.h"

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema2::Tema2()
{
}


Tema2::~Tema2()
{
}


void Tema2::Init()
{
    renderCameraTarget = false;

    tank = new Tank();
    tank->createTank(0, tank->getScale(), 0);
    
    camera = new implemented::CameraTema();
    camera->Set(tank->getPosition() + glm::vec3(-3.5f, 1.5, 0), tank->getPosition(), glm::vec3(0, 1, 0));
    {
        Shader *shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }
    {
        Mesh* mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Big square for ground
    {
        vector<VertexFormat> vertices{
            VertexFormat (glm::vec3(0, 0, 0), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 0
            VertexFormat (glm::vec3(1, 0, -1), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 1
            VertexFormat (glm::vec3(1, 0, 1), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 2
            VertexFormat (glm::vec3(-1, 0, -1), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 3
            VertexFormat (glm::vec3(-1, 0, 1), glm::vec3( 55.f/255, 112.f/255, 32.f/255)), // 4
        };
        vector<unsigned int> indices{
            1, 2, 3,
            2, 3, 4,
        };
        meshes["ground"] = Meshes::CreateMesh("ground", vertices, indices);
    }
    
    aspectRatio = window->props.aspectRatio;
    projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
    
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(28.f/255, 84.f/255, 199.f/255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    // (gay ball)
    tank->renderTank(camera, projectionMatrix, shaders, time);
    if (renderCameraTarget)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
         Meshes::RenderSimpleMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 0, 0), camera, time, projectionMatrix);
    }
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 0.f, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(100.f));
        Meshes::RenderSimpleMesh(meshes["ground"], shaders["LabShader"], modelMatrix, glm::vec3(55.f/255, 112.f/255, 32.f/255), camera, time, projectionMatrix);
    }
    for(auto projectile:tank->getProjectiles())
    {
        projectile->moveProjectile(projectile->getSpeed() * deltaTimeSeconds, deltaTimeSeconds);
        projectile->checkTimeOut();
    }
    tank->removeProjectiles();
    
    // Set Tank position to camera
    if(!vClipping)
    {
        camera->Set(tank->getPosition(), glm::vec3(0, 1, 0));
    }
}



void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}
/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    float cameraSpeed = 2.0f;
    if (window->KeyHold(GLFW_KEY_W)) {
        if(vClipping)
        {
            camera->TranslateForward(deltaTime*cameraSpeed*10);
        } else {
            tank->moveTank(deltaTime*cameraSpeed);
            camera->MoveForward(deltaTime*cameraSpeed, tank->getTankForward());
        }
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        if(vClipping)
        {
            camera->TranslateRight(-deltaTime*cameraSpeed*10);
        } else
        {
            tank->rotateTank(RADIANS(1));
            camera->TranslateForward(2);
            camera->RotateThirdPerson_OY(RADIANS(1));
            camera->TranslateForward(-2);
        }
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        if(vClipping)
        {
            camera->TranslateForward(-deltaTime*cameraSpeed*10);
        } else {
            tank->moveTank(-deltaTime*cameraSpeed);
            camera->MoveForward(-deltaTime*cameraSpeed, tank->getTankForward());
        }
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        if(vClipping)
        {
            camera->TranslateRight(deltaTime*cameraSpeed*10);
        } else
        {
            tank->rotateTank(-RADIANS(1));
            camera->TranslateForward(2);
            camera->RotateThirdPerson_OY(-RADIANS(1));
            camera->TranslateForward(-2);
        }
    }

    if (window->KeyHold(GLFW_KEY_Q)) {
        // TODO(student): Translate the camera downward
        if(vClipping)
        {
            camera->TranslateUpward(-deltaTime*cameraSpeed*10);
        }
    }
    if (window->KeyHold(GLFW_KEY_E)) {
        if(vClipping)
        {
            camera->TranslateUpward(deltaTime*cameraSpeed*10);
        }
    }

    
    if(isPerspective && window->KeyHold(GLFW_KEY_F))
    {
        fov += 0.5f*deltaTime;
        projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
    }
    if(isPerspective && window->KeyHold(GLFW_KEY_R))
    {
        fov -= 0.5f*deltaTime;
        projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
    }
    if(!isPerspective && window->KeyHold(GLFW_KEY_K))
    {
        orthoLeft += 0.5f*deltaTime;
        orthoRight -= 0.5f*deltaTime;
        orthoUp -= 0.5f*deltaTime;
        orthoDown += 0.5f*deltaTime;
        projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.00f, 200.0f);
    }
    if(!isPerspective && window->KeyHold(GLFW_KEY_L))
    {
        orthoLeft -= 0.5f*deltaTime;
        orthoRight += 0.5f*deltaTime;
        orthoUp += 0.5f*deltaTime;
        orthoDown -= 0.5f*deltaTime;
        projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, 0.00f, 200.0f);
    }
    
}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections
    if(key == GLFW_KEY_O)
    {
        orthoLeft = -8.0f;
        orthoRight = 8.0f;
        orthoUp = 4.5f;
        orthoDown = -4.5f;
        isPerspective = false;
        projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, zNear, zFar);
    }
    if (key == GLFW_KEY_P)
    {
        projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
        isPerspective = true;
    }
    if(key == GLFW_KEY_V)
    {
        vClipping = !vClipping;
        if(!vClipping) // reset camera
        {
            glm::vec3 newPos = glm::normalize(glm::vec3(tank->getTankForward().x, 0, tank->getTankForward().z))*3.5f;
            newPos += glm::vec3(0, -1.5, 0);
            camera->Set(tank->getPosition() - newPos , tank->getPosition(), glm::vec3(0, 1, 0));
        }
    }

    if(key == GLFW_KEY_L)
    {
        tank->updatePosition(0,0,0);
    }
}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    float sensivityOX = 0.001f;
    float sensivityOY = 0.001f;
    // Add mouse move event
    if(!vClipping)
    {
        if(window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
        {
            camera->RotateThirdPerson_OX(-sensivityOX*deltaY);
            camera->RotateThirdPerson_OY(-sensivityOY*deltaX);
        } else
        {
            tank->getTurret()->incDeltaX(10*(deltaX>1?1:deltaX< -1?-1:0));
            tank->getCannon()->incDeltaX(10*(deltaX>1?1:deltaX < -1?-1:0));
            tank->getTurret()->rotateTurret(-sensivityOY*tank->getTurret()->getDeltaX());
            tank->getCannon()->rotateCannon(-sensivityOY*tank->getCannon()->getDeltaX());
            tank->getTurret()->setDeltaX(0);
            tank->getCannon()->setDeltaX(0);
            
        }
    }
    else
    {
        if(window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
        {
            camera->RotateFirstPerson_OX(-sensivityOX*deltaY);
            camera->RotateFirstPerson_OY(-sensivityOY*deltaX);
        }
    }
    // std::cout << "sensitivityOX: " << sensivityOX << " sensitivityOY: " << sensivityOY << "\n";
    // std:: cout << tank->getTurret()->getTurretAngle() << "\n";
    // std::cout << "deltaX: " << deltaX << " deltaY: " << deltaY << "\n";
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if(button == 1)
    {
        tank->shoot();
    }
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
    if(button == 2)
    {
        glm::vec3 newPos = glm::normalize(glm::vec3(tank->getTankForward().x, 0, tank->getTankForward().z))*3.5f;
        newPos += glm::vec3(0, -1.5, 0);
        camera->Set(tank->getPosition() - newPos, tank->getPosition(), glm::vec3(0, 1, 0));
    }
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
