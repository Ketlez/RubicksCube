#include <glad/glad.h>
#include <GLFW/glfw3.h>
#define _USE_MATH_DEFINES
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Camera.h"

#include "Shader.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <iostream>
#include <string>
#include <cmath>

#include <ctime>

#include "CubeRub.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 500;
const unsigned int SCR_HEIGHT = 500;

bool fullsize = false;
bool fullscreen = false;

float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

Camera camera(glm::vec3(0.0f, 0.0f, 5.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;


int main()
{

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    glfwWindowHint(GLFW_SAMPLES, 16);   // default is a 4
    

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    
    // build and compile our shader program
    Shader shaderProgram("FvertexShader.txt", "FfragmentShader.txt");

    glEnable(GL_DEPTH_TEST);
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    
    float vertices[] = {
    -0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
    0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
   -0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
   -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 0.0f,

   -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
    0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
   -0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f,
   -0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f,

   -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,
   -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 0.0f,

   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
   -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
   -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,
   -0.5f, -0.5f,  0.5f,  0.0f, 1.0f, 1.0f,
   -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 1.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 1.0f,

    0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
   -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
   -0.5f,  0.5f, -0.5f,  0.0f, 0.0f, 1.0f,
   -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 1.0f,
    };

    unsigned int indices[] = {  // note that we start from 0!
        0, 1, 3,   // first triangle
        1, 2, 3
    };

    
    VAO vao;
    VBO vbo;
    EBO ebo;
    vao.bind();
    vbo.bind();
    vbo.setData(vertices, sizeof(vertices));
    ebo.bind();
    ebo.setData(indices, sizeof(indices));
    vao.attribPointer(0, 3, GL_FLOAT, 6 * sizeof(float), 0);
    vao.attribPointer(1, 3, GL_FLOAT, 6 * sizeof(float), 3 * sizeof(float));

    Texture texture1;
    // load and generate the texture
    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load("texture/TextureBasik.jpg", &width, &height, &nrChannels, 0);
    texture1.setData(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, width, height, data);
    stbi_image_free(data);

    shaderProgram.use();
    
    Texture texture2;
    data = stbi_load("texture/TextureBasik2.jpg", &width, &height, &nrChannels, 0);
    texture2.setData(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, width, height, data);
    stbi_image_free(data);

    shaderProgram.use();
    
    texture1.activeTexture(0);
    texture1.bind();
    texture2.activeTexture(1);
    texture2.bind();

    shaderProgram.setInt("ourTexture1", 0);
    shaderProgram.setInt("ourTexture2", 1);
    CubRub cub;
    int w, h;
    glEnable(GL_CULL_FACE);
    glEnable(GL_MULTISAMPLE);
    float delTime = 0.f;
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    while (!glfwWindowShouldClose(window))
    {   
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwGetWindowSize(window, &w, &h);

        shaderProgram.use();
        vao.bind();

        glm::mat4 view = camera.GetViewMatrix();

        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(camera.Zoom), (float)w / (float)h, 0.01f, 100.0f);

        
        shaderProgram.setMatrix("view", view);
        shaderProgram.setMatrix("projection", projection);

        shaderProgram.setFloat("time", (float)glfwGetTime());
        
     
          
            
        cub.Move(deltaTime, shaderProgram, Move::F_);
        
        

        
        
        //glDrawArrays(GL_TRIANGLES, 0, 36);
                
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
}

void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
    
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_F && action == GLFW_PRESS)
    {
        if (fullsize)
        {
            glfwRestoreWindow(window);
            fullsize = false;

        }
        else
        {
            fullsize = true;
            glfwMaximizeWindow(window);
        }
    }

    if (key == GLFW_KEY_ENTER && action == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS ||
        key == GLFW_KEY_LEFT_ALT && action == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
    {
        if (fullscreen)
        {
            glfwSetWindowMonitor(window, NULL, 200, 200, 800, 600, GLFW_DONT_CARE);
            fullscreen = false;
            glfwRestoreWindow(window);
            fullsize = false;
        }
        else
        {
            int w, h;
            int x, y;
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            glfwGetMonitorWorkarea(monitor, &x, &y, &w, &h);
            //const GLFWvidmode* mode = glfwGetVideoMode(monitor);
            glfwSetWindowMonitor(window, monitor, x, y, w, h, GLFW_DONT_CARE);//mode->refreshRate);
            fullscreen = true;
        }
    }
}
// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}