#pragma once
#include <memory>
#include "Resource.h"
#include <vector>

class ResourceManager
{
public:
	// define an enum to allow us to specify what type of resource we want
	// to get from the Resource Manager
	enum ResourceType {
		TEXTURE = 0,
		FONT,
		AUDIO
	};
	std::vector< std::shared_ptr<ResourceBase> > m_resources;
	// keep the constructor, copy constructor and assignment allocator private
	ResourceManager() {};
	ResourceManager(const ResourceManager&) {};
	ResourceManager& operator=(const ResourceManager&) {};
public:
	static ResourceManager& getInstance();
	~ResourceManager() {};
	std::shared_ptr<ResourceBase> get(const std::string filename,
		ResourceType type);
	void collectGarbage();
	int getCount();
};