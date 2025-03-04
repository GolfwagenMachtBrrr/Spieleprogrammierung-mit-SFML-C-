#pragma once
#include "nRessources.h"
#include "ResourceHolder.h"
#define errmsg std::cout << "Here " << std::endl
namespace Textures
{
	enum ID
	{
		Undefined = -1,
		Spawner,
		Cursor,
		Skeleton,
		Grass,
		Zombie,
		Wand,
		Wand_bullet,
		Sword,
		House,
		Bandit,
		Player,
		BloodScreen,
		DeathScreen,
	};

	static ResourceHolder<sf::Texture, Textures::ID> _TextureHolder;
}

namespace Sounds
{
	enum ID
	{
		SoundtrackGame,
		SoundtrackMenue,
		SoundGun,
		SoundZombie,
		SoundPlayerDeath,
	};

	static ResourceHolder <sf::SoundBuffer, Sounds::ID> _SoundHolder;
}

namespace Fonts
{
	enum ID
	{
		OnlyFont,
	};

	static ResourceHolder<sf::Font, Fonts::ID> _FontHolder; 
}