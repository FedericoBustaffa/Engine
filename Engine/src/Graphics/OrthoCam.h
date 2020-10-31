#pragma once

#include <glm/glm.hpp>

class OrthoCam
{
public:
	OrthoCam(double left, double right, double bottom, double top);

	const glm::mat4& GetViewMatrix() const;
	const glm::mat4& GetProjectionMatrix() const;
	const glm::mat4& GetViewProjectionMatrix() const;

	void SetPosition(const glm::vec3& position);
	const glm::vec3& GetPosition() const;

	void SetRotation(float rotation);
	float GetRotation() const;

private:
	void RecalculateViewMatrix();

private:
	glm::mat4 view, projection, view_projection;

	glm::vec3 position;
	float rotation = 0.0f;
};