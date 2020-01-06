#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
	FORWARD,
	BACKWARD,
	LEFT,
	RIGHT
};


const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

using namespace glm;
class Camera
{
public:
	vec3 Position;
	vec3 Up;
	vec3 Right;
	vec3 Forward;
	vec3 WorldUp;

	float Yaw;
	float Pitch;

	float MovementSpeed;
	float MouseSensitivity;
	float Zoom;

	Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), vec3 forward =glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3 worldUp = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH) :  MovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM)
	{
		Position = position;
		Forward = forward;
		WorldUp = worldUp;
		Yaw = yaw;
		Pitch = pitch;
		updateCameraVectors();
	}

	mat4 LookAt()
	{
		return lookAt(Position, Position + Forward, Up);
	}

	void ProcessKeyboard(Camera_Movement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		if (direction == FORWARD)
			Position += Forward * velocity;
		if (direction == BACKWARD)
			Position -= Forward * velocity;
		if (direction == LEFT)
			Position -= Right * velocity;
		if (direction == RIGHT)
			Position += Right * velocity;

	}

	void ProcessMouse(int xOffset, int yOffset, bool constrainPitch = true)
	{
		xOffset *= MouseSensitivity;
		yOffset *= MouseSensitivity;

		Yaw += xOffset;
		Pitch += yOffset;

		if (Pitch < -70.0f)
			Pitch = -70.0f;
		if (Pitch > 70.0f)
			Pitch = 70.0f;

		if (Yaw >= 360)
			Yaw -= 360;
		if (Yaw <= -360)
			Yaw += 360;
		cout << Yaw << " " << Pitch << endl;
		updateCameraVectors();
	}
	void ProcessMouseScroll(float yoffset)
	{
		if (Zoom >= 1.0f && Zoom <= 45.0f)
			Zoom -= yoffset;
		if (Zoom <= 1.0f)
			Zoom = 1.0f;
		if (Zoom >= 45.0f)
			Zoom = 45.0f;
	}
private:
	void updateCameraVectors()
	{
		vec3 front;
		front.x = cos(radians(Yaw)) * cos(radians(Pitch));
		front.y = sin(radians(Pitch));
		front.z = sin(radians(Yaw)) * cos(radians(Pitch));
		Forward = normalize(front);

		Right = cross(Forward, WorldUp);
		Up = cross(Right, Forward);
	}
};

#endif // !CAMERA_H
