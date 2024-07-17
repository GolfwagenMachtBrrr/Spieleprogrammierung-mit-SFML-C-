#pragma once
#include <SFML/Graphics.hpp>

class Camera : sf::Drawable
{
public:

	void Initialize();
	void Update(const float& deltaTime);

	sf::Vector2f GetPosition();
	void SetPosition(float posX, float posY);

	Camera(float speed)
		: m_cameraSpeed(speed)
	{}

private:

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const
	{
		target.draw(m_body, states);
	}

	sf::Vector2f m_position;
	sf::RectangleShape m_body;
	
	float m_cameraSpeed;
};

