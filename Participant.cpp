#include "Participant.h"

Participant::Participant(
    std::string participantName,
    sf::Color color
)
{
    name = participantName;
    alive = true;
    finished = false;
    finishPosition = 0;
    body.setSize(sf::Vector2f(40, 40));
    body.setFillColor(color);
}

void Participant::draw(sf::RenderWindow& window)
{
    if (alive)
    {
        window.draw(body);
    }
}

std::string Participant::getName()
{
    return name;
}

bool Participant::isAlive()
{
    return alive;
}

bool Participant::hasFinished()
{
    return finished;
}

int Participant::getFinishPosition()
{
    return finishPosition;
}

void Participant::setFinishPosition(int position)
{
    finishPosition = position;
}

void Participant::eliminate()
{
    alive = false;
}

void Participant::revive()
{
    alive = true;
    finished = false;
    finishPosition = 0;
}
void Participant::resetForNextGame()
{
    finished = false;
    finishPosition = 0;
}

void Participant::finish()
{
    finished = true;
}

void Participant::setPosition(float x, float y)
{
    body.setPosition(x, y);
}

void Participant::move(float x, float y)
{
    body.move(x, y);
}

sf::Vector2f Participant::getPosition()
{
    return body.getPosition();
}

sf::Color Participant::getColor()
{
    return body.getFillColor();
}