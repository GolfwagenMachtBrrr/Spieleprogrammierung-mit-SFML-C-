#include "Common.h"

struct Bullet : public GameObject, public Entity 
{
	Bullet(Textures::ID ID, const sf::Vector2f InitialPosition, float newRotation) : GameObject(ID, InitialPosition)
	{
		SetupEntity("Bullet", NULL, 10, 0.125/2, NULL); 

		GameObject::m_sprite.setPosition(InitialPosition); 
		GameObject::m_sprite.setOrigin(GameObject::m_sprite.getLocalBounds().width / 2, 0);
		GameObject::m_sprite.setRotation(-90);
		GameObject::m_sprite.rotate(newRotation);

	}

	void Update() override
	{

	}

	void Draw(sf::RenderWindow& window) const noexcept override{
		window.draw(m_sprite);
	}

	void OnCollision(GameObject& other) override
	{
		switch (other.GetObjectTextureID())
		{
		case Textures::ID::Player:
			break; 

		default: 
			enabled = false;
			break; 
		}
	}

private: 
	sf::Vector2f m_target; 
public: 
	void		 SetTarget(const sf::Vector2f& target) { m_target = target; }
	sf::Vector2f GetTarget() const noexcept            { return m_target; }
};

