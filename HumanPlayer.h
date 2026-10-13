#pragma once

#include "Participant.h"

class HumanPlayer : public Participant
{
public:
    HumanPlayer(
        std::string playerName,
        sf::Color color
    );
};
