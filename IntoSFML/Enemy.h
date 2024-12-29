#include "Common.h"

#define SPRITEUNIT 32
#define MOVEMENT 1

#define FORWARD 7
#define LEFTWARD 3
#define BACKWARD 1
#define RIGHTWARD 5

class Enemy : public GameObject, public Entity
{
public:

	Enemy(const Textures::ID tID, const Fonts::ID fID, const sf::Vector2f& InitalPosition, const sf::IntRect& TextureRect)
		: GameObject(tID, fID, InitalPosition, TextureRect)
	{
		SetupEntity("", 100, 10, 0.125 / 3, 500);
	}
	void mUpdate(const float& dt)
	{
		if (!m_health) { active = false; return; }

		m_text.setString(std::to_string(m_health));
		m_text.setPosition(m_position);


		Move(dt, GameData::Player::_PlayerPosition);
	}
	void Update() override
	{

	}
	void Draw(sf::RenderWindow& window) const noexcept override
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
			HandleCollision(other.GetPosition(), 20);
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
		}
	}
	
private:
	// Movement/shooting Calculations
	sf::Vector2f NormalizeVector(sf::Vector2f& input) const
	{
		float m = sqrt(input.x * input.x + input.y * input.y);
		sf::Vector2f normalizedVector;

		normalizedVector.x = input.x /= m;
		normalizedVector.y = input.y /= m;

		return normalizedVector;
	}
	sf::Vector2f GetDirectionVector() const
	{
		sf::Vector2f direction;
		direction = m_target - m_position;
		direction = NormalizeVector(direction);

		return direction;
	}
	sf::Vector2f GetDirectionVector(const sf::Vector2f& target) const
	{
		sf::Vector2f direction;
		direction = target - m_position;
		direction = NormalizeVector(direction);

		return direction;
	}
	sf::Vector2f GetClosestTarget(const sf::Vector2f& firstTarget, const sf::Vector2f& secondTarget) const
	{
		float diff_first = std::abs(firstTarget.x - this->m_position.x);
		diff_first += std::abs(firstTarget.y - this->m_position.y);

		float diff_second = std::abs(secondTarget.x - this->m_position.x);
		diff_second += std::abs(secondTarget.y - this->m_position.y);

		if (diff_first < diff_second)
		{
			return this->GetDirectionVector(firstTarget);
		}

		return this->GetDirectionVector(secondTarget);
	}

	void Move(const float& dt, const sf::Vector2f& playerPosition)
	{
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
	sf::Text m_text; 

private: 
	//quickfix
	int     movementindicator = 0;
};