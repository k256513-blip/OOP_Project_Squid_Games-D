#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Participant
{
protected:
    std::string name;
    bool alive;
    bool finished;
    int finishPosition;
    sf::RectangleShape body;

public:
    Participant(
        std::string participantName,
        sf::Color color
    );
    virtual ~Participant() = default;
    virtual bool isCPU() const { return false; }

    void draw(sf::RenderWindow& window);

    void setPosition(float x, float y);
    void move(float x, float y);

    std::string getName();
    bool isAlive();
    bool hasFinished();
    int getFinishPosition();
    void setFinishPosition(int position);
    void eliminate();
    void revive();
    void resetForNextGame();
    void finish();
    sf::Vector2f getPosition();
    sf::Color getColor();
};