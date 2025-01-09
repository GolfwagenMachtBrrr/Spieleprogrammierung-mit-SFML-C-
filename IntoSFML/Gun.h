#include "Common.h"
#include "Bullet.h"
#include "nRessources.h"
#include "nGameData.h"
#include "nCollision.h"
#include "nUtility.h"

// https://www.youtube.com/watch?v=k6VIez6pnbc
// https://gamefromscratch.com/sfml-with-c-tutorial-series-windows-game-loops-and-timers/
// https://www.youtube.com/watch?v=HccMBtyXwFo



class Gun : public Item
{
public:

	Gun(){}

	Gun(const Textures::ID tID, const Fonts::ID fID, const sf::Vector2f Initialposition)
		: Item(tID, fID, Initialposition)
	{
	}
	void Update()
	{
		Shoot(GameData::Player::_PlayerPosition, GameData::Views::_GameMousePosition);
		CalculatingBullets(GameData::_DeltaTime);
	}
	
	void Draw(sf::RenderWindow& window) const noexcept 
	{
		for (const auto& bullet : m_bullets) {
			bullet->Draw(window);
		}
	}

private:
	void Shoot(const sf::Vector2f& player_position, const sf::Vector2f& mouse_position)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {

			if (thetimehascome())
			{
				errmsg;
				float angle = Utility::CalculateAngleInDegrees(player_position, mouse_position) * -1;
				std::shared_ptr<Bullet> bullet = std::make_shared<Bullet>(Textures::ID::Wand_bullet, player_position, angle);

				m_bullets.push_back(bullet);
				Collisions::_CollisionManager.addObject(bullet);

				CreateBulletTarget(m_bullets.size() - 1, mouse_position);
			}

		}
	}
	void CalculatingBullets(float dt)
	{
		for (int i = 0; i < m_bullets.size(); i++)
		{
			sf::Vector2f bulletDirection = m_bullets[i]->GetTarget() - m_bullets[i]->GetPosition();
			bulletDirection = Utility::Normalize(bulletDirection);
			m_bullets[i]->SetPosition(m_bullets[i]->GetPosition() + bulletDirection * m_bullets[i]->GetSpeed());
		}


		for (size_t i = 0; i < m_bullets.size(); i++)
		{
			if (m_bullets[i]->active && !m_bullets[i]->enabled) {
				m_bullets[i]->active = false;
				std::swap(m_bullets[i], m_bullets[m_bullets.size() - 1]);
				m_bullets.pop_back();
				break;
			}
			if (m_bullets[i]->GetBoundingBox().contains(m_bullets[i]->GetTarget())) {
				m_bullets[i]->active = false;
				std::swap(m_bullets[i], m_bullets[m_bullets.size() - 1]);
				m_bullets.pop_back();
				break;
			}
		}
	}
	void CreateBulletTarget(const int& index, const sf::Vector2f& mouse_position)
	{

		sf::RectangleShape boundingRect;
		boundingRect.setOrigin(boundingRect.getLocalBounds().width / 2, boundingRect.getLocalBounds().height / 2);
		boundingRect.setPosition(sf::Vector2f(mouse_position.x, mouse_position.y));


		m_bullets[index]->SetTarget(boundingRect.getGlobalBounds().getPosition());

	}

	bool thetimehascome()
	{
		if (m_clock.getElapsedTime().asMilliseconds() >= duration) {
			m_clock.restart(); 
			return true;
		}
		return false; 
	}
	
	
private: 
	std::vector<std::shared_ptr<Bullet>> m_bullets; 
	sf::Clock m_clock; 
	int duration = 300; 

private: 
	sf::Vector2f player_position, mouse_position; 
	float deltatime; 
};
