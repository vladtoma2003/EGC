﻿#include "Meshes.h"
// #include "../camera.h"

using namespace m1;

Mesh* Meshes::CreateMesh(const char* name, std::string path)
{
    Mesh* mesh = new Mesh(name);
    mesh->LoadMesh(path, name + std::string(".obj"));
    return mesh;
}
void Meshes::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, glm::vec3 newColor, implemented::CameraTema *camera,
    float time, glm::mat4 projectionMatrix)
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