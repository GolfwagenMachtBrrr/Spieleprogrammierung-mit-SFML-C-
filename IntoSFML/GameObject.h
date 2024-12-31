#pragma once 
#include "Common.h"
#include "nRessources.h"

#include "Entity.h"
#include <iostream>

// enabled sollte verwendet werden um zu überprüfen
// ob z.b ein zombie bereits wieder angreifen kann. 
// Sollte dann in enemy->Update() aktualisiert werden. 

class GameObject : public Entity
{
public:
	virtual void OnCollision(GameObject& other) = 0;

	GameObject(){}
protected:

	GameObject(const Textures::ID tID, const sf::Vector2f& InitialPosition)
		: m_tID(tID), m_position(InitialPosition), active(true), enabled(true)
	{
		m_sprite.setTexture(Textures::_TextureHolder.Get(m_tID));
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
		m_sprite.setPosition(InitialPosition);
	}

	GameObject(const Textures::ID tID, const Fonts::ID fID, const sf::Vector2f& InitialPosition)
		: m_tID(tID), m_fID(fID), m_position(InitialPosition), active(true), enabled(true)
	{
		m_sprite.setTexture(Textures::_TextureHolder.Get(m_tID));
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
		m_sprite.setPosition(InitialPosition); 

		m_text.setFont(Fonts::_FontHolder.Get(m_fID));
	}

	GameObject(const Textures::ID tID, const Fonts::ID fID, const sf::Vector2f& InitialPosition, const sf::IntRect& TextureRect) // Wenn TexRect benötigt
		: m_tID(tID), m_fID(fID), m_position(InitialPosition), active(true), enabled(true)
	{
		m_sprite.setTexture(Textures::_TextureHolder.Get(m_tID));
		m_sprite.setTextureRect(TextureRect);
		m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
		m_sprite.setPosition(InitialPosition);

		m_text.setFont(Fonts::_FontHolder.Get(m_fID));
	}

	void HandleCollision(const sf::Vector2f objectposition, float force) {
		sf::Vector2f direction = m_position - objectposition;
		float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
		if (length > 0) {
			direction /= length; 
			m_position += direction * force;
		}
	}

protected:
	sf::Sprite		       m_sprite;
	sf::Text		       m_text;
	std::vector<sf::Sound> m_sounds; 

	Textures::ID			m_tID;
	Fonts::ID				m_fID; 
	std::vector<Sounds::ID> m_sID; 

	sf::Vector2f     m_position; 
	int				 m_colliderReference; 

public:
	bool			 active;
	bool			 enabled;

public: 
	//Getter
	sf::FloatRect GetBoundingBox() const noexcept { return m_sprite.getGlobalBounds(); }
	sf::Vector2f GetPosition() const noexcept { return m_sprite.getPosition(); }
	int GetObjectTextureID() const noexcept { return m_tID; }
	int GetColliderReference() const noexcept { return m_colliderReference; }

	//Setter
	void SetPosition(const sf::Vector2f& position) { m_sprite.setPosition(position); m_position = position; }
	void SetColliderReference(int refID) { m_colliderReference = refID; }
};