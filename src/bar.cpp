#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
using namespace std;

#include "headers/shader.hpp"
#include "headers/mesh.hpp"

#include "headers/vectors.hpp"

#include "headers/bar.hpp"

// mesh for bars
Mesh barMesh;

// bar shader
Shader barShader;

void InitBar() {
    // create vertex array and buffers
    unsigned int vao, vbo, ebo;

    // generate vertex arrays and buffers
    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ebo);

    // vertices
    float vertices[] = {
        0.0f, 0.0f, 0.0f, // top left
        barWidth, 0.0f, 0.0f, // top right
        barWidth, -2.0f, 0.0f, // bottom right
        0.0f, -2.0f, 0.0f, // bottom left
    };

    // indices
    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0,
    };

    // bind vao
    glBindVertexArray(vao);

    // load vertices into vbo
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // load indices into ebo
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
    glEnableVertexAttribArray(0);

    // create shader object
    barShader = Shader("shaders/bar.vert", "shaders/bar.frag");

    // load all the data into our private mesh object
    barMesh = {
        vao,
        vbo,
        ebo,

        &barShader,
    };
}

// draws a bar with given parameters
void DrawBar(float x, float y, float height, Vector4 color) {
    // bind vao
    glBindVertexArray(barMesh.VAO);

    // use shader
    barMesh.SHADER->Use();

    // pass position
    barMesh.SHADER->SetUniform2f("position", x, y);

    // pass height
    barMesh.SHADER->SetUniform1f("height", height);

    // pass color
    barMesh.SHADER->SetUniform4f("color", color.x, color.y, color.z, color.w);

    // draw the bar
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    // cleanup
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}