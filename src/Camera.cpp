#include "Camera.h"
#include <GLFW/glfw3.h>


Camera::Camera(glm::vec3 position, glm::vec3 up, float yaw, float pitch):
    m_position(position),
    m_front(glm::vec3(0.0f, 0.0f, -1.0f)), 
    m_world_up(up),
    m_fov(FOV) {
    updateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch) :
    Camera(glm::vec3(posX, posY, posZ), glm::vec3(upX, upY, upZ), yaw, pitch){
        
}

void Camera::setPosition(glm::vec3 position){
    m_position = position;
}

void Camera::translate(glm::vec3 position){
    m_position += position.x * m_front;
    m_position += position.y * glm::normalize(glm::cross(m_front, m_up));
    m_position += position.z * m_up;
}

void Camera::rotate(float pitchOffset, float yawOffset, bool constrainPitch){
    m_yaw += yawOffset;
    m_pitch += pitchOffset;

    if (constrainPitch){
        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;
    }
    updateCameraVectors();
}

void Camera::setFOV(float fov){
    if (fov < 1.0f) {
        m_fov = 1.0f;
    } else if (fov > 179.0f) {
        m_fov = 179.0f;
    } else {
        m_fov = fov;
    }
}

void Camera::zoom(float amount){
    float max = 179.0f;
    if (m_fov >= 1.0f && m_fov <= max){
        m_fov -= amount;
    }
    if (m_fov < 1.0f)
        m_fov = 1.0f;
    if (m_fov > max)
        m_fov = max;
}

glm::vec3 Camera::getPosition(){
    return m_position;
}

glm::vec3 Camera::getViewDirection(){
    return m_front;
}

glm::mat4 Camera::getViewMatrix(){
    return glm::lookAt(m_position, m_position + m_front, m_up);
}

glm::mat4 Camera::getProjectionMatrix(float aspectRation){
    return glm::perspective(glm::radians(m_fov), aspectRation, 0.1f, 100.0f);
}

void Camera::updateCameraVectors(){
    glm::vec3 front;
    front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	m_front = (glm::normalize(front));
    m_right = glm::normalize(glm::cross(m_front, m_world_up));
    m_up = glm::normalize(glm::cross(m_right, m_front));
}
