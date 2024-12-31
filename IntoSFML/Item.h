#pragma once


struct Item : public GameObject
{
	Item(){}

	Item(Textures::ID tID, Fonts::ID fID, const sf::Vector2f& InitialPosition) : GameObject(tID, fID, InitialPosition)
	{
		m_sprite.setScale(sf::Vector2f(4, 4));
	}


	void Draw(sf::RenderWindow& windows) const noexcept
	{
		if (!active) { return; }
		windows.draw(m_sprite); 
	}


	void OnCollision(GameObject& other) override {}

public:
	bool interactive = false; // Wird im inventar angezeigt ist aber nicht benutzbar 
};

namespace Items
{
	enum Weapons
	{
		Crossbow, 
		Sword,
		Shield,
	};

	enum Consumables
	{
		Cake, 
		Schwammerl,
		Gulasch,
	};

}