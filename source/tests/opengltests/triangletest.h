#pragma once

struct TriangleData
{
    GLuint shaderProgram;
    GLuint VAO;
    GLuint VBO;
}gTriData;

// Vertex Shader Source Code
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 vertexColor;

void main() {
    gl_Position = vec4(aPos, 1.0);
    vertexColor = aColor;
}
)";

// Fragment Shader Source Code
const char* fragmentShaderSource = R"(
#version 330 core
in vec3 vertexColor;

out vec4 FragColor;

void main() {
    FragColor = vec4(vertexColor, 1.0);
}
)";

void initTriTest()
{
    // Define vertex data for a triangle
    float vertices[] =
    {
        // Positions        // Colors
         0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f
    };

    // Create a Vertex Buffer Object (VBO) and Vertex Array Object (VAO)
    
    glGenVertexArrays(1, &gTriData.VAO);
    glGenBuffers(1, &gTriData.VBO);

    glBindVertexArray(gTriData.VAO);

    glBindBuffer(GL_ARRAY_BUFFER, gTriData.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    gTriData.shaderProgram = createShaderProgram(vertexShaderSource, fragmentShaderSource);
}

void updateTriTest()
{
    // Use shader program
    glUseProgram(gTriData.shaderProgram);

    // Draw the triangle
    glBindVertexArray(gTriData.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void uninitTriTest()
{
    glDeleteVertexArrays(1, &gTriData.VAO);
    glDeleteBuffers(1, &gTriData.VBO);
    glDeleteProgram(gTriData.shaderProgram);
}