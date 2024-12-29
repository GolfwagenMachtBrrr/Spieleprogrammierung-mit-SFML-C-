#pragma once
#include <string>
#include <iostream>


// Chat GPT hat hier bei der Formatierung gehholden, 
// sowie noexcept & (x >= 0) ? x : 0 hinzugefügt


struct Entity
{
public:
    void SetHealth(int x) noexcept { m_health = (x >= 0) ? x : 0; }
    void SetDamage(int x) noexcept { m_damage = (x >= 0) ? x : 0; }
    void SetSpeed(float x) noexcept { m_speed = (x >= 0) ? x : 0.0f; }
    void SetAttackSpeed(int x) noexcept { m_attackspeed = (x >= 0) ? x : 0; }

    int GetHealth() const noexcept { return m_health; }
    int GetDamage() const noexcept { return m_damage; }
    float GetSpeed() const noexcept { return m_speed; }
    int GetAttackSpeed() const noexcept { return m_attackspeed; }

    // Util
    void PrintEntityStats()
    {
        std::cout << "Name: " << m_name << std::endl;
        std::cout << "..................................." << std::endl; 
        std::cout << "health: " << m_health << std::endl;
        std::cout << "Damage: " << m_damage << std::endl;
        std::cout << "Speed: " << m_speed << std::endl;
        std::cout << "Attackspeed: " << m_attackspeed << std::endl;
        std::cout << "..................................." << std::endl;
    }

    void SetupEntity(std::string name, int health, int damage, float speed, int attackspeed) // NULL if unspecified
    {
        m_name = name;
        m_health = (health >= 0) ? health : -1; 
        m_damage = (damage >= 0) ? damage : -1; 
        m_speed = (speed >= 0) ? speed : -1;; 
        m_attackspeed = (attackspeed >= 0) ? attackspeed : -1;

        // TODO: Alle Parameter durch einen ID Parameter ersetzten, anschließend die richtige txt datei finden und werte so befüllen. 
    }



protected: 
    std::string      m_name = "";
	int			     m_health = -1;
	int			     m_damage = -1;
	float		     m_speed  = -1;
	int				 m_attackspeed = -1; 
};

