#include "Tema2.h"

#include <vector>
#include <string>
#include <iostream>

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

    {
        Shader *shader = new Shader("LabShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Tema2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    {
        Mesh* mesh = new Mesh("body");
        mesh->LoadMesh(MODELS_PATH, "body/body.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh *mesh = new Mesh("track");
        mesh->LoadMesh(MODELS_PATH, "track/track.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("turret");
        mesh->LoadMesh(MODELS_PATH, "turret/turret.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }
    {
        Mesh* mesh = new Mesh("pipe");
        mesh->LoadMesh(MODELS_PATH, "pipe/pipe.obj");
        meshes[mesh->GetMeshID()] = mesh;
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
    { // Body
        glm::mat4 modelMatrix = glm::mat4(1);
        // modelMatrix = glm::translate(modelMatrix, glm::vec3(10.f, -20.f, 10.f));
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 0.5f, 0.f));    
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
        RenderSimpleMesh(meshes["body"], shaders["LabShader"], modelMatrix, glm::vec3(15.f/255, 39.f/255, 10.f/255));
    }
    { // Track Left
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(-1.f, 0.25f, 0.f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.75f, 0.5f));
        RenderSimpleMesh(meshes["track"], shaders["LabShader"], modelMatrix, glm::vec3(50.f/255, 50.f/255, 50.f/255));
    }
    { // Track Right
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(1.f, 0.25f, 0.f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.75f, 0.5f));
        RenderSimpleMesh(meshes["track"], shaders["LabShader"], modelMatrix, glm::vec3(50.f/255, 50.f/255, 50.f/255));
    }
    { // Turret
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 1.f, -0.5f));
    modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.75f, 0.5f));
    RenderSimpleMesh(meshes["turret"], shaders["LabShader"], modelMatrix, glm::vec3(30.f/255, 49.f/255, 30.f/255));
    }
    { // Pipe
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(0.f, 1.f, 1.25f));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f, 0.75f, 0.5f));
        RenderSimpleMesh(meshes["pipe"], shaders["LabShader"], modelMatrix, glm::vec3(50.f/255, 50.f/255, 50.f/255));
    }
    // Render the gay ball
    // if (renderCameraTarget)
    // {
    //     glm::mat4 modelMatrix = glm::mat4(1);
    //     modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
    //     modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
    //     RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
    // }

    if (renderCameraTarget)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderSimpleMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix, glm::vec3(1, 0, 0));
    }
}


void Tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}
void Tema2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, glm::vec3 newColor)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    // TODO(student): Get shader location for uniform mat4 "Model"
    int model = glGetUniformLocation(shader->program, "Model");

    // TODO(student): Set shader uniform "Model" to modelMatrix
    glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // TODO(student): Get shader location for uniform mat4 "View"
    int view = glGetUniformLocation(shader->program, "View");
    

    // TODO(student): Set shader uniform "View" to viewMatrix
    // glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // TODO(student): Get shader location for uniform mat4 "Projection"
    int projection = glGetUniformLocation(shader->program, "Projection");

    // TODO(student): Set shader uniform "Projection" to projectionMatrix
    // glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
    glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    int timeLocation = glGetUniformLocation(shader->program, "Time");
    glUniform1f(timeLocation, 2*abs(sinf(time)));

    // glm::vec3 newColor = glm::vec3(15.f/2555, 39.f/255, 10.f/255);
    int colorLocation = glGetUniformLocation(shader->program, "ObjectColor");
    glUniform3fv(colorLocation, 1, glm::value_ptr(newColor));
    
    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
}

// void Tema2::RenderMesh(Mesh * mesh, Shader * shader, const glm::mat4 & modelMatrix)
// {
//     if (!mesh || !shader || !shader->program)
//         return;
//
//     // Render an object using the specified shader and the specified position
//     shader->Use();
//     glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
//     glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//     glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));
//
//     mesh->Render();
// }


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

        }

        if (window->KeyHold(GLFW_KEY_A)) {
            // TODO(student): Translate the camera to the left
            camera->TranslateRight(-deltaTime*cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_S)) {
            // TODO(student): Translate the camera backward
            camera->TranslateForward(-deltaTime*cameraSpeed);
        }

        if (window->KeyHold(GLFW_KEY_D)) {
            // TODO(student): Translate the camera to the right
            camera->TranslateRight(deltaTime*cameraSpeed);
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

        if (window->GetSpecialKeyState() == 0) {
            renderCameraTarget = false;
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateFirstPerson_OX(-sensivityOX*deltaY);
            camera->RotateFirstPerson_OY(-sensivityOY*deltaX);

        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL) {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OX(-sensivityOX*deltaY);
            camera->RotateThirdPerson_OY(-sensivityOY*deltaX);
        }
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
