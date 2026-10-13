#pragma once

#include "Participant.h"

class CPUPlayer : public Participant
{
private:
    float skill;

public:
    CPUPlayer(
        std::string playerName,
        float playerSkill,
        sf::Color color
    );

    bool shouldMove();
    bool getsCaught();
    bool isCPU() const override;
    float getSkill();
};