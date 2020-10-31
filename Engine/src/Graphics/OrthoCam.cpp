#include "OrthoCam.h"

#include <glm/gtc/matrix_transform.hpp>

OrthoCam::OrthoCam(double left, double right, double bottom, double top)
	: view(1.0f),
	projection(1.0f),
	view_projection(glm::ortho(left, right, bottom, top)),
	position(0.0f)
{
	view_projection = projection * view;
}

const glm::mat4& OrthoCam::GetViewMatrix() const
{
	return view;
}

const glm::mat4& OrthoCam::GetProjectionMatrix() const
{
	return projection;
}

const glm::mat4& OrthoCam::GetViewProjectionMatrix() const
{
	return view_projection;
}

void OrthoCam::SetPosition(const glm::vec3& position)
{
	this->position = position;
	RecalculateViewMatrix();
}

const glm::vec3& OrthoCam::GetPosition() const
{
	return position;
}

void OrthoCam::SetRotation(float rotation)
{
	this->rotation = rotation;
	RecalculateViewMatrix();
}

float OrthoCam::GetRotation() const
{
	return rotation;
}

// private method
void OrthoCam::RecalculateViewMatrix()
{
	glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) *
		glm::rotate(transform, rotation, glm::vec3(0, 0, 1));

	view = glm::inverse(transform);
	view_projection = projection * view;
}