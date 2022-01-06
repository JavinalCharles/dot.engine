#include "dot/TileMapParser.hpp"
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>

using dot::TileMapParser;
using dot::TextureAllocator;
using dot::SharedContext;
using dot::Entity;
using dot::MapTiles;
using dot::TileSet;
using dot::TileSheets;
using dot::MapLayer;

TileMapParser::TileMapParser(TextureAllocator& textureAllocator, SharedContext& context, const std::string& resourcesPath)
	: m_textureAllocator(textureAllocator),
	m_context(context),
	m_resourcesPath(resourcesPath)
{

}

std::vector<std::shared_ptr<dot::Entity>> TileMapParser::parse(const std::string& file, sf::Vector2i offset)
{
	std::ifstream f(file);
	std::stringstream stream;
	stream << f.rdbuf();
	f.close();

	std::string xmlFile(stream.str());

	char data[xmlFile.size()+1];
	strncpy(data, xmlFile.c_str(), xmlFile.size()+1);


	rapidxml::xml_document<> doc;
	std::cout << "Parsing " << data << std::endl;
	doc.parse<0>(data);
	xml_node<>* rootNode = doc.first_node("map");

	// Load Tile Layers from XML
	std::shared_ptr<MapTiles> map = buildMapTiles(rootNode);

	int tilewidth = std::atoi(rootNode->first_attribute("tilewidth")->value());
	int tileheight = std::atoi(rootNode->first_attribute("tileheight")->value());

	std::vector<std::shared_ptr<Entity>> tileObjects;
	unsigned int layerCount = map->size() - 1;

	for (const auto& layer : *map)
	{
		for (const auto& tile : layer.second->tiles)
		{
			std::shared_ptr<TileInfo> tileInfo = tile->properties;

			std::shared_ptr<Entity> tileObject = std::make_shared<Entity>(&m_context);

			const unsigned int tileScale = 2;

			if (layer.second->isVisible)
			{
				auto sprite = tileObject->addComponent<dot::Sprite>();

				sprite->load(tileInfo->textureID);
				sprite->setTextureRect(tileInfo->textureRect);
				sprite->setScale(tileScale, tileScale);

				sprite->setSortOrder(layerCount);
				sprite->setDrawLayer(1);
			}

			float x = tile->x * tilewidth * tileScale + offset.x;
			float y = tile->y * tileheight * tileScale + offset.y;
			tileObject->transform->setPosition(x, y);
			tileObject->transform->setStatic(true);

			if (layer.first == "Collisions")
			{
				// TODO: Define tile-entity collision behaviour
			}
			tileObjects.emplace_back(tileObject);
		}
		--layerCount;
	}

	std::cout << "Parser returning with " << tileObjects.size() << " objects." << std::endl;

	return tileObjects;
}


std::shared_ptr<MapTiles> TileMapParser::buildMapTiles(xml_node<>* rootNode)
{
	std::shared_ptr<TileSheets> tileSheetData = buildTileSheetData(rootNode);

	std::shared_ptr<MapTiles> map = std::make_shared<MapTiles>();

	for (xml_node<>* node = rootNode->last_node("layer"); node; node = node->previous_sibling("layer"))
	{
		std::pair<std::string, std::shared_ptr<MapLayer>> mapLayer = buildLayer(node, tileSheetData);
		map->emplace_back(mapLayer);
	}
	return map;
}

