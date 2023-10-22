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
#include "Square.h"

#pragma region Shaders Variables
const char* vertexShaderPath = "src/vertex.shader";
const char* fragmentShaderPath = "src/fragment.shader";
#pragma endregion
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

std::vector<Particle*> particleVector;
std::vector<Square*> squareVector;

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

    Particle p1;
    Square s1;

    CollisionDetection collisionDectection = CollisionDetection(vec2(halfWindowsSize), particleVector);

    

    VertexArray vaSquare;
    VertexBuffer vbSquare(s1.getVertices(), s1.getVerticesSize());
    IndexBuffer ibSquare(s1.getIndices(), s1.getIndicesSize());

    VertexBufferLayout layoutSquare;
    layoutSquare.AddFloat(3);
    vaSquare.AddBuffer(vbSquare, layoutSquare);

    VertexArray vaParticle;
    VertexBuffer vbParticle(p1.getVertices(), p1.getVerticesSize());
    IndexBuffer ibParticle(p1.getIndices(), p1.getIndicesSize());

    VertexBufferLayout layoutParticle;
    layoutParticle.AddFloat(2);
    vaParticle.AddBuffer(vbParticle, layoutParticle);


    Shader shader(vertexShaderPath, fragmentShaderPath);
    


    Renderer renderer;
    glm::mat4 projectionMatrix = glm::ortho(-halfWindowsSize.x, halfWindowsSize.x, -halfWindowsSize.y, halfWindowsSize.y, -1.0f, 1.0f);


    while (!glfwWindowShouldClose(window))
    {
        collisionDectection.DetectCollision();
        renderer.Clear();
        for (int i = 0; i < squareVector.size(); i++)
        {
            //squareVector[i]->rigidBody->updatePhysics();
            shader.use();
            shader.SetMat4f("m_mvp", projectionMatrix);
            shader.SetMat4f("m_projection", squareVector[i]->transform.getTransformMatrix());
            shader.SetUniform4f("u_Color", squareVector[i]->color.x,
                squareVector[i]->color.y,
                squareVector[i]->color.z,
                squareVector[i]->color.w);

            renderer.Draw(vaSquare, ibSquare, shader);

        }
        for (int i = 0; i < particleVector.size(); i++)
        {
            //squareVector[i]->rigidBody->updatePhysics();
            shader.use();
            shader.SetMat4f("m_mvp", projectionMatrix);
            shader.SetMat4f("m_projection", particleVector[i]->transform.getTransformMatrix());
            shader.SetUniform4f("u_Color", particleVector[i]->color.x,
                particleVector[i]->color.y,
                particleVector[i]->color.z,
                particleVector[i]->color.w);

            renderer.Draw(vaParticle, ibParticle, shader);

        }
        processInput(window);
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

}

float scaleInNewRange(float OldMin, float OldMax, float NewMin, float NewMax, float OldValue) {

    float OldRange = (OldMax - OldMin);
    float NewRange = (NewMax - NewMin);
    float NewValue = (((OldValue - OldMin) * NewRange) / OldRange) + NewMin;

    return(NewValue);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (!pressedKey && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        std::cout << "pressed " << xpos << ", " << ypos << std::endl;
       
        Particle* newP = new Particle();
        

        newP->transform.setPosition(
            vec3(scaleInNewRange(0.0f, halfWindowsSize.x * 2.0f, -halfWindowsSize.x, halfWindowsSize.x, xpos), 
                scaleInNewRange(0.0f, halfWindowsSize.y * 2.0f, halfWindowsSize.y, -halfWindowsSize.y, ypos),
                0));

        particleVector.push_back(newP);
        pressedKey = true;
    }
    else if (pressedKey && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE)
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