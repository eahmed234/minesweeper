#pragma once
#include "BoardLogic.h"

struct Board : public BoardLogic {
public:
	Board();
	void onLeftMouseClick(sf::Vector2f);
	void onRightMouseClick(sf::Vector2f);
	void drawTiles(sf::RenderWindow& window);
};

