#include "BoardLogic.h"
#include <fstream>
#include <stdexcept>
using namespace std;

void BoardLogic::loadSprite(sf::Vector2f pos, const char* name, unordered_map<const char*, sf::Sprite>& sprites) {
	sf::Sprite sprite = SpriteManager::getSprite(name);
	sprite.setPosition(pos);
	sprites.insert({ name, sprite });
}

void BoardLogic::refreshBoard(bool boardFile) {
	for (Tile& tile : tileArray) {
		tile.setFlagged(false);
		tile.setMined(false);
		tile.setRevealed(false);
		tile.emptyNeighbors();
	}
	numMines = numFlags = numRevealed = 0;
	setMineField(boardFile);
}

void BoardLogic::readBoardFile(const char* boardFile) {
	ifstream file(boardFile);
	boolArray.clear();
	char temp;
	while (file.get(temp)) {
		if (temp == '1') {
			boolArray.push_back(true);
		} else if (temp == '0') {
			boolArray.push_back(false);
		}
	}
	file.close();
	refreshBoard(true);
}

void BoardLogic::setMineField(bool useBoolArray) {
	if (useBoolArray) {
		for (int i = 0; i < NUM_TILES; ++i) {
			tileArray[i].setMined(boolArray[i]);
			if (boolArray[i]) ++numMines;
		}
	} else {
		while (numMines < 50) {
			int rng = rand() % NUM_TILES;
			if (!tileArray[rng].ismined()) {
				tileArray[rng].setMined(true);
				++numMines;
			}
		}
	}
	numFlags = numMines;
	setFlagCount();
	setNeighbors();
}

void BoardLogic::setNeighbors() {
	for (int i = 0; i < 16; ++i) {
		for (int j = 0; j < 25; ++j) {	
			int curr = (i * 25) + j;
			Tile& thisTile = tileArray[curr];
			if (thisTile.ismined()) {
				if (i - 1 >= 0 && j - 1 >= 0) tileArray.at(curr - 26).addNeighbor(&thisTile); 		  
				if (i - 1 >= 0) tileArray.at(curr - 25).addNeighbor(&thisTile);					  
				if (i - 1 >= 0 && j + 1 < 25) tileArray.at(curr - 24).addNeighbor(&thisTile);
				if (j - 1 >= 0) tileArray.at(curr - 1).addNeighbor(&thisTile);
				if (j + 1 < 25) tileArray.at(curr + 1).addNeighbor(&thisTile);
				if (i + 1 < 16 && j - 1 >= 0) tileArray.at(curr + 24).addNeighbor(&thisTile);
				if (i + 1 < 16) tileArray.at(curr + 25).addNeighbor(&thisTile);
				if (i + 1 < 16 && j + 1 < 25) tileArray.at(curr + 26).addNeighbor(&thisTile);
			}
		}
	}
}

void BoardLogic::finish(State state) {
	if (state == State::Lose) {
		for (Tile& tile : tileArray) {
			if (tile.ismined() && !tile.isflagged()) 
				tile.setRevealed(true);
		}
	} else if (state == State::Win) {
		for (Tile& tile : tileArray) {
			if (!tile.ismined() && tile.isflagged()) {
				++numFlags;
				tile.setFlagged(false);
			} else if (tile.ismined() && !tile.isflagged()) {
				--numFlags;
				tile.setFlagged(true);
			}
		}
		setFlagCount();
	}
	currState = state;
}

void BoardLogic::revealTile(Tile& tile) {
	if (!tile.isrevealed() && !tile.isflagged()) {
		tile.setRevealed(true);
		++numRevealed;
		if (tile.numNeighbors() == 0) {
			auto coordinate = tile.getPos();
			int j = (int)coordinate.x / 32;
			int i = (int)coordinate.y / 32;
			int curr = (i * 25) + j;
			if (i - 1 >= 0 && j - 1 >= 0) revealTile(tileArray.at(curr - 26));
			if (i - 1 >= 0) revealTile(tileArray.at(curr - 25));
			if (i - 1 >= 0 && j + 1 < 25) revealTile(tileArray.at(curr - 24));
			if (j - 1 >= 0) revealTile(tileArray.at(curr - 1));
			if (j + 1 < 25) revealTile(tileArray.at(curr + 1));
			if (i + 1 < 16 && j - 1 >= 0) revealTile(tileArray.at(curr + 24));
			if (i + 1 < 16) revealTile(tileArray.at(curr + 25));
			if (i + 1 < 16 && j + 1 < 25) revealTile(tileArray.at(curr + 26));
		}
	}
}

void BoardLogic::setFlagCount() {
	flagCount.clear();
	int ones = abs(numFlags) % 10;
	int tens = abs(numFlags / 10) % 10;
	int hundreds = abs(numFlags / 100) % 10;
	sf::Sprite onesPlace = SpriteManager::getSprite(ones);
	sf::Sprite tensPlace = SpriteManager::getSprite(tens);
	sf::Sprite hundredsPlace = SpriteManager::getSprite(hundreds);
	if (numFlags < 0) {
		sf::Sprite neg = SpriteManager::getSprite(-1);
		neg.setPosition(0, 512);
		flagCount.push_back(neg);
		hundredsPlace.setPosition(21, 512);
		tensPlace.setPosition(42, 512);
		onesPlace.setPosition(63, 512);
	} else {
		hundredsPlace.setPosition(0, 512);
		tensPlace.setPosition(21, 512);
		onesPlace.setPosition(42, 512);
	}
	flagCount.push_back(hundredsPlace);
	flagCount.push_back(tensPlace);
	flagCount.push_back(onesPlace);
}