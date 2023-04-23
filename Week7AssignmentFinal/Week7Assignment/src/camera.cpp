/*
* Author: Chris Trimmer
* Assignment: Week 7 (Final Project)
* Date: 04/14/2023
*
* References:
* Ideas, structure, and support from the following sources:
*   http://www.opengl-tutorial.org/beginners-tutorials/
*   https://www.khronos.org/opengl/wiki/Getting_Started#Tutorials_and_How_To_Guides
*   https://learnopengl.com/Introduction
*   https://www.youtube.com/@snhucomputerscience
*	https://www.songho.ca/opengl/gl_cylinder.html
*/


#include <camera.h>


Camera::Camera(int w, int h, glm::vec3 initialPosition, bool isPerspective) :
    isPerspective{isPerspective}, position{initialPosition}, lookDirection {0.f, 0.f, 1.f},
    width{w}, height{h}
//Camera::Camera(int w, int h, glm::vec3 initialPosition, bool isPerspective) :
//    isPerspective{ isPerspective }, position{ initialPosition }, 
//    lookDirection{ -1.f * initialPosition },
//    width{ w }, height{ h }
{
    recalculateVectors();
}



void Camera::MoveCamera(MoveDirection direction, float moveAmount)
{  
    glm::vec3 moveDirection{};

    switch (direction) {
        case MoveDirection::FORWARD: {
            moveDirection = this->lookDirection;
            break;
        }
        case MoveDirection::BACKWARD: {
            moveDirection = -(this->lookDirection);
            break;
        }
        case MoveDirection::LEFT: {
            moveDirection = (glm::normalize(glm::cross(this->lookDirection, this->upDirection)));
            break;
        }
        case MoveDirection::RIGHT: {
            moveDirection = -(glm::normalize(glm::cross(this->lookDirection, this->upDirection)));
            break;
        }
        case MoveDirection::UP: {
            moveDirection = (glm::normalize(glm::cross(this->lookDirection, this->rightDirection)));
            break;
        }
        case MoveDirection::DOWN: {
            moveDirection = -(glm::normalize(glm::cross(this->lookDirection, this->rightDirection)));
            break;
        }
        default: {
            break;
        }
    }

    this->position += moveDirection * moveAmount;
}

void Camera::RotateBy(float yaw, float pitch)
{
    this->yaw += yaw;
    this->pitch += pitch;

    this->pitch = std::clamp(this->pitch, -89.f, 89.f);

    recalculateVectors();
}

void Camera::recalculateVectors()
{
    this->lookDirection = glm::normalize(
        glm::vec3{
            std::cos(glm::radians(this->yaw)) * std::cos(glm::radians(this->pitch)),    // x
            std::sin(glm::radians(this->pitch)),                                        // y
            std::sin(glm::radians(this->yaw)) * std::cos(glm::radians(this->pitch))     // z
        }
    );
                                                                            // world up
    glm::vec3 rightDirection = glm::normalize(glm::cross(this->lookDirection, glm::vec3(0.f, 1.f, 0.f)));
    this->upDirection = glm::normalize(glm::cross(rightDirection, this->lookDirection));

}

void Camera::IncrementZoom(float amount)
{
    this->fov -= amount;

    this->fov = std::clamp(this->fov, 1.f, 75.f);
}

glm::mat4 Camera::GetViewMatrix()
{
    return 

        // eye (x value = turn camera left/right, y value = tilt up or down, z = higher value move closer
        glm::lookAt(this->position,
            this->position + this->lookDirection, // center
            this->upDirection);  // up = positive y

}

glm::mat4 Camera::GetProjectionMatrix() const
{
    auto aspectRatio = (float)this->width / (float)this->height;

    if (this->isPerspective) {
        return glm::perspective(glm::radians(this->fov), aspectRatio,
            this->nearClip, this->farClip);
    }


    return glm::ortho(-aspectRatio, aspectRatio, -1.f, 1.f, this->nearClip, this->farClip);

}

