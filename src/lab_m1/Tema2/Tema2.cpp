#include "lab_m1/Tema2/Tema2.h"

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
    {
        tank->createTank(0, 0, 0);
        renderCameraTarget = false;
        camera = new implemented::CameraTema();
        camera->Set(glm::vec3(0, 2, 3.5f), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    }
    // {
    //     Mesh* mesh = new Mesh("box");
    //     mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
    //     meshes[mesh->GetMeshID()] = mesh;
    // }
    //
    // // Create a simple cube
    // {
    //     vector<VertexFormat> vertices
    //     {
    //         VertexFormat(glm::vec3(-1, -1,  1), glm::vec3(0, 1, 1), glm::vec3(0.2, 0.8, 0.2)),
    //         VertexFormat(glm::vec3( 1, -1,  1), glm::vec3(1, 0, 1), glm::vec3(0.9, 0.4, 0.2)),
    //         VertexFormat(glm::vec3(-1,  1,  1), glm::vec3(1, 0, 0), glm::vec3(0.7, 0.7, 0.1)),
    //         VertexFormat(glm::vec3( 1,  1,  1), glm::vec3(0, 1, 0), glm::vec3(0.7, 0.3, 0.7)),
    //         VertexFormat(glm::vec3(-1, -1, -1), glm::vec3(1, 1, 1), glm::vec3(0.3, 0.5, 0.4)),
    //         VertexFormat(glm::vec3( 1, -1, -1), glm::vec3(0, 1, 1), glm::vec3(0.5, 0.2, 0.9)),
    //         VertexFormat(glm::vec3(-1,  1, -1), glm::vec3(1, 1, 0), glm::vec3(0.7, 0.0, 0.7)),
    //         VertexFormat(glm::vec3( 1,  1, -1), glm::vec3(0, 0, 1), glm::vec3(0.1, 0.5, 0.8)),
    //     };
    //
    //     vector<unsigned int> indices =
    //     {
    //         0, 1, 2,        1, 3, 2,
    //         2, 3, 7,        2, 7, 6,
    //         1, 7, 3,        1, 5, 7,
    //         6, 7, 4,        7, 5, 4,
    //         0, 4, 1,        1, 4, 5,
    //         2, 6, 4,        0, 2, 4,
    //     };
    //
    //     CreateMesh("cube", vertices, indices);
    // }
    //
    // Create a shader program for drawing face polygon with the color of the normal
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

}


// Mesh* Tema2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
// {
//     unsigned int VAO = 0;
//     // Create the VAO and bind it
//     glGenVertexArrays(1, &VAO);
//     glBindVertexArray(VAO);
//
//     // Create the VBO and bind it
//     unsigned int VBO;
//     glGenBuffers(1, &VBO);
//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//
//     // Send vertices data into the VBO buffer
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
//
//     // Create the IBO and bind it
//     unsigned int IBO;
//     glGenBuffers(1, &IBO);
//     glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
//
//     // Send indices data into the IBO buffer
//     glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);
//
//     // ========================================================================
//     // This section demonstrates how the GPU vertex shader program
//     // receives data.
//
//     // TODO(student): If you look closely in the `Init()` and `Update()`
//     // functions, you will see that we have three objects which we load
//     // and use in three different ways:
//     // - LoadMesh   + LabShader (this lab's shader)
//     // - CreateMesh + VertexNormal (this shader is already implemented)
//     // - CreateMesh + LabShader (this lab's shader)
//     // To get an idea about how they're different from one another, do the
//     // following experiments. What happens if you switch the color pipe and
//     // normal pipe in this function (but not in the shader)? Now, what happens
//     // if you do the same thing in the shader (but not in this function)?
//     // Finally, what happens if you do the same thing in both places? Why?
//
//     // Set vertex position attribute
//     glEnableVertexAttribArray(0);
//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);
//
//     // Set vertex normal attribute
//     glEnableVertexAttribArray(1);
//     glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));
//
//     // Set texture coordinate attribute
//     glEnableVertexAttribArray(2);
//     glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));
//
//     // Set vertex color attribute
//     glEnableVertexAttribArray(3);
//     glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
//     // ========================================================================
//
//     // Unbind the VAO
//     glBindVertexArray(0);
//
//     // Check for OpenGL errors
//     CheckOpenGLError();
//
//     // Mesh information is saved into a Mesh object
//     meshes[name] = new Mesh(name);
//     meshes[name]->InitFromBuffer(VAO, static_cast<unsigned int>(indices.size()));
//     meshes[name]->vertices = vertices;
//     meshes[name]->indices = indices;
//     return meshes[name];
// }


void Tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(89.0f/255, 192.0f/255, 235.0f/255, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema2::Update(float deltaTimeSeconds)
{
    time = Engine::GetElapsedTime();
    // {
    //     glm::mat4 modelMatrix = glm::mat4(1);
    //     modelMatrix = glm::translate(modelMatrix, glm::vec3(-2, 0.5f, 0));
    //     modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 1, 0));
    //     RenderMesh(meshes["box"], shaders["LabShader"], modelMatrix);
    // }
    //
    // {
    //     glm::mat4 modelMatrix = glm::mat4(1);
    //     modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
    //     modelMatrix = glm::rotate(modelMatrix, RADIANS(45.0f), glm::vec3(0, 1, 0));
    //     modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
    //     RenderSimpleMesh(meshes["cube"], shaders["VertexNormal"], modelMatrix);
    // }
    //
    // {
    //     glm::mat4 modelMatrix = glm::mat4(1);
    //     modelMatrix = glm::translate(modelMatrix, glm::vec3(2, 0.5f, 0));
    //     modelMatrix = glm::rotate(modelMatrix, RADIANS(60.0f), glm::vec3(1, 0, 0));
    //     modelMatrix = glm::scale(modelMatrix, glm::vec3(0.5f));
    //     RenderSimpleMesh(meshes["cube"], shaders["LabShader"], modelMatrix);
    // }
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
    if (renderCameraTarget)
    {
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        RenderMesh(meshes["sphere"], shaders["VertexNormal"], modelMatrix);
    }

}


void Tema2::FrameEnd()
{
    // DrawCoordinateSystem();
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
    glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
    glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // TODO(student): Get shader location for uniform mat4 "Projection"
    int projection = glGetUniformLocation(shader->program, "Projection");

    // TODO(student): Set shader uniform "Projection" to projectionMatrix
    glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
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


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema2::OnInputUpdate(float deltaTime, int mods)
{
    // Add key press event

}


void Tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // // TODO(student): Switch projections
    // if(key == GLFW_KEY_O)
    // {
    //     orthoLeft = -8.0f;
    //     orthoRight = 8.0f;
    //     orthoUp = 4.5f;
    //     orthoDown = -4.5f;
    //     // isPerspective = false;
    //     projectionMatrix = glm::ortho(orthoLeft, orthoRight, orthoDown, orthoUp, zNear, zFar);
    // }

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
