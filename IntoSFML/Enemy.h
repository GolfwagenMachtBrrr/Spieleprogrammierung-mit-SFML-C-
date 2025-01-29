#include "Common.h"
#include "nUtility.h"

#define SPRITEUNIT 32
#define MOVEMENT 1

#define FORWARD 7
#define LEFTWARD 3
#define BACKWARD 1
#define RIGHTWARD 5

#include <string>

#define lerrmsg std::cout << "I`m at Enemy->OnCollision()" << std::endl; 

class Enemy : public GameObject
{
public:

	Enemy(const Textures::ID tID, const Fonts::ID fID, const sf::Vector2f& InitalPosition, const sf::IntRect& TextureRect)
		: GameObject(tID, fID, InitalPosition, TextureRect)
	{
		SetupEntity("", 100, 10, 0.125 / 3, 500);
	}
	void Update()
	{
		if (!m_health) { active = false; return; }

		m_text.setString(std::to_string(m_health));
		m_text.setPosition(m_position);


		Move(GameData::Player::_PlayerPosition);
	}
	
	void Draw(sf::RenderWindow& window) const noexcept 
	{
		if (GameData::Player::ValidateRendering(m_sprite))
		{
			window.draw(m_sprite);
			window.draw(m_text);
		}
	}
	void OnCollision(GameObject& other) override
	{
		switch (other.GetObjectTextureID())
		{
		case Textures::ID::Zombie:
			HandleCollision(other.GetPosition(), 5);
			break;
		case Textures::ID::House:
			HandleCollision(other.GetPosition(), 5);
			break;
		case Textures::ID::Spawner:
			HandleCollision(other.GetPosition(), 5);
			break;

		case Textures::ID::Wand_bullet:

			if (other.enabled)
			{
				m_health -= 10;
				other.enabled = false;
			}
			break;

		case Textures::ID::Player:
			if (other.enabled)
			{
				other.enabled = false; 
				other.SetHealth(other.GetHealth() - m_damage); 
			}
		}
	}
	
private:
	// Movement/shooting Calculations
	sf::Vector2f GetDirectionVector(const sf::Vector2f& target) const
	{
		sf::Vector2f direction;
		direction = target - m_position;
		direction = Utility::Normalize(direction);

		return direction;
	}

	void Move(const sf::Vector2f& playerPosition)
	{
		float dt = GameData::_DeltaTime; 
		sf::Vector2f direction; direction = this->GetDirectionVector(playerPosition);
		sf::Vector2f hypotheticalPosition = m_position + direction * dt * m_speed;


		if (hypotheticalPosition.x < 0 || hypotheticalPosition.y < 0) {
			direction.x = 0;
			direction.y = 0;
			hypotheticalPosition = m_position + direction * dt * m_speed;
		}

		//AdjustTileMap(map, hypotheticalPosition); 
		this->m_sprite.setPosition(hypotheticalPosition);
		this->m_position = this->m_sprite.getPosition();

		//impl enemy animations 
		this->WalkAnimation(direction, dt);
	}
	void WalkAnimation(const sf::Vector2f& direction, const float& deltatime)
	{
		if (direction.x == 0 && direction.y == 0) {
			return;
		}

		if (direction.x > 0 && direction.y < 0) {
			m_sprite.setTextureRect(sf::IntRect((movementindicator / MOVEMENT) * SPRITEUNIT, FORWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			movementindicator++;
			if (movementindicator / MOVEMENT == 3) {
				movementindicator = 0;
			}
		}

		else if (direction.x > 0 && direction.y > 0 && direction.x < direction.y) {

			m_sprite.setTextureRect(sf::IntRect((movementindicator / MOVEMENT) * SPRITEUNIT, BACKWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			movementindicator++;
			if (movementindicator / MOVEMENT == 3) {
				movementindicator = 0;
			}
		}

		else if (direction.x < 0 && direction.y > 0) {

			m_sprite.setTextureRect(sf::IntRect((movementindicator / MOVEMENT) * SPRITEUNIT, LEFTWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			movementindicator++;
			if (movementindicator / MOVEMENT == 3) {
				movementindicator = 0;
			}
		}

		else if (direction.x > 0 && direction.y > 0 && direction.x > direction.y) {

			m_sprite.setTextureRect(sf::IntRect((movementindicator / MOVEMENT) * SPRITEUNIT, RIGHTWARD * SPRITEUNIT, SPRITEUNIT, SPRITEUNIT));
			movementindicator++;
			if (movementindicator / MOVEMENT == 3) {
				movementindicator = 0;
			}
		}


	}

private:
	sf::Vector2f m_target; 

private: 
	//quickfix
	int     movementindicator = 0;
};