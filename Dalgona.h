#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include "GameState.h"
#include "Participant.h"
#include "HumanPlayer.h"
#include "CPUPlayer.h"
#include "DalgonaShape.h"

class Dalgona
{
private:
    // All contestants who entered Dalgona
    std::vector<Participant*> participants;

    // Contestants currently playing this batch
    std::vector<Participant*> currentBatch;

    CPUPlayer* cpuPlayers[4];

    DalgonaShape playerShapes[4];

    std::vector<char> sequences[4];

    sf::Font font;

    sf::Text title;
    sf::Text resultText;
    sf::Text continueButton;
    sf::RectangleShape continueButtonBox;

    sf::RectangleShape compartments[4];
    sf::CircleShape cookies[4];

    sf::CircleShape circleShapes[4];
    sf::ConvexShape triangleShapes[4];
    sf::RectangleShape squareShapes[4];

    sf::Text playerNames[4];
    sf::Text eliminatedText[4];
    sf::Text passedText[4];
    sf::Text sequenceText[4][4];

    sf::Clock memorizationClock;
    sf::Clock cpuClock;

    bool memorizationPhase;
    bool inputPhase;

    int currentSequenceIndex;
    int cpuSequenceIndex[4];

   
    bool playerCompleted;
    bool gameFinished;

    // =========================================================
  // BACKGROUND
  // =========================================================

    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    int currentBatchStart;
    int currentBatchSize;
    int totalBatches;
    int currentBatchNumber;
    int humanBatchSlot;

    void generateSequences();
    void updateCPUs();
    void setupNextBatch();

public:
    Dalgona(
        HumanPlayer* player1,
        CPUPlayer* player2,
        CPUPlayer* player3,
        CPUPlayer* player4,
        CPUPlayer* player5,
        CPUPlayer* player6
    );

    GameState handleInput(sf::Event& event);

    void update();

    void draw(sf::RenderWindow& window);

    void reset();
    void startGame();

    void setParticipants(
        const std::vector<Participant*>& survivors
    );
};