std::shared_ptr<TileSheets> TileMapParser::buildTileSheetData(xml_node<>* rootNode)
{
	TileSheets tileSheets;

	for(xml_node<>* tilesheetNode = rootNode->first_node("tileset"); tilesheetNode; tilesheetNode = tilesheetNode->next_sibling("tileset"))
	{
		TileSheetData tileSheetData;

		tileSheetData.firstgid = tilesheetNode->first_attribute("firstgid") ? std::atoi(tilesheetNode->first_attribute("firstgid")->value()) : 0;


		std::cout << "Reading .tsx file: " << m_resourcesPath << "/" << tilesheetNode->first_attribute("source")->value() << std::endl;
		std::string tsxFile(m_resourcesPath + "/" +tilesheetNode->first_attribute("source")->value());
		
		std::ifstream f(tsxFile);
		std::stringstream stream;
		stream << f.rdbuf();
		f.close();
		std::string xmlFile(stream.str());

		char data[xmlFile.size()+1];

		strncpy(data, xmlFile.c_str(), xmlFile.size()+1);
		std::cout << "Read .tsx file: " << data << std::endl;
		
		rapidxml::xml_document<> doc;
		doc.parse<0>(data);
		xml_node<>* tsxNode = doc.first_node("tileset");
		tileSheetData.tilewidth = std::atoi(tsxNode->first_attribute("tilewidth")->value());
		tileSheetData.tileheight = std::atoi(tsxNode->first_attribute("tileheight")->value());
		tileSheetData.tilecount = std::atoi(tsxNode->first_attribute("tilecount")->value());
		tileSheetData.columns = std::atoi(tsxNode->first_attribute("columns")->value());

		xml_node<>* imageNode = tsxNode->first_node("image");
		std::string imageSource = imageNode->first_attribute("source")->value();
		tileSheetData.textureID = m_textureAllocator.add(m_resourcesPath + "/" + imageSource);

		tileSheets.insert(std::make_pair(tileSheetData.firstgid, std::make_shared<TileSheetData>(tileSheetData)));
	}

	return std::make_shared<TileSheets>(tileSheets);
}

std::pair<std::string, std::shared_ptr<MapLayer>> TileMapParser::buildLayer(xml_node<>* layerNode, std::shared_ptr<TileSheets> tileSheets)
{
	std::cout << "Making a Map Layer" << std::endl;
	TileSet tileset;
	std::shared_ptr<MapLayer> layer = std::make_shared<MapLayer>();

	int width = std::atoi(layerNode->first_attribute("width")->value());
	int height = std::atoi(layerNode->first_attribute("height")->value());

	xml_node<>* dataNode = layerNode->first_node("data");

	char* mapIndices = dataNode->value();
	std::stringstream fileStream(mapIndices);
	int count = 0;

	std::string line;
	while(fileStream.good())
	{
		std::string substr;
		std::getline(fileStream, substr, ',');

		if (dot::Utils::isInteger(substr))
		{
			substr.erase(std::remove(substr.begin(), substr.end(), '\r'), substr.end());
			substr.erase(std::remove(substr.begin(), substr.end(), '\n'), substr.end());
			// TODO: check if the character removals worked
		}
		int tileId = std::stoi(substr);
		if(tileId != 0)
		{
			auto itr = tileset.find(tileId);
			if (itr == tileset.end())
			{
				std::shared_ptr<TileSheetData> tileSheet;
				int firstId;

				for (auto iter = tileSheets->rbegin(); iter != tileSheets->rend(); ++iter)
				{
					if(tileId >= iter->first)
					{
						firstId = iter->first;
						tileSheet = iter->second;
						break;
					}
				}
				std::cout << "firstId: " << firstId << std::endl; 
				if (!tileSheet)
				{
					continue;
				}

				int textureX = (tileId - firstId) % tileSheet->columns;
				int textureY = (tileId - firstId) / tileSheet->columns;

				if (textureX < 0)
				{
					std::cout << "Here!" << std::endl;
				}

				std::cout << "tileID: " << tileId << " textureX: " << textureX << "; textureY: " << textureY << std::endl;
				std::cout << "Coords:" << textureX * tileSheet->tilewidth << ", " << textureY * tileSheet->tileheight << std::endl; 


				std::shared_ptr<TileInfo> tileInfo = std::make_shared<TileInfo>(tileSheet->textureID, tileId, sf::IntRect(textureX * tileSheet->tilewidth, textureY * tileSheet->tileheight, tileSheet->tilewidth, tileSheet->tilewidth));

				itr = tileset.insert(std::make_pair(tileId, tileInfo)).first;
			}

			std::shared_ptr<Tile> tile = std::make_shared<Tile>();

			tile->properties = itr->second;
			tile->x = count % width - 1;
			tile->y = count / width;

			layer->tiles.emplace_back(tile);
		}
		++count;
	}
	const std::string layerName = layerNode->first_attribute("name")->value();

	bool layerVisible = true;
	xml_attribute<>* visibleAttribute = layerNode->first_attribute("visible");

	if(visibleAttribute)
	{
		layerVisible = std::atoi(visibleAttribute->value());
	}
	layer->isVisible = layerVisible;

	std::cout << "Created a Map Layer: " << layerName << std::endl;

	return std::make_pair(layerName, layer);
}