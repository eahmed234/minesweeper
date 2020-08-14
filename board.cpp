#include "board.h"

Board::Board() {
	SpriteManager::setSprites();
	currState = State::Neutral;
	tileArray.reserve(NUM_TILES);
	for (int i = 0; i < 16; ++i) {
		for (int j = 0; j < 25; ++j) {
			auto pos = sf::Vector2f((float)j * 32.0f, (float)i * 32.0f);
			Tile tile(pos);
			tileArray.push_back(tile);
		}
	}
	setMineField(false);
	loadSprite(sf::Vector2f(368, 512), "face_happy", otherSprites);
	loadSprite(sf::Vector2f(368, 512), "face_lose", otherSprites);
	loadSprite(sf::Vector2f(368, 512), "face_win", otherSprites);
	loadSprite(sf::Vector2f(464, 512), "debug", otherSprites);
	loadSprite(sf::Vector2f(528, 512), "test_1", otherSprites);
	loadSprite(sf::Vector2f(592, 512), "test_2", otherSprites);
	loadSprite(sf::Vector2f(656, 512), "test_3", otherSprites);
}

void Board::onLeftMouseClick(sf::Vector2f mouse) {
	if (currState == State::Neutral) {
		bool done = false;
		for (Tile& tile : tileArray) {
			if (tile.getTileSprite().getGlobalBounds().contains(mouse) && !tile.isrevealed() && !tile.isflagged()) {
				if (tile.ismined()) {
					finish(State::Lose);
				} else {
					revealTile(tile);
				}
				if (numRevealed + numMines == NUM_TILES) {
					finish(State::Win);
				}
				done = true;
				break;
			}
		}
		if (!done) {
			for (auto const& s : otherSprites) {
				if (s.second.getGlobalBounds().contains(mouse)) {
					if (s.first == "face_happy") {
						refreshBoard(false);
						break;
					} else if (s.first == "debug") {
						debug = !debug;
						break;
					} else if (s.first == "test_1") {
						readBoardFile("boards/testboard1.brd");
						break;
					} else if (s.first == "test_2") {
						readBoardFile("boards/testboard2.brd");
						break;
					} else if (s.first == "test_3") {
						readBoardFile("boards/testboard3.brd");
						break;
					}
				}
			}
		}
	} else if (currState == State::Lose || currState == State::Win) {
		if (otherSprites["face_lose"].getGlobalBounds().contains(mouse) || otherSprites["face_win"].getGlobalBounds().contains(mouse)) {
			refreshBoard(false);
			currState = State::Neutral;
		} else if (otherSprites["debug"].getGlobalBounds().contains(mouse)) {
			debug = !debug;
		} else if (otherSprites["test_1"].getGlobalBounds().contains(mouse)) {
			readBoardFile("boards/testboard1.brd");
			refreshBoard(true);
			currState = State::Neutral;
		} else if (otherSprites["test_2"].getGlobalBounds().contains(mouse)) {
			readBoardFile("boards/testboard2.brd");
			refreshBoard(true);
			currState = State::Neutral;
		} else if (otherSprites["test_3"].getGlobalBounds().contains(mouse)) {
			readBoardFile("boards/testboard3.brd");
			refreshBoard(true);
			currState = State::Neutral;
		}
	}
}

void Board::onRightMouseClick(sf::Vector2f mouse) {
	for (Tile& tile : tileArray) {
		if (tile.getTileSprite().getGlobalBounds().contains(mouse) && !tile.isrevealed()) {
			if (!tile.isflagged()) {
				--numFlags;
				tile.setFlagged(true);
			} else {
				++numFlags;
				tile.setFlagged(false);
			}
			setFlagCount();
			break;
		}
	}
}

void Board::drawTiles(sf::RenderWindow& window) {
	for (Tile& tile : tileArray) {
		window.draw(tile.getTileSprite());
		window.draw(tile.getLayerSprite());
		if (tile.ismined() && (debug || currState == State::Lose))
			window.draw(tile.getMineOverlay());
	}
	switch (currState) {
	case State::Neutral:
		window.draw(otherSprites["face_happy"]);
		break;
	case State::Lose:
		window.draw(otherSprites["face_lose"]);
		break;
	case State::Win:
		window.draw(otherSprites["face_win"]);
	}
	window.draw(otherSprites["debug"]);
	window.draw(otherSprites["test_1"]);
	window.draw(otherSprites["test_2"]);
	window.draw(otherSprites["test_3"]); 
	for (sf::Sprite& s : flagCount) {
		window.draw(s);
	}
}
