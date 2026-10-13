#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "GameState.h"
#include "Participant.h"


class GlassBridge
{
private:

    // =========================================================
    // CONSTANTS
    // =========================================================

    static const int ROW_COUNT = 10;


    // =========================================================
    // PARTICIPANTS
    // =========================================================

    std::vector<Participant*> participants;

    std::vector<Participant*> activeParticipants;
    std::vector<Participant*> passedParticipants;

    std::vector<Participant*> turnOrder;

    int turnIndex;

    Participant* currentParticipant;


    // =========================================================
    // PARTICIPANT POSITION
    // =========================================================

    struct ParticipantBridgeData
    {
        Participant* participant;
        int row;

        bool onLeft;
        bool finished;
    };

    std::vector<ParticipantBridgeData> participantData;


    // =========================================================
    // GLASS PANELS
    // =========================================================

    struct GlassRow
    {
        bool safeIsLeft = false;

        bool leftBroken = false;
        bool rightBroken = false;
    };

    GlassRow bridge[ROW_COUNT]{};


    // =========================================================
    // CPU MEMORY
    // =========================================================

    struct MemoryData
    {
        Participant* participant;

        int row;

        bool safeWasLeft;

        int observedDistance;
    };

    std::vector<MemoryData> cpuMemory;


    // =========================================================
    // GAME STATE
    // =========================================================

    bool gameStarted;
    bool gameFinished;

    bool waitingForHumanInput;
    bool allRemainingParticipantsFinished();

    // =========================================================
    // TIMERS
    // =========================================================

    sf::Clock moveClock;
    sf::Clock humanChoiceClock;

    float nextMoveDelay;


    // =========================================================
    // GRAPHICS
    // =========================================================

    sf::Font font;

    sf::Text title;

    sf::Text turnText;
    sf::Text timerText;
    sf::Text instructionText;

    sf::Text statusText;
    sf::Text resultTitle;
    sf::Text survivorText;
    sf::Text continueButton;

    sf::RectangleShape continueButtonBox;


    // =========================================================
    // INTERNAL FUNCTIONS
    // =========================================================

    void generateBridge();

    void createTurnOrder();

    void selectNextParticipant();

    ParticipantBridgeData* getBridgeData(
        Participant* participant
    );

    void resolveHumanChoice(bool chooseLeft);

    void resolveCPUChoice();

    void resolveChoice(
        Participant* participant,
        bool chooseLeft
    );

    bool cpuChoosesLeft(
        Participant* participant,
        int row
    );

    void recordSuccessfulJump(
        Participant* participant,
        int row,
        bool safeWasLeft
    );

    void eliminateParticipant(
        Participant* participant
    );

    void passParticipant(
        Participant* participant
    );

    void checkMinimumSurvivors();

    int getTotalSurvivors();

    float generateMoveDelay();


public:

    // =========================================================
    // CONSTRUCTOR
    // =========================================================

    GlassBridge();


    // =========================================================
    // PARTICIPANTS
    // =========================================================

    void setParticipants(
        const std::vector<Participant*>& survivors
    );


    // =========================================================
    // MAIN FUNCTIONS
    // =========================================================

    GameState handleInput(sf::Event& event);

    void update();

    void draw(sf::RenderWindow& window);

    void reset();

    void startGame();
};