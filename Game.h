#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "MainMenu.h"
#include "GameSelection.h"
#include "RedLightGreenLight.h"
#include "Dalgona.h"
#include "TugOfWar.h"
#include "GlassBridge.h"
#include "Intermission.h"
#include "SquidGame.h"
#include "GameState.h"
#include "MiniGameType.h"

#include "HumanPlayer.h"
#include "CPUPlayer.h"

class Game
{
private:
    sf::RenderWindow window;

    // The six contestants belong to the overall game
    // The sixteen contestants belong to the overall game
    HumanPlayer player;

    CPUPlayer cpu1;
    CPUPlayer cpu2;
    CPUPlayer cpu3;
    CPUPlayer cpu4;
    CPUPlayer cpu5;
    CPUPlayer cpu6;
    CPUPlayer cpu7;
    CPUPlayer cpu8;
    CPUPlayer cpu9;
    CPUPlayer cpu10;
    CPUPlayer cpu11;
    CPUPlayer cpu12;
    CPUPlayer cpu13;
    CPUPlayer cpu14;
    CPUPlayer cpu15;

    MainMenu mainMenu;
    GameSelection gameSelection;

    RedLightGreenLight redLightGreenLight;
    Dalgona dalgona;
    TugOfWar tugOfWar;
    GlassBridge glassBridge;
    Intermission intermission;
    SquidGame squidGame;


    sf::Text livesLabel;
    sf::Text heartTexts[3];

    sf::RectangleShape gameOverBox;
    sf::Text gameOverText;

    sf::RectangleShape returnToMenuButtonBox;
    sf::Text returnToMenuButton;

    // =========================================================
// PLAYER LIFE SYSTEM
// =========================================================

    int playerLives;


    // =========================================================
    // CURRENT GAME CHECKPOINT
    // =========================================================

    std::vector<Participant*> gameCheckpoint;


    // =========================================================
    // LIFE / CHECKPOINT HELPERS
    // =========================================================

    void saveGameCheckpoint();

    void restoreGameCheckpoint();

    bool isPlayerAlive();

    sf::Font font;
    sf::Text comingSoonText;
    sf::Text continueButton;

    GameState currentState;


    bool paused;

    sf::RectangleShape pauseOverlay;
    sf::RectangleShape resumeButtonBox;
    sf::RectangleShape mainMenuButtonBox;

    sf::Text resumeButton;
    sf::Text mainMenuButton;

    sf::RectangleShape countdownBox;
    sf::Text countdownText;

    sf::Clock countdownClock;

    bool countdownActive;
    int countdownNumber;

    std::vector<Participant*> participants;
    std::vector<Participant*> sessionParticipants;
    std::vector<MiniGameType> selectedGames;
    int currentGameIndex;
    int selectedBotCount;

    sf::Text botCountText;
public:
    Game();

    void run();

    void drawLives();
    void resetAllParticipants();
    void triggerGameOver();
    void startCountdown();
    std::vector<Participant*> getSurvivors();

};