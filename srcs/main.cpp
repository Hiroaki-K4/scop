#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.h"
#include "Parser.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "ERROR: You should run ./scop [obj file name]" << std::endl;
        return EXIT_FAILURE;
    }

    if(!glfwInit()){
        std::cout << "ERROR: Failed to initialize GLFW" << std::endl;
        return EXIT_FAILURE;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) {
        std::cout << "ERROR: Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "ERROR: Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Build and compile our shader program
    Shader ourShader("texture.vs", "texture.fs");

    std::string obj_file_name = argv[1];

    Parser p("../resources/" + obj_file_name);
    std::vector<std::vector<double>> obj_vertices;
    std::vector<std::vector<int>> obj_face_elements;
    p.parse_obj_file(obj_vertices, obj_face_elements);
    std::vector<std::vector<double>> polygons;
    p.create_polygons(obj_vertices, obj_face_elements, polygons);
    const int info_num = 5;
    std::cout << "SIZE: " << polygons.size() * info_num << std::endl;
    float new_vertices[polygons.size() * info_num];
    p.convert_polygons_vector_to_float_vertices(polygons, info_num);
    // float vertices[] = {
    //     // positions          // texture coords
    //     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,
    //     0.5f, -0.5f, -0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,

    //     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 1.0f,
    //     -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,

    //     -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //     -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //     -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    //     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //     0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,

    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,
    //     0.5f, -0.5f, -0.5f, 1.0f, 1.0f,
    //     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    //     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,
    //     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,
    //     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,

    //     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,
    //     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,
    //     -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,
    //     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f
    // };
    float vertices[] = {
        // positions          // texture coords
        0.232406, -1.216630, 1.133818, 0.0f, 0.0f,
        0.232406, -0.745504, 2.843098, 0.0f, 0.0f,
        -0.227475, -0.745504, 2.843098, 0.0f, 0.0f,
        -0.227475, -1.216630, 1.133818, 0.0f, 0.0f,
        0.232407, 1.119982, 1.133819, 0.0f, 0.0f,
        0.232406, 1.119982, 1.602814, 0.0f, 0.0f,
        -0.227475, 1.119982, 1.602813, 0.0f, 0.0f,
        -0.227475, 1.119982, 1.133818, 0.0f, 0.0f,
        0.232406, -0.340316, 2.843098, 0.0f, 0.0f,
        -0.227475, -0.340316, 2.843098, 0.0f, 0.0f,
        0.232407, -0.305193, 1.133819, 0.0f, 0.0f,
        0.232407, -0.294496, 2.297937, 0.0f, 0.0f,
        -0.227475, -0.305193, 1.133818, 0.0f, 0.0f,
        -0.227475, -0.294496 ,2.297937, 0.0f, 0.0f,
        0.232406, -1.222569, 1.497195, 0.0f, 0.0f,
        0.232406, -0.745504, 1.477731, 0.0f, 0.0f,
        -0.227475, -0.745504, 1.477731, 0.0f, 0.0f,
        -0.227475, -1.222569, 1.497194, 0.0f, 0.0f,
        -0.227403, -0.731178, 0.901477, 0.0f, 0.0f,
        -0.227403, -0.731178, -0.037620, 0.0f, 0.0f,
        0.223704, -0.731178, -0.037620, 0.0f, 0.0f,
        0.223704, -0.731178, 0.901477, 0.0f, 0.0f,
        -0.227403, 1.119377, 0.901477, 0.0f, 0.0f,
        -0.227403, 1.119377, -0.037620, 0.0f, 0.0f,
        0.223704, 1.119377, -0.037620, 0.0f, 0.0f,
        0.223704, 1.119377, 0.901477, 0.0f, 0.0f,
        -0.227403, -0.129772, 0.901477, 0.0f, 0.0f,
        -0.227403, 0.551492, 0.384487, 0.0f, 0.0f,
        -0.227403, 1.104268, 0.408501, 0.0f, 0.0f,
        -0.227403, 0.507336, 0.901477, 0.0f, 0.0f,
        0.223704, 0.507336, 0.901477, 0.0f, 0.0f,
        0.223704, 1.104269, 0.408501, 0.0f, 0.0f,
        0.223704, 0.551492, 0.384487, 0.0f, 0.0f,
        0.223704, -0.129772, 0.901477, 0.0f, 0.0f,
        -0.227403, 0.634134, -0.037620, 0.0f, 0.0f,
        -0.227403, -0.066768, 0.398575, 0.0f, 0.0f,
        -0.227403, -0.684649, 0.389681, 0.0f, 0.0f,
        -0.227403, -0.075523, -0.037620, 0.0f, 0.0f,
        0.223704, 0.634134, -0.037620, 0.0f, 0.0f,
        0.223704, -0.066768, 0.398575, 0.0f, 0.0f,
        0.223704, -0.684649, 0.389681, 0.0f, 0.0f,
        0.223704, -0.075523, -0.037620, 0.0f, 0.0f,
    };
    // Setup VAO
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind vertex array object
    glBindVertexArray(VAO);

    // Copy our vertices array in a buffer for OpenGL to use
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // Position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // Texture attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // Create texture
    unsigned int texture1, texture2;
    // texture 1
    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    // Set the texture wrapping/filtering options (on currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char *data = stbi_load("../resources/textures/container.jpg", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    // texture2
    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    // Set the texture wrapping/filtering options (on currently bound texture)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Load and generate the texture
    data = stbi_load("../resources/textures/awesomeface.png", &width, &height, &nrChannels, 0);
    if (data) {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    glEnable(GL_DEPTH_TEST);

    // Render loop
    while (!glfwWindowShouldClose(window)) {
        // Input
        processInput(window);

        // Render
        // Clear the colorbuffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        // Project to 2D
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);
        model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f),
                    glm::vec3(0.5f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
        projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

        unsigned int modelLoc = glGetUniformLocation(ourShader.ID, "model");
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        unsigned int projLoc = glGetUniformLocation(ourShader.ID, "projection");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, &projection[0][0]);

        // Render the triangle
        ourShader.use();
        glBindVertexArray(VAO);
        // glDrawArrays(GL_TRIANGLES, 0, 36);
        glDrawArrays(GL_POINTS, 0, 42);

        // Swap buffers and poll IO events
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Optional: de-allocate all resources once they've outlived their purpose
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();

    return 0;
}
