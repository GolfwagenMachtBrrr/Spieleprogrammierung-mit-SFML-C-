#include "Camera.h"
#include <iostream>

#define SPEED 0.125f

void Camera::Initialize()
{
	m_body = sf::RectangleShape(sf::Vector2f(10, 10));
	m_body.setPosition(sf::Vector2f(0, 0));
}

void Camera::Update(const float &deltatime)
{
	m_position = m_body.getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_body.setPosition(m_position + sf::Vector2f(0, -1) * m_cameraSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_body.setPosition(m_position + sf::Vector2f(0, 1) * m_cameraSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_body.setPosition(m_position + sf::Vector2f(1, 0) * m_cameraSpeed);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_body.setPosition(m_position + sf::Vector2f(-1, 0) * m_cameraSpeed);
	}
}

sf::Vector2f Camera::GetPosition()
{
	return m_position;
}

void Camera::SetPosition(float posX, float posY)
{
	m_body.setPosition(sf::Vector2f(posX, posY));
}
