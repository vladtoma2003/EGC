﻿#include "Tema2.h"

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

    camera = new implemented::CameraTema();
    camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    tank = new Tank();
    tank->createTank(camera->GetTargetPosition().x, camera->GetTargetPosition().y, camera->GetTargetPosition().z);
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
    // TODO(student): After you implement the changing of the projection
    // parameters, remove hardcodings of these parameters
    aspectRatio = window->props.aspectRatio;
    projectionMatrix = glm::perspective(fov, aspectRatio, zNear, zFar);
    
}


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
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
    
    // Set Tank position to camera
    tank->updatePosition(camera->GetTargetPosition().x, camera->GetTargetPosition().y, camera->GetTargetPosition().z);
    
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
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float cameraSpeed = 2.0f;

        if (window->KeyHold(GLFW_KEY_W)) {
            // TODO(student): Translate the camera forward
            camera->TranslateForward(deltaTime*cameraSpeed);
            // tank->moveTank(deltaTime*cameraSpeed, 0, 0);
        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // TODO(student): Translate the camera to the left
            camera->TranslateRight(-deltaTime*cameraSpeed);
            // tank->moveTank(0, 0, -deltaTime*cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // TODO(student): Translate the camera backward
            camera->TranslateForward(-deltaTime*cameraSpeed);
            // tank->moveTank(-deltaTime*cameraSpeed, 0, 0);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            camera->TranslateRight(deltaTime*cameraSpeed);
            // tank->moveTank(0, 0, deltaTime*cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_Q)) {
            // TODO(student): Translate the camera downward
            camera->TranslateUpward(-deltaTime*cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_E)) {
            // TODO(student): Translate the camera upward
            camera->TranslateUpward(deltaTime*cameraSpeed);
        }
    }

    // TODO(student): Change projection parameters. Declare any extra
    // variables you might need in the class header. Inspect this file
    // for any hardcoded projection arguments (can you find any?) and
    // replace them with those extra variables.
    
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

}


void Tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        // if (window->GetSpecialKeyState() == 0) {
        //     renderCameraTarget = false;
        //     // TODO(student): Rotate the camera in first-person mode around
        //     // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
        //     // variables for setting up the rotation speed.
        //     camera->RotateFirstPerson_OX(-sensivityOX*deltaY);
        //     camera->RotateFirstPerson_OY(-sensivityOY*deltaX);
        //
        // }

        // if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OX(-sensivityOX*deltaY);
            camera->RotateThirdPerson_OY(-sensivityOY*deltaX);
        // }
    }
}


void Tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}


void Tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema2::OnWindowResize(int width, int height)
{
}
