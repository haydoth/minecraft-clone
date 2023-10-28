#pragma once

#include <ext.hpp>
#include <iostream>

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class camera
{
public:

    struct camera_data {
        glm::mat4 view_matrix;
        glm::mat4 projection_matrix;

        glm::vec3 position;
    };


    // constructor with vectors
    camera(
        glm::mat4 projection = 
        glm::lookAt(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0)),
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW, float pitch = PITCH) : m_front(glm::vec3(0.0f, 0.0f, -1.0f))
    {
        m_position = position;
        m_world_up = up;
        m_yaw = yaw;
        m_pitch = pitch;
        update_camera_vectors();

        m_data = camera_data();
        m_data.view_matrix = glm::mat4(1);
        m_data.projection_matrix = projection;
    }

    camera_data get_data()
    {
        m_data.view_matrix = glm::lookAt(m_position, m_position + m_front, m_up);
        m_data.position = m_position;
        return m_data;
    }

    void move(glm::vec3 input, float speed, float deltaTime)
    {
        glm::vec3 velocity = (input.z * m_front + input.x * m_right);
        velocity.y += input.y;
        velocity *= speed * deltaTime;
        
        m_position += velocity;
    }

    void rotate(glm::vec2 input, float sensitivity)
    {
        input.x *= sensitivity;
        input.y *= sensitivity;

        m_yaw += input.x;
        m_pitch += input.y;

        if (m_pitch > 89.0f)
            m_pitch = 89.0f;
        if (m_pitch < -89.0f)
            m_pitch = -89.0f;

        // update Front, Right and Up Vectors using the updated Euler angles
        update_camera_vectors();
    }

    bool on_mouse_moved_event()
    {

    }

private:
    // calculates the front vector from the Camera's (updated) Euler Angles
    void update_camera_vectors()
    {
        // calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        front.y = sin(glm::radians(m_pitch));
        front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
        m_front = glm::normalize(front);
        // also re-calculate the Right and Up vector
        m_right = glm::normalize(glm::cross(m_front, m_world_up));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
        m_up = glm::normalize(glm::cross(m_right, m_front));
    }
    camera_data m_data;

    // camera Attributes
    glm::vec3 m_position;
    glm::vec3 m_front;
    glm::vec3 m_up;
    glm::vec3 m_right;
    glm::vec3 m_world_up;
    // euler Angles
    float m_yaw;
    float m_pitch;
};