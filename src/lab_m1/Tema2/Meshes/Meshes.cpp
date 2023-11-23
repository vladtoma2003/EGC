#include "Meshes.h"
using namespace m1;

Mesh* Meshes::CreateMesh(const char* name, std::string path)
{
    Mesh* mesh = new Mesh(name);
    mesh->LoadMesh(path, name + std::string(".obj"));
    
    // unsigned int VAO = 0;
    //  // Create the VAO and bind it
    //  glGenVertexArrays(1, &VAO);
    //  glBindVertexArray(VAO);
    //
    //  // Create the VBO and bind it
    //  unsigned int VBO;
    //  glGenBuffers(1, &VBO);
    //  glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //
    //  // Send vertices data into the VBO buffer
    //  glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->vertices[0]) * mesh->vertices.size(), mesh->vertices.data(), GL_STATIC_DRAW);
    //
    //  // Create the IBO and bind it
    //  unsigned int IBO;
    //  glGenBuffers(1, &IBO);
    //  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    //
    //  // Send indices data into the IBO buffer
    //  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh->indices[0]) * mesh->indices.size(), mesh->indices.data(), GL_STATIC_DRAW);
    //
    //  // ========================================================================
    //  // This section demonstrates how the GPU vertex shader program
    //  // receives data.
    //
    //  // TODO(student): If you look closely in the `Init()` and `Update()`
    //  // functions, you will see that we have three objects which we load
    //  // and use in three different ways:
    //  // - LoadMesh   + LabShader (this lab's shader)
    //  // - CreateMesh + VertexNormal (this shader is already implemented)
    //  // - CreateMesh + LabShader (this lab's shader)
    //  // To get an idea about how they're different from one another, do the
    //  // following experiments. What happens if you switch the color pipe and
    //  // normal pipe in this function (but not in the shader)? Now, what happens
    //  // if you do the same thing in the shader (but not in this function)?
    //  // Finally, what happens if you do the same thing in both places? Why?
    //
    //  // Set vertex position attribute
    //  glEnableVertexAttribArray(0);
    //  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);
    //
    //  // Set vertex normal attribute
    //  glEnableVertexAttribArray(1);
    //  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(sizeof(glm::vec3)));
    //
    //  // Set texture coordinate attribute
    //  glEnableVertexAttribArray(2);
    //  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3)));
    //
    //  // Set vertex color attribute
    //  glEnableVertexAttribArray(3);
    //  glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    //  // ========================================================================
    //
    //  // Unbind the VAO
    //  glBindVertexArray(0);
    //
    //  // Check for OpenGL errors
    //  CheckOpenGLError();

     return mesh;
}

// void Meshes::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, glm::vec3 newColor)
// {
//     if (!mesh || !shader || !shader->GetProgramID())
//         return;
//
//     // Render an object using the specified shader and the specified position
//     glUseProgram(shader->program);
//
//     // TODO(student): Get shader location for uniform mat4 "Model"
//     int model = glGetUniformLocation(shader->program, "Model");
//
//     // TODO(student): Set shader uniform "Model" to modelMatrix
//     glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMatrix));
//
//     // TODO(student): Get shader location for uniform mat4 "View"
//     int view = glGetUniformLocation(shader->program, "View");
//     
//
//     // TODO(student): Set shader uniform "View" to viewMatrix
//     glm::mat4 viewMatrix = GetSceneCamera()->GetViewMatrix();
//     glUniformMatrix4fv(view, 1, GL_FALSE, glm::value_ptr(viewMatrix));
//
//     // TODO(student): Get shader location for uniform mat4 "Projection"
//     int projection = glGetUniformLocation(shader->program, "Projection");
//
//     // TODO(student): Set shader uniform "Projection" to projectionMatrix
//     glm::mat4 projectionMatrix = GetSceneCamera()->GetProjectionMatrix();
//     glUniformMatrix4fv(projection, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
//
//     int time = 0;
//     int timeLocation = glGetUniformLocation(shader->program, "Time");
//     glUniform1f(timeLocation, 2*abs(sinf(time)));
//
//     // glm::vec3 newColor = glm::vec3(15.f/2555, 39.f/255, 10.f/255);
//     int colorLocation = glGetUniformLocation(shader->program, "ObjectColor");
//     glUniform3fv(colorLocation, 1, glm::value_ptr(newColor));
//     
//     // Draw the object
//     glBindVertexArray(mesh->GetBuffers()->m_VAO);
//     glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, 0);
// }