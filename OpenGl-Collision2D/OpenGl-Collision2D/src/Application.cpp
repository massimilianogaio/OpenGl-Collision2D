#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Particle.h"
#include "CollisionDetection.h"
#include "Utils.h"

#pragma region Shaders Variables
const char* vertexShaderPath = "src/vertex.shader";
const char* fragmentShaderPath = "src/fragment.shader";
#pragma endregion
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

std::vector<Particle*> particleVector;
bool pressedKey = false;
int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(halfWindowsSize.x * 2 , halfWindowsSize.y * 2, "Collision 2D", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    Particle p1, p2, p3, p4, p5, p6, p7, p8, p9;
    particleVector.push_back(&p1);
    particleVector.push_back(&p2);
    particleVector.push_back(&p3);
    //particleVector.push_back(&p4);
    //particleVector.push_back(&p5);
    //particleVector.push_back(&p6);
    //particleVector.push_back(&p7);
    //particleVector.push_back(&p8);
    //particleVector.push_back(&p9);
    //p1.transform.setScale(vec3(1.0f));
    //p2.transform.setScale(vec3(2.5f));
    //p3.transform.setScale(vec3(2.5f));
    //p4.transform.setScale(vec3(2.5f));
    CollisionDetection collisionDectection = CollisionDetection(vec2(halfWindowsSize), particleVector);

    VertexArray va;
    VertexBuffer vb(p1.getVertices(), p1.getVerticesSize());
    IndexBuffer ib(p1.getIndices(), p1.getIndicesSize());

    VertexBufferLayout layout;
    layout.AddFloat(2);

    va.AddBuffer(vb, layout);

    Shader shader(vertexShaderPath, fragmentShaderPath);
    


    Renderer renderer;
    glm::mat4 projectionMatrix = glm::ortho(-halfWindowsSize.x, halfWindowsSize.x, -halfWindowsSize.y, halfWindowsSize.y, -1.0f, 1.0f);


    while (!glfwWindowShouldClose(window))
    {
        collisionDectection.DetectCollision();
        renderer.Clear();
        for (int i = 0; i < particleVector.size(); i++)
        {
            particleVector[i]->rigidBody->updatePhysics();
            shader.use();
            shader.SetMat4f("m_mvp", projectionMatrix);
            shader.SetMat4f("m_projection", particleVector[i]->transform.getTransformMatrix());
            shader.SetUniform4f("u_Color", particleVector[i]->color.x, 
                particleVector[i]->color.y, 
                particleVector[i]->color.z, 
                particleVector[i]->color.w);

            
            renderer.Draw(va, ib, shader);

        }
       
        processInput(window);
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (!pressedKey && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        fprintf(stdout, "pressed\n");
        Particle* newP = new Particle();
        particleVector.push_back(newP);
        pressedKey = true;
    }
    else if (pressedKey && glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE)
    {
        pressedKey = false;
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