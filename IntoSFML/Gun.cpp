#include "Gun.h"
#include <iostream>
#include <algorithm>

#define fuck_around try
#define find_out catch

// https://www.youtube.com/watch?v=k6VIez6pnbc
// https://gamefromscratch.com/sfml-with-c-tutorial-series-windows-game-loops-and-timers/
// https://www.youtube.com/watch?v=HccMBtyXwFo

sf::Vector2f Normalize(sf::Vector2f a)
{
	float m = sqrt(a.x * a.x + a.y * a.y);
	sf::Vector2f normalizedVector;

	normalizedVector.x = a.x /= m;
	normalizedVector.y = a.y /= m;

	return normalizedVector;
}


bool AABB(sf::FloatRect a, sf::FloatRect b)
{
	if (a.left + a.width > b.left &&
		b.left + b.width > a.left &&
		b.top + b.height > a.top &&
		a.top + a.height > b.top)
	{
		return true;
	}
	return false;
}

void Gun::Update(const float &dt, const sf::Vector2f &player_position, const sf::Vector2f& mouse_position, MapManager &mapm, CollisionManager& collisionmanager)
{
	

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		
		if (this->GetAttackTimer())
		{
			Bullet* bullet = new Bullet(10, 0.5, Textures::ID::Wand_bullet);
			bullet->body.setSize(sf::Vector2f(5, 2.5));
			bullet->body.setPosition(player_position);
			bullet->objectType = bullet->type;
			m_bullets.push_back(bullet);
			collisionmanager.addObject(bullet);
			CreateBulletTarget(m_bullets.size() - 1, mouse_position);
		}

	}

	for (int i = 0; i < m_bullets.size(); i++)
	{
		sf::Vector2f bulletDirection = m_bullets[i]->target.getPosition() - m_bullets[i]->body.getPosition();
		bulletDirection = Normalize(bulletDirection);

		m_bullets[i]->body.setPosition(m_bullets[i]->body.getPosition() + bulletDirection * m_bullets[i]->speed);
	}


	for (size_t i = 0; i < m_bullets.size(); i++)
	{
		// StackOverflow code: 

		
		if (m_bullets[i]->target_reached) {
			m_bullets[i]->active = false;
			/*std::swap(m_bullets[i], m_bullets[m_bullets.size() - 1]); 
			m_bullets.pop_back(); */
			break; 
		}
		if (m_bullets[i]->GetBoundingBox().intersects(m_bullets[i]->target.getGlobalBounds())) {
			m_bullets[i]->active = false;
			/*std::swap(m_bullets[i], m_bullets[m_bullets.size() - 1]);
			m_bullets.pop_back();*/
			break; 
		}
	}

}

void Gun::CreateBulletTarget(const int& index, const sf::Vector2f& mousePos)
{
	sf::RectangleShape boundingRect;
	boundingRect.setSize(sf::Vector2f(20, 20));
	boundingRect.setFillColor(sf::Color::Transparent);
	boundingRect.setOutlineColor(sf::Color::Blue);
	boundingRect.setOutlineThickness(1);
	boundingRect.setPosition(sf::Vector2f(mousePos.x, mousePos.y));
	this->m_bullets[index]->target = boundingRect;
}

const bool Gun::GetAttackTimer()
{
	if (this->m_attacktimer.getElapsedTime().asMilliseconds() >= this->m_attacktimermax)
	{
		this->m_attacktimer.restart();
		return true; 
	}
	return false;
}

void Gun::Draw(sf::RenderWindow& window)
{
	for (const auto& bullet : m_bullets) { window.draw(bullet->body); }
	for (const auto& bullet : m_bullets) { window.draw(bullet->target); }
}
