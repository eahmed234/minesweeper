#pragma once
#include "SpriteManager.h"
#include <SFML/Graphics.hpp>
#include <vector>
using std::vector;

class Tile {
	bool isMined = false;
	bool isFlagged = false;
	bool isRevealed = false;
	vector<Tile*> minedNeighbors;
	sf::Sprite tileSprite = SpriteManager::getSprite("tile_revealed");
	sf::Sprite upperLayer = SpriteManager::getSprite("tile_hidden");
	sf::Sprite mineOverlay = SpriteManager::getSprite("mine");
	sf::Vector2f pos;
public:
	Tile(sf::Vector2f _pos);
	sf::Sprite& getTileSprite() { return tileSprite; }
	sf::Sprite& getLayerSprite() { return upperLayer; }
	sf::Sprite& getMineOverlay() { return mineOverlay; }
	sf::Vector2f getPos() { return pos; }
	bool ismined() { return isMined; }
	bool isflagged() { return isFlagged; }
	bool isrevealed() { return isRevealed; }
	void setMined(bool _isMined);
	void setFlagged(bool _isFlagged);
	void setRevealed(bool _isRevealed);
	void setPosition();
	void addNeighbor(Tile* tile);
	void emptyNeighbors();
	int numNeighbors() { return minedNeighbors.size(); }
};
