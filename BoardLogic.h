#pragma once
#include "Tile.h"
#include <unordered_map>
#include <vector>
using std::vector;
using std::unordered_map;

class BoardLogic {
protected:
	const int NUM_TILES = 400;
	int numMines = 0;
	int numFlags = 0;
	int numRevealed = 0;
	bool debug = false;
	vector<bool> boolArray;
	vector<Tile> tileArray;
	vector<sf::Sprite> flagCount;
	unordered_map<const char*, sf::Sprite> otherSprites;
	enum class State { Win, Lose, Neutral };
	State currState = State::Neutral;
	void loadSprite(sf::Vector2f pos, const char* name, unordered_map<const char*, sf::Sprite>& sprites);
	void refreshBoard(bool boardFile);
	void readBoardFile(const char* boardFile);
	void setMineField(bool useBoolArray);
	void setNeighbors();
	void finish(State state);
	void revealTile(Tile& tile);
	void setFlagCount();
};

