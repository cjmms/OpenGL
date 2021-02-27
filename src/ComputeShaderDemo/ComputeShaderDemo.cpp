#include "ComputeShaderDemo.h"

ComputeShaderDemo::ComputeShaderDemo()
{
    float planeVertices[] = {
        // positions            // normals         // texcoords
         0.5f, 0.5f,  -1.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -0.5f, -0.5f,  -1.0f,  0.0f, 1.0f, 0.0f,   0.0f,  0.0f,
        -0.5f, 0.5f,  -1.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,

         0.5f, 0.5f,  -1.0f,  0.0f, 1.0f, 0.0f,  10.0f,  0.0f,
        -0.5f, -0.5f,  -1.0f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
         0.5f, -0.5f,  -1.0f,  0.0f, 1.0f, 0.0f,  10.0f, 10.0f
    };

    unsigned int VAO, VBO;

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(planeVertices), planeVertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);
}



void ComputeShaderDemo::render(glm::mat4 view, glm::mat4 projection, Shader& shader, Texture& texture)
{
    glm::mat4 model(1.0);
    model = glm::translate(model, glm::vec3(0.0, 1.0, 0.0));
    shader.setMat4("mvp", projection * view * model);

    glDrawArrays(GL_TRIANGLES, 0, 6);
}



int runComputeShaderDemo()
{
    GLFWwindow* window;

    // Initialize the library 
    if (!glfwInit())
        return -1;

    // Create a windowed mode window and its OpenGL context 
    window = glfwCreateWindow(1200, 1000, "Vanilla", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Make the window's context current 
    glfwMakeContextCurrent(window);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    if (glewInit() != GLEW_OK)
        std::cout << "init error" << std::endl;

    glEnable(GL_PROGRAM_POINT_SIZE);
    glEnable(GL_DEPTH_TEST);

    Shader shader("res/Shaders/ComputeShaderDemo/basic.shader");
    shader.Bind();

    Texture texture("res/Textures/wood.jpg", JPG);
    shader.setInt("texture_wood", 0);


    ComputeShaderDemo renderer;

    // Loop until the user closes the window 
    while (!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Render here 
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera.cameraUpdateFrameTime();

        glm::mat4 projection = camera.getProjectionMatrix();
        glm::mat4 view = camera.getViewMatrix();

        renderer.render(view, projection, shader, texture);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}