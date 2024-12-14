#pragma once
#include "SFML/Graphics.hpp"
#include <map>
#include <string>


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
	};


}


template<typename Resource, typename Identifier>
class ResourceHolder
{
public: 
	void Load(Identifier ID, const std::string& filename)
	{
		std::unique_ptr<Resource> resource(new Resource());

		if (!resource->loadFromFile(filename)) {
			throw std::runtime_error("ResourceHolder::Load - Failed to Load " + filename); 
		}

		// graps the texture while still inserting it 
		auto inserted = m_ResourceMap.insert(std::make_pair(ID, std::move(resource)));
		_ASSERT(inserted.second); 
	}

	template<typename Parameter>
	void Load(Identifier ID, const std::string& filename, const Parameter& secondParam)
	{
		std::unique_ptr<Resource> resource(new Resource());

		if (!resource->loadFromFile(filename, secondParam)) {
			throw std::runtime_error("ResourceHolder::Load - Failed to Load " + filename);
		}

		// graps the texture while still inserting it 
		auto inserted = m_ResourceMap.insert(std::make_pair(ID, std::move(resource)));
		_ASSERT(inserted.second);
	}

	Resource& Get(Identifier ID)
	{
		auto found = m_ResourceMap.find(ID);
		_ASSERT(found != m_ResourceMap.end());

		return *found->second; 
	}

	const Resource& Get(Identifier ID) const
	{
		auto found = m_ResourceMap.find(ID);
		_ASSERT(found != m_ResourceMap.end());

		return *found->second;
	}


private: 
	std::map<Identifier, std::unique_ptr<Resource>> m_ResourceMap;

};

typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;

