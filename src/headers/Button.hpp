#pragma once
#include "global.hpp"

constexpr bool CLICKABLE = true;
constexpr bool NOT_CLICKABLE = false;

class Button
{
    private:
        int upEdge, leftEdge, downEdge, rightEdge;
        std::string string;
        sf::Text text;
        sf::Font font;
        int charSize;
        bool isCursorOn(sf::Vector2f mousePosition);
        bool clickable;
    
public:
    Button(int leftEdge, int upEdge, std::string string, sf::Font font, int charSize, bool clickable);

    void setPos(int upEdge, int leftEdge);
    void setText(std::string string, sf::Font font, int charSize);
    bool isClicked(sf::Vector2f mousePosition, bool& isLMBpressed);
    void display(sf::RenderWindow &window, sf::Vector2f& mousePosition);
    void operator=(Button button);

    int get_upEdge() { return this->upEdge; }
    int get_leftEdge() { return this->leftEdge; }
    std::string get_string() { return this->string; }
    sf::Font get_font() { return this->font; }
    int get_charSize() { return this->charSize; }

};