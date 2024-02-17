#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Shader.h"
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "IndexBuffer.h"
#include "Renderer.h"
#include "Square.h"
#include "Particle.h"
#include "CollisionDetection.h"
#include "Utils.h"

#pragma region Shaders Variables
const char* vertexShaderPath = "src/vertex.shader";
const char* fragmentShaderPath = "src/fragment.shader";
#pragma endregion
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

std::vector<Shape*> shapeVector;

bool pressedKey = false;
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(halfWindowsSize.x * 2, halfWindowsSize.y * 2, "Collision 2D", NULL, NULL);
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

    CollisionDetection collisionDectection = CollisionDetection(vec2(halfWindowsSize), shapeVector);



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
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        collisionDectection.DetectCollision();
        renderer.Clear();
        for (int i = 0; i < shapeVector.size(); i++)
        {

            shapeVector[i]->rigidBody->updatePhysics(deltaTime);
            shader.use();
            shader.SetMat4f("m_mvp", projectionMatrix);
            shader.SetMat4f("m_projection", shapeVector[i]->transform.getTransformMatrix());
            shader.SetUniform4f("u_Color", shapeVector[i]->getColor().x,
                shapeVector[i]->getColor().y,
                shapeVector[i]->getColor().z,
                shapeVector[i]->getColor().w);

            if (shapeVector[i]->GetShapeType() == EShapeType::Quadrilateral)
            {
                renderer.Draw(vaSquare, ibSquare, shader);
            }
            else if (shapeVector[i]->GetShapeType() == EShapeType::Circle)
            {
                renderer.Draw(vaParticle, ibParticle, shader);
            }


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

bool isToSpawnSquare = false;
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (!pressedKey && glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {

        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        float xMousePosScreenSpace = scaleInNewRange(0.0f, halfWindowsSize.x * 2.0f, -halfWindowsSize.x, halfWindowsSize.x, xpos);
        float yMousePosScreenSpace = scaleInNewRange(0.0f, halfWindowsSize.y * 2.0f, halfWindowsSize.y, -halfWindowsSize.y, ypos);
        float zMousePosScreenSpace = 0;

        vec3 mousePosScreenSpace = vec3(xMousePosScreenSpace, yMousePosScreenSpace, zMousePosScreenSpace);

        bool isMouseOverShape = false;
        for (int i = 0; i < shapeVector.size(); i++)
        {
            if (isMouseOverShape) break;
            isMouseOverShape = shapeVector[i]->IsPositionInsideShape(mousePosScreenSpace);
            if (isMouseOverShape)
            {
                auto it = shapeVector.begin() + i;
                shapeVector.erase(it);
            }
        }

        if (isMouseOverShape)
        {
            std::cout << "MouseOverShape" << xpos << ", " << ypos << std::endl;
        }
        else
        {
            Shape* newP;
            if (isToSpawnSquare)
            {
                std::cout << "Square generated" << xpos << ", " << ypos << std::endl;
                newP = new Square();

            }
            else
            {
                std::cout << "Particle generated" << xpos << ", " << ypos << std::endl;
                newP = new Particle();

            }
            isToSpawnSquare = !isToSpawnSquare;

            newP->transform.setPosition(mousePosScreenSpace);

            shapeVector.push_back(newP);
        }
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