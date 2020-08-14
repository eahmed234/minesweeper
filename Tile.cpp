#include "Tile.h"
#include <string>

Tile::Tile(sf::Vector2f _pos) : pos(_pos) { setPosition(); }

void Tile::setMined(bool _isMined) { isMined = _isMined; }

void Tile::setFlagged(bool _isFlagged) {
	isFlagged = _isFlagged;
	if (isFlagged) {
		tileSprite = SpriteManager::getSprite("tile_hidden");
		upperLayer = SpriteManager::getSprite("flag");
	} else {
		tileSprite = SpriteManager::getSprite("tile_revealed");
		upperLayer = SpriteManager::getSprite("tile_hidden");
	}
	setPosition();
}

void Tile::setRevealed(bool _isRevealed) { 
	isRevealed = _isRevealed;
	if (isRevealed) {
		if (isMined) {
			upperLayer = SpriteManager::getSprite("mine");
		} else {
			if (minedNeighbors.size() > 0) {
				upperLayer = SpriteManager::getSprite("number_" + std::to_string(minedNeighbors.size()));
			} else {
				upperLayer = SpriteManager::getSprite("tile_revealed");
			}
		}
	} else {
		tileSprite = SpriteManager::getSprite("tile_revealed");
		upperLayer = SpriteManager::getSprite("tile_hidden");
	}
	setPosition();
}

void Tile::setPosition() {
	tileSprite.setPosition(pos);
	upperLayer.setPosition(pos);
	mineOverlay.setPosition(pos);
}

void Tile::addNeighbor(Tile* tile) {
	minedNeighbors.push_back(tile);
}

void Tile::emptyNeighbors() {
	minedNeighbors.clear();
}
