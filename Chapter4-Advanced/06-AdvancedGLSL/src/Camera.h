#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>

#include <vector>

enum Camera_Movement
{
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class Camera
{
public:
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

private:
	double last_xpos;
	double last_ypos;
	double deltaX;
	double deltaY;
	bool first_time = true;

public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f) :
		Position(position),
		WorldUp(up),
		Yaw(yaw),
		Pitch(pitch),
		Front(glm::vec3(0.0f, 0.0f, -1.0f)),
		MovementSpeed(2.5f),
		MouseSensitivity(0.1f),
		Zoom(45.0f)
	{
		updateCameraVectors();
	}

	inline void Initialize(){first_time = true;}

	void OnMouseMove(double xpos, double ypos)
	{
		if (first_time)
		{
			last_xpos = xpos;
			last_ypos = ypos;
			first_time = false;
		}

		double deltaX = xpos - last_xpos;
		double deltaY = ypos - last_ypos;
		last_xpos = xpos;
		last_ypos = ypos;

		deltaX *= MouseSensitivity;
		deltaY *= MouseSensitivity;

		Yaw += (float)deltaX;
		Pitch -= (float)deltaY;

		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;

		updateCameraVectors();
	}

	void OnKeyboard(float deltaTime, Camera_Movement movement)
	{
		switch (movement)
		{
		case Camera_Movement::FORWARD:
			Position += Front * deltaTime * MovementSpeed;
			break;
		case Camera_Movement::BACKWARD:
			Position -= Front * deltaTime * MovementSpeed;
			break;
		case Camera_Movement::LEFT:
			Position -= Right * deltaTime * MovementSpeed;
			break;
		case Camera_Movement::RIGHT:
			Position += Right * deltaTime * MovementSpeed;
			break;
		case Camera_Movement::UP:
			Position += Up * deltaTime * MovementSpeed;
			break;
		case Camera_Movement::DOWN:
			Position -= Up * deltaTime * MovementSpeed;
			break;
		default:
			break;
		}
	}

	void OnScroll(double scrollValue)
	{
		Zoom -= (float)scrollValue;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}

	glm::mat4 GetViewMatrix()
	{
		return glm::lookAt(Position, Position + Front, Up);
	}

private:
	void updateCameraVectors()
	{
		glm::vec3 front;
		front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		front.y = sin(glm::radians(Pitch));
		front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		Front = glm::normalize(front);


		Right = glm::normalize(glm::cross(Front, WorldUp));
		Up = glm::normalize(glm::cross(Right, Front));
	}
};

#endif