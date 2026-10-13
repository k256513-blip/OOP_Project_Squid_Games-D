#include "CPUPlayer.h"
#include <cstdlib>

CPUPlayer::CPUPlayer(
    std::string playerName,
    float playerSkill,
    sf::Color color
)
    : Participant(playerName, color)
{
    skill = playerSkill;
}

bool CPUPlayer::shouldMove()
{
    int randomNumber = std::rand() % 100;

    return randomNumber < skill;
}

bool CPUPlayer::getsCaught()
{
    int randomNumber = std::rand() % 100;

    float catchChance = 20.0f - (skill * 0.2f);

    return randomNumber < catchChance;
}
bool CPUPlayer::isCPU() const
{
    return true;
}
float CPUPlayer::getSkill()
{
    return skill;
}