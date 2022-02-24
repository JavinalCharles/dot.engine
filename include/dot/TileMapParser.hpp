#pragma once

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <sstream>
#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "dot/E/Tile.hpp"
#include "dot/E/Entity.hpp"
#include "dot/C/Sprite.hpp"
#include "dot/Utilities/WorkingDirectory.hpp"
#include "dot/C/BoxCollider.hpp"
#include "dot/C/SpriteBoxCollider.hpp"
#include "dot/Utilities/Utils.hpp"
#include "dot/C/DrawnLightBounds.hpp"

using namespace rapidxml;


namespace dot
{

struct TileSheetData
{
	int firstgid;
	int tilewidth;
	int tileheight;
	int tilecount;
	int columns;
	unsigned textureID;

}; // struct TileSetDataa

struct MapLayer
{
	std::vector<std::shared_ptr<Tile>> tiles;
	bool isVisible;
};

using MapTiles = std::vector<std::pair<std::string, std::shared_ptr<MapLayer>>>;
using TileSet = std::unordered_map<unsigned, std::shared_ptr<TileInfo>>;
using TileSheets = std::map<int, std::shared_ptr<TileSheetData>>;

class TileMapParser
{
public:
	TileMapParser(dot::TextureAllocator& textureAllocator, dot::SharedContext& context, const std::string& resourcesPath);
	std::vector<std::shared_ptr<dot::Entity>> parse(const std::string& file, sf::Vector2i offset);
private:
	std::shared_ptr<TileSheets> buildTileSheetData(xml_node<>* rootNode);
	std::shared_ptr<MapTiles> buildMapTiles(xml_node<>* rootNode);
	std::pair<std::string, std::shared_ptr<MapLayer>> buildLayer(xml_node<>* layerNode, std::shared_ptr<TileSheets> tileSheets);

	dot::TextureAllocator& m_textureAllocator;
	dot::SharedContext& m_context;
	std::string m_resourcesPath;
}; // class TileMapParser



}; // namespace dot