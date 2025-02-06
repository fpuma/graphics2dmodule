#pragma once

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

struct CubeData
{
    GLuint VBO, VAO, EBO;
    GLuint shaderProgram;
}gCubeData;

// Vertex Shader Source Code
const char* vertexShaderSourceCube = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    FragPos = vec3(model * vec4(aPos, 1.0));
    Normal = mat3(transpose(inverse(model))) * aNormal;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
}
)";

// Fragment Shader Source Code
const char* fragmentShaderSourceCube = R"(
#version 330 core
in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main() {
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;

    vec3 result = (ambient + diffuse) * objectColor;
    FragColor = vec4(result, 1.0);
}
)";

void initCubeTest()
{
    float vertices[] = {
        // Positions          // Normals
        -0.5f, -0.5f, -0.5f,  -1.0f,  -1.0f, -1.0f,
         0.5f, -0.5f, -0.5f,   1.0f,  -1.0f, -1.0f,
         0.5f,  0.5f, -0.5f,   1.0f,   1.0f, -1.0f,
        -0.5f,  0.5f, -0.5f,  -1.0f,   1.0f, -1.0f,
        -0.5f, -0.5f,  0.5f,  -1.0f,  -1.0f,  1.0f,
         0.5f, -0.5f,  0.5f,   1.0f,  -1.0f,  1.0f,
         0.5f,  0.5f,  0.5f,   1.0f,   1.0f,  1.0f,
        -0.5f,  0.5f,  0.5f,  -1.0f,   1.0f,  1.0f
    };

    unsigned int indices[] = {
        0, 1, 2, 2, 3, 0,
        1, 5, 6, 6, 2, 1,
        7, 6, 5, 5, 4, 7,
        4, 0, 3, 3, 7, 4,
        4, 5, 1, 1, 0, 4,
        3, 2, 6, 6, 7, 3
    };

    glGenVertexArrays(1, &gCubeData.VAO);
    glBindVertexArray(gCubeData.VAO);
    
    glGenBuffers(1, &gCubeData.EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gCubeData.EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    glGenBuffers(1, &gCubeData.VBO);
    glBindBuffer(GL_ARRAY_BUFFER, gCubeData.VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    gCubeData.shaderProgram = createShaderProgram(vertexShaderSourceCube, fragmentShaderSourceCube);
}

void updateCubeTest()
{
    glUseProgram(gCubeData.shaderProgram);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 5.0f));
    model = glm::rotate(model, (float)SDL_GetTicks() / 1000.0f, glm::vec3(0.5f, 1.0f, 0.0f));
    GLuint modelLoc = glGetUniformLocation(gCubeData.shaderProgram, "model");
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
    
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -10.0f));
    GLuint viewLoc = glGetUniformLocation(gCubeData.shaderProgram, "view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
    
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
    GLuint projLoc = glGetUniformLocation(gCubeData.shaderProgram, "projection");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
    
    glm::vec3 lightPos(0.0f, 1.5f, 6.0f);
    GLuint lightPosLoc = glGetUniformLocation(gCubeData.shaderProgram, "lightPos");
    glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
    
    glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
    GLuint lightColLoc = glGetUniformLocation(gCubeData.shaderProgram, "lightColor");
    glUniform3fv(lightColLoc, 1, glm::value_ptr(lightColor));
    
    glm::vec3 objColor(64.0f/255.0f, 224.0f/255.0f, 208.0f/255.0f);
    GLuint objColLoc = glGetUniformLocation(gCubeData.shaderProgram, "objectColor");
    glUniform3fv(objColLoc, 1, glm::value_ptr(objColor));

    glBindVertexArray(gCubeData.VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    
}

void uninitCubeTest()
{
    glDeleteVertexArrays(1, &gCubeData.VAO);
    glDeleteBuffers(1, &gCubeData.VBO);
    glDeleteBuffers(1, &gCubeData.EBO);
    glDeleteProgram(gCubeData.shaderProgram);
}