#pragma once

#include <SFML/Graphics.hpp>
#include "GameState.h"
#include "CPUPlayer.h"
#include "HumanPlayer.h"
#include <SFML/Audio.hpp>
class RedLightGreenLight
{
private:
    HumanPlayer& player;

    CPUPlayer& cpu1;
    CPUPlayer& cpu2;
    CPUPlayer& cpu3;
    CPUPlayer& cpu4;
    CPUPlayer& cpu5;
    CPUPlayer& cpu6;
    CPUPlayer& cpu7;
    CPUPlayer& cpu8;
    CPUPlayer& cpu9;
    CPUPlayer& cpu10;
    CPUPlayer& cpu11;
    CPUPlayer& cpu12;
    CPUPlayer& cpu13;
    CPUPlayer& cpu14;
    CPUPlayer& cpu15;


    // =========================================================
// RLGL AUDIO
// =========================================================

    sf::SoundBuffer greenLightBuffer;
    sf::SoundBuffer redLightBuffer;
    sf::SoundBuffer gunshotBuffer;

    sf::Sound greenLightSound;
    sf::Sound redLightSound;
    sf::Sound gunshotSound;
    bool initialGreenSoundPlayed;

    // =========================================================
// PLAYER 1 SPRITE / ANIMATION
// =========================================================

    sf::Texture playerIdleTexture;

    sf::Texture playerWalkTextures[5];

    sf::Sprite playerSprite;

    int playerWalkFrame;

    sf::Clock playerAnimationClock;
    sf::Clock playerMovementVisualClock;

    




    // =========================================================
// CPU SPRITES / ANIMATION
// =========================================================

    CPUPlayer* cpuPlayers[15];

    sf::Texture cpuIdleTextures[15];
    sf::Texture cpuWalkTextures[15][5];

    sf::Sprite cpuSprites[15];

    int cpuWalkFrame[15];

    sf::Clock cpuAnimationClocks[15];
    sf::Clock cpuMovementVisualClocks[15];

    int idleX[8];
    int idleY[8];

    int walkX[8];
    int walkY[8];


    sf::RectangleShape finishLine;
    // =========================================================
// RLGL BACKGROUND
// =========================================================

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::Font font;
    sf::Text lightText;
    sf::Text resultText;
    sf::Text continueButton;
    sf::RectangleShape continueButtonBox;
    sf::Text cpuResultText;
    sf::Clock lightClock;
    sf::Clock cpuClock;
    sf::Clock redLightGraceClock;
    sf::Text playerOneLabel;

    // =========================================================
// DOLL
// =========================================================

    sf::Texture dollTextures[11];
    sf::Sprite dollSprite;

    int dollFrame;
    sf::Clock dollAnimationClock;


    // =========================================================
    // GUARDS
    // =========================================================

    sf::Texture guardTextures[5];

    sf::Sprite guardSprites[6];

    int guardFrame;
    sf::Clock guardAnimationClock;


    float lightDuration;
    bool greenLight;
    bool playerFinished;
    bool playerEliminated;
    bool cpuCheckedRedLight;
    int nextFinishPosition;
    int playerFinishPosition;

public:
    RedLightGreenLight(
        HumanPlayer& player,

        CPUPlayer& cpu1,
        CPUPlayer& cpu2,
        CPUPlayer& cpu3,
        CPUPlayer& cpu4,
        CPUPlayer& cpu5,
        CPUPlayer& cpu6,
        CPUPlayer& cpu7,
        CPUPlayer& cpu8,
        CPUPlayer& cpu9,
        CPUPlayer& cpu10,
        CPUPlayer& cpu11,
        CPUPlayer& cpu12,
        CPUPlayer& cpu13,
        CPUPlayer& cpu14,
        CPUPlayer& cpu15
    );

    GameState handleInput(sf::Event& event);
    void update();
    void draw(sf::RenderWindow& window);

    bool isFinished();
    void reset();
    void prepareNextGame();
};