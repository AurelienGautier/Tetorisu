#pragma once
#include "global.hpp"

class Button
{
    public:
        Button();
        Button(int upEdge, int leftEdge);
        Button(int upEdge, int leftEdge, std::string string, sf::Font font, int charSize);

        void setPos(int upEdge, int leftEdge);
        void setText(std::string string, sf::Font font, int charSize);
        bool isClicked(sf::Vector2i mousePosition);
        void display(sf::RenderWindow &window);

    private:
        int upEdge, leftEdge, downEdge, rightEdge;
        std::string string;
        sf::Text text;
        sf::Font font;
        int charSize;
};