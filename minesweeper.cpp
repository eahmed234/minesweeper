#include "board.h"
std::unordered_map<string, sf::Texture> SpriteManager::textures;

int main() {
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 600), "Minesweeper");
    sf::Image icon;
    icon.loadFromFile("images/mine.png");
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    Board board;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            } else if (event.type == sf::Event::MouseButtonPressed) {
                auto a = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                if (event.mouseButton.button == sf::Mouse::Left) {
                    board.onLeftMouseClick(a);
                } else if (event.mouseButton.button == sf::Mouse::Right) {
                    board.onRightMouseClick(a);
                }
            }
            window.clear(sf::Color::White);
            board.drawTiles(window);
            window.display();
        }
    }
    return 0;
}