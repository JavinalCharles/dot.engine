#pragma once

#include "dot/ResourceAllocator.hpp"

namespace dot
{

struct TileInfo
{
	TileInfo()
		: tileID(0)
	{

	}

	TileInfo(unsigned textureID, unsigned tileID, sf::IntRect textureRect)
		: textureID(textureID),
		tileID(tileID),
		textureRect(textureRect)
	{

	}

	int tileID;
	int textureID;
	sf::IntRect textureRect;
};

struct Tile
{
	std::shared_ptr<TileInfo> properties;
	int x;
	int y;
};

}; // namespace dot