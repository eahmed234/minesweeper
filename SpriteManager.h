#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
using std::string;

struct SpriteManager {
	static std::unordered_map<string, sf::Texture> textures;
	static sf::Sprite getSprite(string s) { 
		sf::Sprite sp(textures.at(s));
		return sp;
	}
	static sf::Sprite getSprite(int i) {
		sf::Sprite digit(textures["digits"]);
		if (i == -1) {
			digit.setTextureRect(sf::IntRect(210, 0, 21, 32));
		} else {
			digit.setTextureRect(sf::IntRect(i * 21, 0, 21, 32));
		}
		return digit;
	}
	static void setSprites() {
		string names[] = {
			"digits",
			"mine",
			"tile_hidden",
			"tile_revealed",
			"number_1",
			"number_2",
			"number_3",
			"number_4",
			"number_5",
			"number_6",
			"number_7",
			"number_8",
			"flag",
			"face_happy",
			"face_win",
			"face_lose", 
			"debug", 
			"test_1", 
			"test_2", 
			"test_3" 
		};
		for (string s : names) {
			sf::Texture texture;
			texture.loadFromFile("images/" + s + ".png");
			textures[s] = texture;
		}
	}
};