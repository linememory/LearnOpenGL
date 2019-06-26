#ifndef CAMERA_H
#define CAMERA_H

#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const float YAW       = 0.0f;
const float PITCH     =  0.0f;
const float FOV      =  45.0f;


class Camera{
private:
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_world_up;
    float m_yaw;
    float m_pitch;
    float m_fov;
    void updateCameraVectors();
public:
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);
    void setPosition(glm::vec3 position);
    void translate(glm::vec3 position);
    void rotate(glm::vec3 front);
    void rotate(float pitchOffset, float yawOffset, bool constrainPitch = true);
    void setFOV(float fov);
    void zoom(float amount);
    glm::vec3 getPosition();
    glm::mat4 getViewMatrix();
    glm::mat4 getProjectionMatrix(float aspectRation);
};


#endif
