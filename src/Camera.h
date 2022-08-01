#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

enum class Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const float YAW = 0.0f;
const float PITCH = 0.0f;
const float SPEED = 4.5f;
const float ZOOM = 75.0f;
const float RADIUS = 7.0f;

class Camera
{
public:
    // camera Attributes
    glm::vec3 Position;
    
    // euler Angles
    float Yaw;
    float Pitch;
    
    // camera options
    float MovementSpeed;
    float Zoom;
    float Radius;

    // constructor with vectors
    Camera(float yaw = YAW, float pitch = PITCH, float radius = RADIUS) : MovementSpeed(SPEED), Zoom(ZOOM)
    {
        Yaw = yaw;
        Pitch = pitch;
        Radius = radius;
        updateCameraPosition();
    }

    // returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix()
    {
        return glm::lookAt(Position, glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    }

    void updateCameraPosition()
    {
        if (Pitch > glm::radians(55.0f))
            Pitch = glm::radians(55.0f);
        if (Pitch < glm::radians(-55.0f))
            Pitch = glm::radians(-55.0f);
        Position.y = sin(Pitch) * Radius;
        Position.x = sin(Yaw) * cos(Pitch) * Radius;
        Position.z = cos(Yaw) * cos(Pitch) * Radius;
    };
    // processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        
        
        float velocity = MovementSpeed * deltaTime;
        if (direction == Camera_Movement::FORWARD)
        {
            Pitch += velocity;
            updateCameraPosition();
        }
        if (direction == Camera_Movement::BACKWARD)
        {
            Pitch -= velocity;
            updateCameraPosition();
        }
        if (direction == Camera_Movement::LEFT)
        {
            Yaw -= velocity;
            updateCameraPosition();
        }
        if (direction == Camera_Movement::RIGHT) {
            Yaw += velocity;
            updateCameraPosition();
        }
    }

    

    // processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        Zoom -= (float)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 75.0f)
            Zoom = 75.0f;
    }

};